#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "sqlite_db.hpp"
#include "dirent.h"
#include <vector>
#include <string>

static const char *TAG = "sqlite3_db";
sqlite3 *db;

const char *data = "Callback function called";
static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    printf("%s: ", (const char *)data);
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int open_db(const char *filename, sqlite3 **db)
{
    int rc = sqlite3_open(filename, db);
    if (rc)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    else
    {
        printf("Opened database successfully\n");
    }
    return rc;
}

char *zErrMsg = 0;
int db_exec(sqlite3 *db, const char *sql)
{
    printf("%s\n", sql);
    int64_t start = esp_timer_get_time();
    int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        printf("Operation done successfully\n");
    }
    int64_t time_taken_us = esp_timer_get_time() - start;
    printf("Time taken: %lld us (%.2f ms)\n", time_taken_us, time_taken_us / 1000.0);
    return rc;
}

SQLiteDB::SQLiteDB(Button *key,
                   QueueHandle_t queue_i,
                   QueueHandle_t queue_o,
                   void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                                      key(key)
{
    int rc;

    sqlite3_initialize();

    if (open_db("/sdcard/data.db", &db))
        return;

    // delete_db();
    print_employee_db();
    ESP_LOGI(TAG, "\n");
    print_attendance_db();

    
    // create_csv_template();

    // import_csv_to_db("/sdcard/template.csv");

    // print_db();

    // sqlite3_close(db);
}

SQLiteDB::~SQLiteDB()
{
    // Empty
}

void SQLiteDB::update()
{
}

void SQLiteDB::run()
{
}

void create_csv_template(const char *csv_filename)
{
    FILE *file = fopen(csv_filename, "wb");
    if (file == NULL)
    {
        ESP_LOGE(TAG, "Can not open file %s", csv_filename);
        return;
    }

    fprintf(file, "ID,NAME,EMPLOYEEID,ROLE\n");
    fprintf(file, "1,Nguyen Van A,123456,1\n");
    fprintf(file, "2,Tran Thi B,654321,0\n");

    fclose(file);
    ESP_LOGI(TAG, "Created csv template %s", csv_filename);
}

void import_webserver_data_to_db(RawDataChunk_t *chunks, int chunk_count) 
{
    int rc = db_exec(db, "DELETE FROM employee;");
    if (rc != SQLITE_OK) {
        ESP_LOGE(TAG, "Failed to clear employee table.");
        sqlite3_close(db);
        return;
    }

    // rc = db_exec(db, "DELETE FROM attendance;");
    // if (rc != SQLITE_OK) {
    //     ESP_LOGE(TAG, "Failed to clear attendance table.");
    //     sqlite3_close(db);
    //     return;
    // }    

    ESP_LOGI(TAG, "Old data cleared from the employee table.");

    for (int i = 0; i < chunk_count; i++) {
        RawDataChunk_t *chunk = &chunks[i];

        if (strlen(chunk->id) == 0 || strlen(chunk->name) == 0 || 
            strlen(chunk->employeeId) == 0 || strlen(chunk->role) == 0) {
            ESP_LOGE(TAG, "Invalid data format in chunk %d: id=%s, name=%s, employeeId=%s, role=%s",
                     i + 1, chunk->id, chunk->name, chunk->employeeId, chunk->role);
            continue;
        }

        char sql[512] = {0};
        snprintf(sql, sizeof(sql),
                 "INSERT INTO employee (ID, NAME, EMPLOYEEID, ROLE) VALUES ('%s', '%s', '%s', '%s');",
                 chunk->id, chunk->name, chunk->employeeId, chunk->role);

        rc = db_exec(db, sql);
        if (rc != SQLITE_OK) {
            ESP_LOGE(TAG, "Failed to insert data from chunk %d: %s", i + 1, sql);
            sqlite3_close(db);
            return;
        }

        ESP_LOGI(TAG, "Inserted data from chunk %d: id=%s, name=%s, employeeId=%s, role=%s",
                 i + 1, chunk->id, chunk->name, chunk->employeeId, chunk->role);
    }

    ESP_LOGI(TAG, "All data from chunks imported to database successfully.");
}



void import_csv_to_db(const char *csv_filename)
{  
    int rc = db_exec(db, "DELETE FROM employee;");
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return;
    }
    rc = db_exec(db, "DELETE FROM attendance;");
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return;
    }      
    ESP_LOGI(TAG, "Old data cleared from the employee table");

    FILE *file = fopen(csv_filename, "r");
    if (file == NULL)
    {
        ESP_LOGE(TAG, "Can not open file %s", csv_filename);
        return;
    }

    char line[256];
    
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        
        char id[50] = {0};
        char name[100] = {0};
        char employeeId[50] = {0};
        char role[10] = {0};
        
        char *token = strtok(line, ",");
        if (token) strcpy(id, token);
        token = strtok(NULL, ",");
        if (token) strcpy(name, token);
        token = strtok(NULL, ",");
        if (token) strcpy(employeeId, token);
        token = strtok(NULL, ",");
        if (token) strcpy(role, token);

        if (strlen(id) == 0 || strlen(name) == 0 || strlen(employeeId) == 0 || strlen(role) == 0) {
            ESP_LOGE(TAG, "Invalid data format: %s", line);
            continue;
        }
        
        char sql[512] = {0}; 
        snprintf(sql, sizeof(sql), "INSERT INTO employee (ID, NAME, EMPLOYEEID, ROLE) VALUES (%s, '%s', '%s', '%s');", id, name, employeeId, role);

        int rc = db_exec(db, sql);
        if (rc != SQLITE_OK)
        {
            ESP_LOGE(TAG, "Failed to insert data: ");
            fclose(file);
            sqlite3_close(db);
            return;
        }        
    }
    fclose(file);
    ESP_LOGI(TAG, "Entered data from file %s", csv_filename);
}

