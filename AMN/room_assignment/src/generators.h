#pragma once
#include <stdint.h>
#include <limits.h>

#ifdef __APPLE__
#include <stdlib.h>
#else
#include <bsd/stdlib.h>
#endif

union _32to64 {
		uint32_t u32[2];
		uint64_t u64;
};


float randFloat();
double randDouble();
unsigned long randomul_limited (unsigned long min ,unsigned long max);