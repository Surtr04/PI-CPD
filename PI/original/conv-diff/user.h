#include "FVLib.h"
#include <iostream>
#include <ctime>

double Xvelocity(FVPoint2D<double> P,Parameter &para);
double Yvelocity(FVPoint2D<double> P,Parameter &para);
double getDiffusion(FVEdge2D *ptr_e,Parameter &para);
double RHS(FVPoint2D<double> P,Parameter &para);
double Dirichlet(FVPoint2D<double> P,Parameter &para);
double Neumann(FVPoint2D<double> P,Parameter &para);
double solExact(FVPoint2D<double> P,Parameter &para);