void update_attendance_to_db(int id, const char *name, const char *date, const char *time)
{
    char sql[512] = {0};
    sqlite3_stmt *stmt;

    // check if ID and DATE already exist
    snprintf(sql, sizeof(sql), "SELECT CHECK1, CHECK2, CHECK3, CHECK4, CHECK5, CHECK6 FROM attendance WHERE ID = %d AND DATE = '%s';", id, date);
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        ESP_LOGE(TAG, "Failed to prepare SELECT statement: %s", sqlite3_errmsg(db));
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        // ID and DATE already exist, update CHECK columns
        for (int i = 0; i < 6; i++)
        {
            const unsigned char *check = sqlite3_column_text(stmt, i);
            if (check == NULL) // Cột trống
            {
                snprintf(sql, sizeof(sql), "UPDATE attendance SET CHECK%d = '%s' WHERE ID = %d AND DATE = '%s';", i + 1, time, id, date);
                sqlite3_finalize(stmt);
                rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
                if (rc != SQLITE_OK)
                {
                    ESP_LOGE(TAG, "Failed to update data: %s", sqlite3_errmsg(db));
                }
                return;
            }
        }
        ESP_LOGW(TAG, "All CHECK columns are full for ID %d on DATE %s", id, date);
    }
    else
    {
        // ID and DATE do not exist, insert new data
        snprintf(sql, sizeof(sql), "INSERT INTO attendance (ID, NAME, DATE, CHECK1) VALUES (%d, '%s', '%s', '%s');", id, name, date, time);
        sqlite3_finalize(stmt);
        rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
        if (rc != SQLITE_OK)
        {
            ESP_LOGE(TAG, "Failed to insert new data: %s", sqlite3_errmsg(db));
        }
    }
}

void SQLiteDB::delete_db()
{
    int rc = db_exec(db, "DELETE FROM employee;");
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return;
    }
    rc = db_exec(db, "DELETE FROM attendance;");
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return;
    }    
}

void SQLiteDB::print_employee_db()
{
    const char* sql = "SELECT * FROM employee;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    int column_count = sqlite3_column_count(stmt);
    

    for (int i = 0; i < column_count; i++) {
        printf("%s\t", sqlite3_column_name(stmt, i));
    }
    printf("\n");

    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < column_count; i++) {
            if (sqlite3_column_type(stmt, i) == SQLITE_NULL) {
                printf("NULL\t"); 
            } else {
                printf("%s\t", sqlite3_column_text(stmt, i));
            }
        }
        printf("\n"); 
    }

    sqlite3_finalize(stmt); 
}

