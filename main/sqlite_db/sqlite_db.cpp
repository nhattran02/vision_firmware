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

static const char *TAG = "sqlite3_db";

const char* data = "Callback function called";
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

int open_db(const char *filename, sqlite3 **db) {
   int rc = sqlite3_open(filename, db);
   if (rc) {
       printf("Can't open database: %s\n", sqlite3_errmsg(*db));
       return rc;
   } else {
       printf("Opened database successfully\n");
   }
   return rc;
}

char *zErrMsg = 0;
int db_exec(sqlite3 *db, const char *sql) {
   printf("%s\n", sql);
   int64_t start = esp_timer_get_time();
   int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   } else {
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
    sqlite3 *db;
    int rc;

    sqlite3_initialize();

    // Open database 1
    if (open_db("/sdcard/mdr512.db", &db))
        return;

#if 1
    rc = db_exec(db, "Select * from domain_rank where domain between 'google.com' and 'google.com.z'");
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return;
    }

    rc = db_exec(db, "Select * from domain_rank where domain = 'zoho.com'");
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);

    // All done, unmount partition and disable SDMMC or SPI peripheral
    esp_vfs_fat_sdmmc_unmount();
    ESP_LOGI(TAG, "Card unmounted");
#endif
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
