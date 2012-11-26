#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <papi.h>
#include "papi_errors.h"



int main (int argc, char** argv) {


}

void run_papi() {

	int papi_version = PAPI_library_init(PAPI_VER_CURRENT);
	unsigned long long int start_time, end_time;


	check(papi_version != PAPI_VER_CURRENT && papi_version > 0, ERR_PAPI_INIT);
	check(papi_version < 0, ERR_PAPI_INIT2);


	


}