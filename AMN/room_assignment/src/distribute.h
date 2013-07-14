#pragma once

void randomseed (unsigned int seed);
void rand_dislikes (unsigned long* dislike_matrix, unsigned long students, unsigned long min, unsigned long max);
unsigned long distribute_random (unsigned long * dislikes, unsigned long * rooms, unsigned long * assigned, unsigned long nstudents);
unsigned long distribute_wo_sa (unsigned long * dislikes, unsigned long * rooms, unsigned long nstudents);