// ------ FVKrylov.h ------
// S. CLAIN 2012/01
#ifndef _FVKrylov
#define _FVKrylov
//-----------
#include "FVLib_config.h"
#include "FVGlobal.h"
#include "FVVect.h"
#include "FVSparseM.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <omp.h>


using std::cout;
using std::endl;
template<class T_> class FVKrylov
{
protected:
size_t _k,_max_k,_nb_rows;
FVVect<T_> _x0,_b,_r0,_c,_cos,_sin;
std::vector< FVVect<T_> > _QKry,_UKry;
FVSparseM<T_> _Cond;
double _Nr0;
public:
    
     FVKrylov();
     FVKrylov(const size_t m);       
    ~FVKrylov();
     FVKrylov(const FVKrylov &kr); // copy class
     void setRightHandSide(const FVVect<T_> &b);
     void setInitialVector(const FVVect<T_> &x0);
     void setInitialResidual(FVVect<T_> &r0);
     double setArnoldi( FVVect<T_> &q);
     size_t getNoIteration(){return(_k);}
     FVVect<T_> getSolution();
     double setConditionningArnoldi( FVVect<T_> &q);
     void setConditionningMatrix(const FVSparseM<T_> &cond);
     void clean();
     void clean(size_t m);
};

template<class T_>
FVKrylov<T_>::FVKrylov()
{
  _max_k=10; _k=0;_nb_rows=0;
  _QKry.resize(_max_k+1);
  _UKry.resize(_max_k+1);  
  _c.resize(_max_k+1);_c=0;_c[0]=1;
  _cos.resize(_max_k+1);
  _sin.resize(_max_k+1);
}
template<class T_>
FVKrylov<T_>::FVKrylov(const size_t m)
{
  _max_k=m; _k=0;_nb_rows=0;
  _QKry.resize(_max_k+1);
  _UKry.resize(_max_k+1);  
  _c.resize(_max_k+1);_c=0;_c[0]=1;
  _cos.resize(_max_k+1);
  _sin.resize(_max_k+1);  
}

template<class T_>
FVKrylov<T_>::~FVKrylov()
{
   _k=0.;
}
template<class T_>
FVKrylov<T_>::FVKrylov(const FVKrylov &kr)  
{
     _k=kr._k;_max_k=kr._max_k;_nb_rows=kr._nb_rows;
     // here I have to copy the matrixes and the vectors
} 
template<class T_> 
void FVKrylov<T_>::setRightHandSide(const FVVect<T_> &b)
{
if(_nb_rows==0) {_nb_rows=b.size();_b.resize(_nb_rows);}    
#ifdef _DEBUGS
    size_t err=(_nb_rows != b.size());
    if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif      
_b=b;    
}
template<class T_> 
void FVKrylov<T_>::setInitialVector(const FVVect<T_> &x0)
{
if(_nb_rows==0) {_nb_rows=x0.size();_x0.resize(_nb_rows);}    
#ifdef _DEBUGS
    size_t err=(_nb_rows != x0.size());
    if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif      
_x0=x0;   
}
template<class T_>
void FVKrylov<T_>::setInitialResidual(FVVect<T_> &r0)
{
if(_nb_rows==0) {_nb_rows=r0.size();_r0.resize(_nb_rows);}    
#ifdef _DEBUGS
    size_t err=(_nb_rows != r0.size());
    if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif      
_r0=r0;   
_Nr0=Norm(r0);r0/=_Nr0;
_QKry[0].resize(_nb_rows);_QKry[0]=r0;
_c[0]*=_Nr0;
//cout<<" initialise _Q matrix with";r0.show();
_k++;
}

