#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

int event_set;          //papi
long long event_value[2];  //papi  

typedef struct p_error {
        char err_code[30];        
} papi_error;



#define ERR_PAPI_INIT					0
#define ERR_PAPI_INIT2					1
#define ERR_PAPI_EVENT_SET				2
#define ERR_PAPI_ADD_EVENT				3
#define ERR_PAPI_REMOVE_EVENT	        4
#define ERR_PAPI_GET_EVENT_INFO	        5
#define ERR_PAPI_START					6
#define ERR_PAPI_STOP					7

static papi_error p_errors[] = {
        {"ERR_PAPI_INIT"					},
        {"ERR_PAPI_INIT2"					},
        {"ERR_PAPI_EVENT_SET"		        },
        {"ERR_PAPI_ADD_EVENT"		        },
        {"ERR_PAPI_REMOVE_EVENT"	        },
        {"ERR_PAPI_GET_EVENT_INFO"	        },
        {"ERR_PAPI_START"					},
        {"ERR_PAPI_STOP"					},
};


#define papi_safe(func,err_no) if (func != PAPI_OK) handle_error(err_no)
#define check(func,err_no) if (func) handle_error(err_no)


void inline papi_init();
void inline papi_end();
void inline papi_stop();
void inline papi_start();