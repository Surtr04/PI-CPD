#include "papi.h"



void handle_error(int err_no) {
    fprintf(stderr,"\nError: %d - %s\n",err_no,p_errors[err_no].err_code);  
    exit(-1);
}

#define NUM_EVENTS 11

int current_event;        
unsigned long long int start_time, end_time;
PAPI_event_info_t inf;

int papi_events[NUM_EVENTS] = {
    PAPI_TOT_CYC,   /* Total number of cycles           */
    PAPI_TOT_INS,   /* Instructions completed           */
    PAPI_LD_INS,    /* number of load instructions      */
    PAPI_SR_INS,    /* number of store instructions     */  

    PAPI_FP_OPS,    /* Floating point operations        */
    PAPI_FP_INS,    /* Floating point instructions      */  

    PAPI_L1_DCA,    /* L1 data cache accesses           */
    PAPI_L1_DCM,    /* L1 data cache misses             */
    PAPI_L2_DCA,    /* L2 data cache accesses           */
    PAPI_L2_DCM,    /* L2 data cache misses             */
    PAPI_L3_DCA,    /* L3 data cache accesses           */
};


void inline papi_init() {

    int papi_version = PAPI_library_init(PAPI_VER_CURRENT);    


    check(papi_version != PAPI_VER_CURRENT && papi_version > 0, ERR_PAPI_INIT);
    check(papi_version < 0, ERR_PAPI_INIT2);

    event_set = PAPI_NULL;
    papi_safe(PAPI_create_eventset(&event_set), ERR_PAPI_EVENT_SET);

    //PAPI_event_info_t inf;
    papi_safe(PAPI_get_event_info(papi_events[current_event], &inf),ERR_PAPI_GET_EVENT_INFO);

    papi_safe(PAPI_add_event(event_set, papi_events[current_event]), ERR_PAPI_ADD_EVENT);
    start_time = PAPI_get_virt_usec();

}

void inline papi_start() {
    papi_safe(PAPI_start(event_set), ERR_PAPI_START);
}

void inline papi_stop() {
    papi_safe(PAPI_stop(event_set, event_value), ERR_PAPI_STOP);  
}


void inline papi_end(){

    end_time = PAPI_get_virt_usec();
    fprintf(stdout, "%s\t", inf.symbol);
    fprintf(stdout, "\t%llu\t", event_value[0]);    
    fprintf(stdout, "\t%llu\n", end_time - start_time);
    papi_safe(PAPI_remove_event(event_set, papi_events[current_event]), ERR_PAPI_REMOVE_EVENT);

}