void SQLiteDB::print_attendance_db()
{
    const char* sql = "SELECT * FROM attendance;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    int column_count = sqlite3_column_count(stmt);
    

    for (int i = 0; i < column_count; i++) {
        printf("%s\t", sqlite3_column_name(stmt, i));
    }
    printf("\n");

    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < column_count; i++) {
            if (sqlite3_column_type(stmt, i) == SQLITE_NULL) {
                printf("NULL\t"); 
            } else {
                printf("%s\t", sqlite3_column_text(stmt, i));
            }
        }
        printf("\n"); 
    }

    sqlite3_finalize(stmt); 
}

void load_data_from_database_to_users(void)
{
    const char *sql = "SELECT * FROM employee;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    n_users = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        if (n_users >= MAX_USERS)
        {
            ESP_LOGW(TAG, "Reached max number of employees: %d", MAX_USERS);
            break;
        }

        users[n_users].id = sqlite3_column_int(stmt, 0);
        const unsigned char *name_text = sqlite3_column_text(stmt, 1);
        snprintf(users[n_users].name, sizeof(users[n_users].name), "%s", name_text ? reinterpret_cast<const char *>(name_text) : "");        
        const unsigned char *employeeId_text = sqlite3_column_text(stmt, 2);
        snprintf(users[n_users].employeeId, sizeof(users[n_users].employeeId), "%s", employeeId_text ? reinterpret_cast<const char *>(employeeId_text) : "");
        users[n_users].role = sqlite3_column_int(stmt, 3);
        users[n_users].fingerprint = sqlite3_column_int(stmt, 4);
        users[n_users].faceid = sqlite3_column_int(stmt, 5);
        const unsigned char *password_hash_text = sqlite3_column_text(stmt, 6);
        snprintf(users[n_users].password_hash, sizeof(users[n_users].password_hash), "%s", password_hash_text ? reinterpret_cast<const char *>(password_hash_text) : "");
        
        n_users++;
    }
}


void load_data_from_database_to_attendance(void)
{
    ESP_LOGI(TAG, "Loading attendance data from database");
    const char *sql = "SELECT * FROM attendance;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    n_attendance = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        if (n_attendance >= MAX_ATTENDANCE)
        {
            ESP_LOGW(TAG, "Reached max number of attendance: %d", MAX_ATTENDANCE);
            break;
        }

        int _id = sqlite3_column_int(stmt, 0);
        snprintf(attendance_data[n_attendance].id, sizeof(attendance_data[n_attendance].id), "%d", _id);
        const unsigned char *name_text = sqlite3_column_text(stmt, 1);
        snprintf(attendance_data[n_attendance].name, sizeof(attendance_data[n_attendance].name), "%s", name_text ? reinterpret_cast<const char *>(name_text) : "");
        const unsigned char *date_text = sqlite3_column_text(stmt, 2);
        snprintf(attendance_data[n_attendance].date, sizeof(attendance_data[n_attendance].date), "%s", date_text ? reinterpret_cast<const char *>(date_text) : "");
        const unsigned char *check1_text = sqlite3_column_text(stmt, 3);
        snprintf(attendance_data[n_attendance].check1, sizeof(attendance_data[n_attendance].check1), "%s", check1_text ? reinterpret_cast<const char *>(check1_text) : "");
        const unsigned char *check2_text = sqlite3_column_text(stmt, 4);
        snprintf(attendance_data[n_attendance].check2, sizeof(attendance_data[n_attendance].check2), "%s", check2_text ? reinterpret_cast<const char *>(check2_text) : "");
        const unsigned char *check3_text = sqlite3_column_text(stmt, 5);
        snprintf(attendance_data[n_attendance].check3, sizeof(attendance_data[n_attendance].check3), "%s", check3_text ? reinterpret_cast<const char *>(check3_text) : "");
        const unsigned char *check4_text = sqlite3_column_text(stmt, 6);
        snprintf(attendance_data[n_attendance].check4, sizeof(attendance_data[n_attendance].check4), "%s", check4_text ? reinterpret_cast<const char *>(check4_text) : "");
        const unsigned char *check5_text = sqlite3_column_text(stmt, 7);
        snprintf(attendance_data[n_attendance].check5, sizeof(attendance_data[n_attendance].check5), "%s", check5_text ? reinterpret_cast<const char *>(check5_text) : "");
        const unsigned char *check6_text = sqlite3_column_text(stmt, 8);
        snprintf(attendance_data[n_attendance].check6, sizeof(attendance_data[n_attendance].check6), "%s", check6_text ? reinterpret_cast<const char *>(check6_text) : "");

        n_attendance ++;
    }
}

