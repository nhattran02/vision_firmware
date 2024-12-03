#pragma once

#include "stdio.h"

typedef enum JobActionType
{
    JOB_ACTION_HANDSHAKE,  
    JOB_ACTION_UPLOAD_RAW_DATA,
    JOB_ACTION_EXIT,
    JOB_ACTION_UNKNOWN
} JobActionType_t;

int aws_iot_demo_main( int argc, char ** argv );
void aws_iot_run(void);