template<class T_> 
double FVKrylov<T_>::setArnoldi(FVVect<T_> &q)
{
double aux1,aux2,test,rc;
    //_k is the number of column vector that contain Q
if(_k>_max_k) 
    {cout<<"Warning max number of Krylov iteration attained"<<endl;return(0.);}
if(_k==0) 
    {cout<<"Warning, initial residual has not been set"<<endl; return(0.);}
//cout<<"in the arnoldi with k="<<_k<<endl;
//cout<<"Aq=";q.show();
_QKry[_k].resize(_nb_rows);
_UKry[_k-1].resize(_max_k+1);
// Arnoldi algorithm
for(size_t i=0;i<_k;i++)  (_UKry[_k-1])[i]=Dot(_QKry[i],q);   
for(size_t i=0;i<_k;i++)  q-=(_UKry[_k-1])[i]*_QKry[i];

//cout<<"vector p=";q.show();
if(NormMax((q))<FVKRYLOV_PRECISION) 
     {
      //cout<<"orthogonal basis complete"<<endl;
      //cout<<"Hessenber matrix column";_U[_k-1].show();
      for(size_t l=0;l<_k-1;l++)
          {
          aux1=(_UKry[_k-1])[l]*_cos[l]+(_UKry[_k-1])[l+1]*_sin[l];
          aux2=-(_UKry[_k-1])[l]*_sin[l]+(_UKry[_k-1])[l+1]*_cos[l];
          (_UKry[_k-1])[l]=aux1;
          (_UKry[_k-1])[l+1]=aux2;
          }
      //  no more vector for _Q;   
      _k++;
      return(0.);
     } 
test=(_UKry[_k-1])[_k]=Norm(q);    
q/=(_UKry[_k-1])[_k];_QKry[_k]=q;
//cout<<"new normalized q";q.show(); 
//cout<<"Hessenber matrix column";_U[_k-1].show();
// ortogonalization Hessenberg 
for(size_t l=0;l<_k-1;l++)
    {
    aux1=(_UKry[_k-1])[l]*_cos[l]+(_UKry[_k-1])[l+1]*_sin[l];
    aux2=-(_UKry[_k-1])[l]*_sin[l]+(_UKry[_k-1])[l+1]*_cos[l];
    (_UKry[_k-1])[l]=aux1;
    (_UKry[_k-1])[l+1]=aux2;
    }
// define the new Givens matrix
rc=sqrt((_UKry[_k-1])[_k]*(_UKry[_k-1])[_k]+(_UKry[_k-1])[_k-1]*(_UKry[_k-1])[_k-1]);
_cos[_k-1]=(_UKry[_k-1])[_k-1]/rc;
_sin[_k-1]=(_UKry[_k-1])[_k]/rc;
// eliminate 
aux1=(_UKry[_k-1])[_k-1]*_cos[_k-1]+(_UKry[_k-1])[_k]*_sin[_k-1];
aux2=-(_UKry[_k-1])[_k-1]*_sin[_k-1]+(_UKry[_k-1])[_k]*_cos[_k-1];
(_UKry[_k-1])[_k-1]=aux1;
(_UKry[_k-1])[_k]=aux2;
aux1=_c[_k-1]*_cos[_k-1]+_c[_k]*_sin[_k-1];
aux2=-_c[_k-1]*_sin[_k-1]+_c[_k]*_cos[_k-1];
_c[_k-1]=aux1;
_c[_k]=aux2;
//cout<<"U column ";(_U[_k-1]).show();
//cout<<"c = ";_c.show();
// dont compute the solution is not necessary
_k++;
//cout<<"--------end iteration--------with k="<<_k<<endl;
return(test);// We return the norm of the orthogonal part of Aq 
               // if small then Aq is in the Krylov space.
               //caution,we have incremented the index 
}

template<class T_> 
FVVect<T_>  FVKrylov<T_>::getSolution()
{
// let 's have a look
//FVVect<T_> xx(_max_k+1); 
FVVect<T_> y(_max_k+1),x(_nb_rows);

_k--;
//cout<<"situation before resolution, we have k="<<_k<<endl;
//cout<<"Q matrix"<<endl; for(size_t j=0;j<_k;j++) _Q[j].show();
//cout<<"U matrix"<<endl; for(size_t j=0;j<_k;j++) _U[j].show();
//cout<<"c=";_c.show();
//  backsubstitution
y=0;
for(size_t i=0;i<_k;i++)
    {    
    y[_k-1-i]=_c[_k-1-i];    
    for(size_t j=0;j<i;j++) y[_k-1-i]-=(_UKry[_k-1-j])[_k-1-i]*y[_k-1-j];
    y[_k-1-i]/=(_UKry[_k-1-i])[_k-1-i];
    }    
//cout<<"y=";y.show();   
//xx=0;
//for(size_t i=0;i<_k;i++) for(size_t j=0;j<_k;j++) xx[i]+=(_U[j])[i]*y[j];
//xx-=_c;
//cout<<"Uy-c=";xx.show();
// compute the solution
x=_x0;
for(size_t i=0;i<_k;i++) x+=y[i]*_QKry[i];
_k++;
return(x);
}

template<class T_> 
double FVKrylov<T_>::setConditionningArnoldi(FVVect<T_> &q)
{
return(0.0);   
}



template<class T_> 
void FVKrylov<T_>::setConditionningMatrix(const FVSparseM<T_> &cond)
{
    ;   
}
     
template<class T_> 
void FVKrylov<T_>::clean()
{
 _k=0;_nb_rows=0; _c=0;_c[0]=1;
}

template<class T_> 
void FVKrylov<T_>::clean(size_t m)
{
  _max_k=m; _k=0;_nb_rows=0;
  _QKry.resize(_max_k+1);
  _UKry.resize(_max_k+1);  
  _c.resize(_max_k+1);_c=0;_c[0]=1;
  _cos.resize(_max_k+1);
  _sin.resize(_max_k+1);  
}
#endif // define _FVKrylov


