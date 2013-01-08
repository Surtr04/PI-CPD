 // ------ Tools.h ------
// S. CLAIN 2012/06

#ifndef _Tools 
#define _Tools
#include "FVLib_config.h" 
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdlib>

inline double FVPow(double x, size_t p)
{
   register double val=1.;
   while(p) {val*=x;p--;}
   return(val);
} 

inline double FVSqrt3(double a)
{
  register double x=a,x1,x2,inva,f;
  if(a==0) return(a);
  if(std::abs(a)==1.) return(a);
  inva=1./a;
  while(std::abs(f)*inva>FVEPSI)
      {
      x1=x*x;f=(x1+x1+x1-a);x2=x1*x-a;f/=x2;x-=f;    
      }
  return(x);
}

void strtos(char *ptr, char **endptr,char *auxString);
#endif // define _Tools