void update_finger_print_to_db(int id, int value)
{
    const char *sql = "UPDATE employee SET FINGER = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind the value and id to the SQL statement
    sqlite3_bind_int(stmt, 1, value); 
    sqlite3_bind_int(stmt, 2, id);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
}

void update_faceid_to_db(int id, int value)
{
    const char *sql = "UPDATE employee SET FACEID = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind the value and id to the SQL statement
    sqlite3_bind_int(stmt, 1, value); 
    sqlite3_bind_int(stmt, 2, id);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
}

void update_role_to_db(int id, int value)
{
    const char *sql = "UPDATE employee SET ROLE = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind the value and id to the SQL statement
    sqlite3_bind_int(stmt, 1, value);
    sqlite3_bind_int(stmt, 2, id);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
}

void update_password_to_db(int id, const char *password_hash)
{
    const char *sql = "UPDATE employee SET PASSWORD = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }    

    sqlite3_bind_text(stmt, 1, password_hash, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

void save_report_to_csv(const char *csv_file_path) 
{
    FILE *file = fopen(csv_file_path, "w");
    if (!file) 
    {
        printf("Failed to open file: %s\n", csv_file_path);
        return;
    }

    const char *sql = "SELECT * FROM attendance;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare SQL statement: %s\n", sqlite3_errmsg(db));
        fclose(file);
        return;
    }

    int column_count = sqlite3_column_count(stmt);
    for (int i = 0; i < column_count; i++) {
        fprintf(file, "%s", sqlite3_column_name(stmt, i));
        if (i < column_count - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        for (int i = 0; i < column_count; i++) {
            const char *value = (const char *)sqlite3_column_text(stmt, i);
            fprintf(file, "%s", value ? value : "");
            if (i < column_count - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    if (rc != SQLITE_DONE) {
        printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    fclose(file);

    printf("Report saved to: %s\n", csv_file_path);
}

bool check_admin_exist()
{
    const char *sql = "SELECT EXISTS (SELECT 1 FROM employee WHERE (FINGER = 1 OR FACEID = 1) AND ROLE = 1);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        exists = sqlite3_column_int(stmt, 0) == 1;
    }
    else
    {
        printf("Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);

    return exists;
}

void print_users(void)
{
    if (n_users == 0)
    {
        printf("No users loaded from the database.\n");
        return;
    }

    printf("User Data:\n");
    for (int i = 0; i < n_users; i++)
    {
        printf("User %d:\n", i + 1);
        printf("  ID: %d\n", users[i].id);
        printf("  Name: %s\n", users[i].name);
        printf("  Employee ID: %s\n", users[i].employeeId);
        printf("  Role: %d\n", users[i].role);
        printf("\n");
    }
}

void print_attendance(void)
{
    if (n_attendance == 0)
    {
        printf("No attendance data loaded from the database.\n");
        return;
    }

    printf("Attendance Data:\n");
    for (int i = 0; i < n_attendance; i++)
    {
        printf("Attendance %d:\n", i + 1);
        printf("  ID: %s\n", attendance_data[i].id);
        printf("  Name: %s\n", attendance_data[i].name);
        printf("  Date: %s\n", attendance_data[i].date);
        printf("  Check1: %s\n", attendance_data[i].check1);
        printf("  Check2: %s\n", attendance_data[i].check2);
        printf("  Check3: %s\n", attendance_data[i].check3);
        printf("  Check4: %s\n", attendance_data[i].check4);
        printf("  Check5: %s\n", attendance_data[i].check5);
        printf("  Check6: %s\n", attendance_data[i].check6);
        printf("\n");
    }
}