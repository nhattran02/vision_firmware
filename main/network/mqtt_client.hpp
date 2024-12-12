#pragma once

#include "stdio.h"

typedef enum JobActionType
{
    JOB_ACTION_HANDSHAKE,  
    JOB_ACTION_UPLOAD_RAW_DATA,
    JOB_ACTION_IMPORT_DATA,
    JOB_ACTION_UNKNOWN
} JobActionType_t;

typedef struct {
    int chunk_index;          
    char id[50];             
    char name[100];          
    char employeeId[50];     
    char role[10];
} RawDataChunk_t;

int aws_iot_demo_main( int argc, char ** argv );
void aws_iot_run(void);
