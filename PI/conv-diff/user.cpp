#include "user.h"

double Xvelocity(FVPoint2D<double> P,Parameter &para)
{
double val; 
return(para.getDouble("Xvelocity"));
}
double Yvelocity(FVPoint2D<double> P,Parameter &para)
{
return(para.getDouble("Yvelocity"));
}
double getDiffusion(FVEdge2D *ptr_e,Parameter &para)
{
return(para.getDouble("Diffusion"));    
}
double RHS(FVPoint2D<double> P,Parameter &para)
{
double val;
//val=P.x-1.;
val=FVLIB_PI*exp(FVLIB_PI*P.x)*sin(FVLIB_PI*P.y);
//val=FVLIB_PI*cos(P.x*FVLIB_PI)*exp(P.y);
return(val);
}
double Dirichlet(FVPoint2D<double> P,Parameter &para)
{
double val;
//val=0.5*P.x*P.x;
val=exp(FVLIB_PI*P.x)*sin(FVLIB_PI*P.y);
//val=(1+sin(FVLIB_PI*P.x))*exp(P.y);
return(val);
}
double Neumann(FVPoint2D<double> P,Parameter &para)
{
double val;
if(P.y<0.5) 
    val=FVLIB_PI*exp(FVLIB_PI*P.x)*cos(FVLIB_PI*P.y);
else
    val=-FVLIB_PI*exp(FVLIB_PI*P.x)*cos(FVLIB_PI*P.y);
return(val);
}
double solExact(FVPoint2D<double> P,Parameter &para)
{
double val;
//val=0.5*P.x*P.x;
val=exp(FVLIB_PI*P.x)*sin(FVLIB_PI*P.y);
//val=(1+sin(FVLIB_PI*P.x))*exp(P.y);
return(val);
}



