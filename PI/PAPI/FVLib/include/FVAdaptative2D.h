#ifndef _FVADAPTATIVE2D
#define _FVADAPTATIVE2D
#include "FVStencil.h"
#include "FVRecons2D.h"


class FVAdaptative2D
{
private:
FVStencil * _ptr_st[FVAPAPTATIVE_MAX_DEGREE+1]; 
FVRecons2D * _ptr_rec[FVAPAPTATIVE_MAX_DEGREE+1]; 
FVVect<double> *_Vertex2DVect,*_Edge2DVect,*_Cell2DVect;  
FVMesh2D *_ptr_m;
FVCell2D *_ptr_c;
FVEdge2D *_ptr_e;
FVVertex2D *_ptr_v;
size_t _reference_type;
public:
FVAdaptative2D(); // constructor
~FVAdaptative2D(); // destructor
FVAdaptative2D(const FVAdaptative2D  &ada); // copy constructor
FVAdaptative2D & operator =(const  FVAdaptative2D &ada) // assigment operator
{
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
     if(ada._ptr_st[i])  {_ptr_st[i]=new FVStencil;(*_ptr_st[i])=(*ada._ptr_st[i]); }
          else {_ptr_st[i]=NULL;}
     if(ada._ptr_rec[i]) {_ptr_rec[i]=new FVRecons2D;(*_ptr_rec[i])=(*ada._ptr_rec[i]); }      
          else {_ptr_rec[i]=NULL;}
    } 
_Vertex2DVect=ada._Vertex2DVect;
_Edge2DVect=ada._Edge2DVect;
_Cell2DVect=ada._Cell2DVect;     
_ptr_m=ada._ptr_m;   
_ptr_c=ada._ptr_c;
_ptr_e=ada._ptr_e;
_ptr_v=ada._ptr_v;
_reference_type=ada._reference_type;
return *this;   
}
void clean(); // clean the instance
void show(); // show the instance
void setMesh(FVMesh2D &m){_ptr_m=&m;}
FVMesh2D * getMesh(){return _ptr_m;}
void setReferenceGeometry(FVVertex2D *ptr_v ){_ptr_v=ptr_v;_reference_type=FVVERTEX2D;}
void setReferenceGeometry(FVEdge2D *ptr_e ){_ptr_e=ptr_e;_reference_type=FVEDGE2D;}
void setReferenceGeometry(FVCell2D *ptr_c ){_ptr_c=ptr_c;_reference_type=FVCELL2D;}

 
void makePolynomial(size_t degree, size_t type,size_t code,double weight); 
void makePolynomial(FVStencil &st,size_t degree, size_t type); 

void setVectorVertex2D( FVVect<double> & u);  
void setVectorEdge2D( FVVect<double> & u);  
void setVectorCell2D( FVVect<double> & u);  

void computeCoef();
void resetCoef();
double getValue(FVPoint2D<double> P, size_t d); 
FVPoint2D<double> getDerivative(FVPoint2D<double> P, size_t d); 
FVPoint2D<FVPoint2D<double> >getHessian(FVPoint2D<double> P, size_t d); 


};
#endif // define _FVADAPTATIVE2D