// ------ FVRecons2D.h ------
// S. CLAIN 2011/11
#ifndef _FVRECONS2D
#define _FVRECONS2D
#include "FVMesh2D.h"
#include "FVStencil.h"
#include "FVCell2D.h"
#include "FVVect.h"
#include "FVDenseM.h"
#include "FVPoint2D.h"
#include "FVPoint3D.h"
#include "FVGaussPoint.h"
#include "FVLib_config.h"
#include "FVTools.h"

class FVRecons2D
{
private:
FVPoint2D<double> _ref_point;
FVVect<double> *_Vertex2DVect,*_Edge2DVect,*_Cell2DVect;  
FVVect<double> *_coef,*_M;
FVStencil * _ptr_s;
FVDenseM<double> *_A,*_Q,*_Adag;
double _evalMean(void *ptr,size_t type,size_t alpha1, size_t alpha2); 
double _ref_val;
size_t _degree,_Ncoef,_reconstruction_type;
public:
// Constructors and destructors
FVRecons2D()
{
//cout<<"using the FVRecons2D  default constructor"<<endl;  fflush(NULL); 
_ptr_s=NULL;_Vertex2DVect=NULL;_Edge2DVect=NULL;_Cell2DVect=NULL;
_A=new   FVDenseM<double>; 
_Q=new   FVDenseM<double>;
_coef= new FVVect<double>;
_M=new FVVect<double>;
_Adag=new   FVDenseM<double>;
_ref_point=0.; _ref_val=0;_degree=0;_Ncoef=0;
_reconstruction_type= REC_NULL;
}
FVRecons2D(FVStencil *ptr_s)
{
//cout<<"using the FVRecons2D constructor with stencil"<<endl;    fflush(NULL);        
_ptr_s=ptr_s;
_A=new   FVDenseM<double>; 
_Q=new   FVDenseM<double>;
_coef= new FVVect<double>;
_M=new FVVect<double>;
_Adag=new   FVDenseM<double>; 
_ref_point=0;_degree=0;_Ncoef=0;_reconstruction_type= REC_NULL;
if(ptr_s->getReferenceType()==FVVERTEX2D) _ref_point=((FVVertex2D *)(_ptr_s->getReferenceGeometry()))->coord;
if(ptr_s->getReferenceType()==FVEDGE2D)   _ref_point=((FVEdge2D *)(_ptr_s->getReferenceGeometry()))->centroid;    
if(ptr_s->getReferenceType()==FVCELL2D)   _ref_point=((FVCell2D *)(_ptr_s->getReferenceGeometry()))->centroid;
}
FVRecons2D(FVStencil *ptr_s, size_t degree)
{
//cout<<"using the FVRecons2D constructor with stencil and degress"<<endl;  fflush(NULL);          
_degree=degree;    
_Ncoef=((_degree+2)*(_degree+1))/2-1;
_ptr_s=ptr_s;
_A=new   FVDenseM<double>; 
_Adag=new   FVDenseM<double>; 
_Q=new   FVDenseM<double>;
_coef= new FVVect<double>;
_M=new FVVect<double>;
_ref_point=0;
_reconstruction_type= REC_NULL;
if(ptr_s->getReferenceType()==FVVERTEX2D) _ref_point=((FVVertex2D *)(_ptr_s->getReferenceGeometry()))->coord;
if(ptr_s->getReferenceType()==FVEDGE2D)   _ref_point=((FVEdge2D *)(_ptr_s->getReferenceGeometry()))->centroid;    
if(ptr_s->getReferenceType()==FVCELL2D)   _ref_point=((FVCell2D *)(_ptr_s->getReferenceGeometry()))->centroid;
}    
// destructor   
~FVRecons2D()
{
// cout<<"using the FVRecons2D destructor "<<endl; fflush(NULL);   
    if(_A) delete(_A); if(_Q) delete(_Q);if(_coef) delete(_coef);if(_M) delete(_M);if(_Adag) delete(_Adag);     
} 

FVRecons2D(const FVRecons2D & rec); // copy constructor
FVRecons2D & operator =(const  FVRecons2D &rec) // assigment operator
{
//cout<<"using the FVRecons2D assigment operator "<<endl; fflush(NULL); 
_ptr_s=rec._ptr_s;
_Vertex2DVect=rec._Vertex2DVect;
_Edge2DVect=rec._Edge2DVect;
_Cell2DVect=rec._Cell2DVect; 
_ref_point=rec._ref_point; 
_ref_val=rec._ref_val;
_degree=rec._degree;
_Ncoef=rec._Ncoef; 
_reconstruction_type=rec._reconstruction_type;
//             
_A->resize(rec._A->nb_rows,rec._A->nb_cols);
(*_A)=(*rec._A); 
_Adag->resize(rec._Adag->nb_rows,rec._Adag->nb_cols);
(*_Adag)=(*rec._Adag);   
_Q->resize(rec._Q->nb_rows,rec._Q->nb_cols);
(*_Q)=(*rec._Q); 
_coef->resize(rec._coef->size());    
(*_coef)=(*rec._coef); 
_M->resize(rec._M->size());   
(*_M)=(*rec._M); 
return *this;
}
void checkMemory();

// setStencil 
void setStencil(FVStencil &st){ FVRecons2D::setStencil(&st); }      
void setStencil(FVStencil *ptr_s)
{
_ptr_s=ptr_s;
_ref_point=0;_degree=0;_Ncoef=0;
if(ptr_s->getReferenceType()==FVVERTEX2D) _ref_point=((FVVertex2D *)(_ptr_s->getReferenceGeometry()))->coord;
if(ptr_s->getReferenceType()==FVEDGE2D)   _ref_point=((FVEdge2D *)(_ptr_s->getReferenceGeometry()))->centroid;    
if(ptr_s->getReferenceType()==FVCELL2D)   _ref_point=((FVCell2D *)(_ptr_s->getReferenceGeometry()))->centroid;       
 }
void setStencil(FVStencil &st, size_t degree){ FVRecons2D::setStencil(&st,degree); }      
void setStencil(FVStencil *ptr_s, size_t degree)
{
_ptr_s=ptr_s;
_ref_point=0;   
_degree=degree; 
_Ncoef=((_degree+2)*(_degree+1))/2-1;
if(ptr_s->getReferenceType()==FVVERTEX2D) _ref_point=((FVVertex2D *)(_ptr_s->getReferenceGeometry()))->coord;
if(ptr_s->getReferenceType()==FVEDGE2D)   _ref_point=((FVEdge2D *)(_ptr_s->getReferenceGeometry()))->centroid;    
if(ptr_s->getReferenceType()==FVCELL2D)   _ref_point=((FVCell2D *)(_ptr_s->getReferenceGeometry()))->centroid;       
 }
FVStencil *getStencil() {return(_ptr_s);}     
// others     
void setPolynomialDegree(size_t degree){_degree=degree;_Ncoef=((_degree+2)*(_degree+1))/2-1;}    
size_t getPolynomialDegree(){return(_degree); } 
void setReferencePoint(FVPoint2D<double> P){_ref_point=P;}
void setVectorVertex2D( FVVect<double> & u){_Vertex2DVect=&u;}
void setVectorEdge2D( FVVect<double> & u)  {_Edge2DVect=&u;}
void setVectorCell2D( FVVect<double> & u)  {_Cell2DVect=&u;}
void setReconstructionType(size_t rec_type){_reconstruction_type=rec_type;}
size_t getReconstructionType(){return _reconstruction_type;}
FVVect<double>* getVectorVertex2D( ){return _Vertex2DVect;}
FVVect<double>* getVectorEdge2D( )  {return _Edge2DVect;}
FVVect<double>* getVectorCell2D( )  {return _Cell2DVect;}
void doConservativeMatrix();
void computeConservativeCoef(); 
void doNonConservativeMatrix();
void computeNonConservativeCoef();
void doMatrix()
    {
     if(_reconstruction_type==REC_NULL) {cout<<"error construction type not defined"<<endl;exit(0);}          
     if(_reconstruction_type==REC_NON_CONSERVATIVE)  FVRecons2D::doNonConservativeMatrix();
     if(_reconstruction_type==REC_CONSERVATIVE)  FVRecons2D::doConservativeMatrix();            
    }
void computeCoef()
    {
     if(_reconstruction_type==REC_NULL) {cout<<"error construction type not defined"<<endl;exit(0);}          
     if(_reconstruction_type==REC_NON_CONSERVATIVE)  FVRecons2D::computeNonConservativeCoef();
     if(_reconstruction_type==REC_CONSERVATIVE)  FVRecons2D::computeConservativeCoef();            
    }
double ConditioningNumber();
void resetCoef(){if (_coef->size()!=_Ncoef) _coef->resize(_Ncoef);(*_coef)=0.;_ref_val=0.;}
double getValue(FVPoint2D<double> P, size_t degree );    
double getValue(FVPoint2D<double> P){return(FVRecons2D::getValue(P,_degree));}    
FVPoint2D<double> getDerivative(FVPoint2D<double> P, size_t degree);
FVPoint2D<double> getDerivative(FVPoint2D<double> P){return(FVRecons2D::getDerivative(P,_degree));}
FVPoint2D<FVPoint2D<double> >getHessian(FVPoint2D<double> P, size_t degree);
FVPoint2D<FVPoint2D<double> >getHessian(FVPoint2D<double> P){return(FVRecons2D::getHessian(P,_degree));}
void clean()
{
_A->resize(0); _Q->resize(0);_coef->resize(0);_M->resize(0);_Adag->resize(0);
_ptr_s=NULL;_Vertex2DVect=NULL;_Edge2DVect=NULL;_Cell2DVect=NULL;
_ref_point=0.; _ref_val=0;_degree=0;_Ncoef=0;
    _reconstruction_type= REC_NULL;  
}
void show();    
};

FVPoint2D<size_t> alpha2D(size_t k);






#endif // define _FVRECONS2D