#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <papi.h>
#include "papi_errors.h"
#include "matrixDotProduct.h"


#define NUM_EVENTS 12			
int event_set;					
int current_event;				
long long event_value;			


int papi_events[NUM_EVENTS] = {
	PAPI_FML_INS,	
	PAPI_FDV_INS,	
	PAPI_TOT_CYC, 	
	PAPI_TOT_INS,	
	PAPI_LD_INS,	
	PAPI_SR_INS,	

	PAPI_VEC_INS,	
	PAPI_FP_OPS,	

	PAPI_L1_DCA,	
	PAPI_L1_DCM,	
	PAPI_L2_DCA,	
	PAPI_L2_DCM,
};

void run_papi() {

	int papi_version = PAPI_library_init(PAPI_VER_CURRENT);
	unsigned long long int start_time, end_time;


	check(papi_version != PAPI_VER_CURRENT && papi_version > 0, ERR_PAPI_INIT);
	check(papi_version < 0, ERR_PAPI_INIT2);

	event_set = PAPI_NULL;
	papi_safe(PAPI_create_eventset(&event_set), ERR_PAPI_EVENT_SET);

	PAPI_event_info_t inf;
	papi_safe(PAPI_get_event_info(papi_events[current_event], &inf),ERR_PAPI_GET_EVENT_INFO);

	papi_safe(PAPI_add_event(event_set, papi_events[current_event]), ERR_PAPI_ADD_EVENT);
	start_time = PAPI_get_virt_usec();
	
	dotProduct_papi();

	end_time = PAPI_get_virt_usec();
	fprintf(stdout, "%s\t", inf.symbol);
	fprintf(stdout, "\t%llu\t", event_value);
	fprintf(stdout, "\t%llu\n", end_time - start_time);
	papi_safe(PAPI_remove_event(event_set, papi_events[current_event]), ERR_PAPI_REMOVE_EVENT);



}

int main (int argc, char** argv) {
	//matrix size - w/ op? - event_index
	if(argc < 3){
		fprintf(stderr,"wrong number of arguments");
		exit(1);
	}

	size = atoi(argv[1]);
	int op = atoi(argv[2]);
	current_event = atoi(argv[3]);

	if (!op) {

		m = (matrices*) (malloc(sizeof(matrices)));

		m->matrixA = initRandMatrix();
		m->matrixB = initUnitMatrix();
		m->matrixC = initMatrix();			
	}
	else {
		m->matrixA = initRandMatrix();
		m->matrixB = transposeMatrix(initUnitMatrix());
		m->matrixC = initMatrix();
	}


	run_papi();

	free(m);

	return 0;

}

