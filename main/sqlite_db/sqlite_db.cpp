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
    print_db();


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

    fprintf(file, "ID,NAME,EMPLOYEEID,ROLE,CHECK1,CHECK2,CHECK3,CHECK4,CHECK5,CHECK6\n");
    fprintf(file, "1,Nguyen Van A,123456,1,,,,,,\n");
    fprintf(file, "2,Tran Thi B,654321,0,,,,,,\n");

    fclose(file);
    ESP_LOGI(TAG, "Created csv template %s", csv_filename);
}

void import_csv_to_db(const char *csv_filename)
{  
    int rc = db_exec(db, "DELETE FROM employee;");
    if (rc != SQLITE_OK) 
    {
        ESP_LOGE(TAG, "Failed to clear existing data in the employee table");
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
        int check[6] = {0}; // CHECK1, CHECK2, CHECK3, CHECK4, CHECK5, CHECK6
        
        char *token = strtok(line, ",");
        if (token) strcpy(id, token);
        token = strtok(NULL, ",");
        if (token) strcpy(name, token);
        token = strtok(NULL, ",");
        if (token) strcpy(employeeId, token);
        token = strtok(NULL, ",");
        if (token) strcpy(role, token);
        for (int i = 0; i < 6 && (token = strtok(NULL, ",")); i++) {
            check[i] = atoi(token);
        }

        if (strlen(id) == 0 || strlen(name) == 0 || strlen(employeeId) == 0 || strlen(role) == 0) {
            ESP_LOGE(TAG, "Invalid data format: %s", line);
            continue;
        }
        
        char sql[512]; 
        snprintf(sql, sizeof(sql),
            "INSERT INTO employee (ID, NAME, EMPLOYEEID, ROLE, CHECK1, CHECK2, CHECK3, CHECK4, CHECK5, CHECK6) VALUES (%s, '%s', '%s', '%s', %d, %d, %d, %d, %d, %d);",
            id, name, employeeId, role, check[0], check[1], check[2], check[3], check[4], check[5]);

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

void SQLiteDB::delete_db()
{
    int rc = db_exec(db, "DELETE FROM employee;");
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return;
    }
}

void SQLiteDB::print_db() 
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
        snprintf(users[n_users].name, sizeof(users[n_users].name), "%s", reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        snprintf(users[n_users].employeeId, sizeof(users[n_users].employeeId), "%s", reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        users[n_users].role = sqlite3_column_int(stmt, 3);

        for (int i = 0; i < 6; i++)
        {
            users[n_users].check[i] = sqlite3_column_int(stmt, 4 + i);
        }
        
        n_users++;
    }
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

        printf("  Check Values: ");
        for (int j = 0; j < 6; j++)
        {
            printf("%d ", users[i].check[j]);
        }
        printf("\n");
    }
}