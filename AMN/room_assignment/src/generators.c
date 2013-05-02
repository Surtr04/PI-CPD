#include "generators.h"

float randFloat() {
	float f = (float) arc4random() / (float) UINT32_MAX;
	return f;
}

double randDouble() {

	union _32to64 r;
	r.u32[0] = arc4random();	
	r.u32[1] = arc4random();	

	return ((double) r.u64 / (double) UINT64_MAX);
}


unsigned long randomul_limited (unsigned long min ,unsigned long max) {
	float f = randFloat();
	return f * ( max - min + 1 ) + min;
}