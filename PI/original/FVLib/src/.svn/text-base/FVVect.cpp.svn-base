#include "FVVect.h"




double Dot(FVVect<double> &u, FVVect<double> &v)
{
double d=0.;
#ifdef _DEBUGS
    size_t err=(u.size()!=v.size());
    if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif
for(size_t i=0;i<u.size();i++) d+=u[i]*v[i];
return(d);
}

double Norm(FVVect<double> &u)
{
return(sqrt(Dot(u,u)));
}
double Min(FVVect<double> &u)
{
double m=u[0];
for(size_t i=0;i<u.size();i++) if(m>u[i]) m=u[i];
return(m);
}
double Max(FVVect<double> &u)
{
double m=u[0];
for(size_t i=0;i<u.size();i++) if(m<u[i]) m=u[i];
return(m);
}
double NormMax(FVVect<double> &u)
{
double m=u[0]*u[0];
for(size_t i=0;i<u.size();i++) if(m<u[i]*u[i]) m=u[i]*u[i];
return(sqrt(m));
}