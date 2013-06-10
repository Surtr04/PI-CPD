// ------ FVRecons1D.h ------
// S. CLAIN 2011/10
#ifndef _FVRECONS1D
#define _FVRECONS1D
#include "FVMesh1D.h"
#include "FVStencil.h"
#include "FVVect.h"
#include "FVDenseM.h"
#include "FVPoint1D.h"
#include "FVGaussPoint.h"
#include "FVLib_config.h"
#include "FVTools.h"

class FVRecons1D
{
private:
FVPoint1D<double> _ref_point;
FVVect<double> *_Vertex1DVect,*_Cell1DVect;  
FVVect<double> *_coef,*_M;
FVStencil * _ptr_s;
FVDenseM<double> *_A,*_Q,*_Adag;
double _evalMean(void *ptr,size_t type,size_t alpha); 
double _ref_val;
size_t _degree,_Ncoef,_reconstruction_type;

public:
FVRecons1D()
    {
     //cout<<"using the FVRecons2D  default constructor"<<endl;  fflush(NULL);        
    _ptr_s=NULL;
    _Vertex1DVect=NULL;
    _Cell1DVect=NULL;
    _A=new   FVDenseM<double>; 
    _Q=new   FVDenseM<double>;
    _coef= new FVVect<double>;
    _M=new FVVect<double>;
    _Adag=new   FVDenseM<double>;
    _ref_point=0.; _ref_val=0;_degree=0;_Ncoef=0;_reconstruction_type= REC_NULL;
    }             
FVRecons1D(FVStencil *ptr_s)
    {
    //cout<<"using the FVRecons1D constructor with stencil"<<endl;    fflush(NULL);        
    _ptr_s=ptr_s;
    _A=new   FVDenseM<double>; 
    _Q=new   FVDenseM<double>;
    _coef= new FVVect<double>;
    _M=new FVVect<double>;
    _Adag=new   FVDenseM<double>;    
    _ref_point=0;_degree=0;_Ncoef=0;_reconstruction_type= REC_NULL;
    if(ptr_s->getReferenceType()==FVVERTEX1D) 
        _ref_point=((FVVertex1D *)(_ptr_s->getReferenceGeometry()))->coord;
    if(ptr_s->getReferenceType()==FVCELL1D) 
        _ref_point=((FVCell1D *)(_ptr_s->getReferenceGeometry()))->centroid;
    }
FVRecons1D(FVStencil *ptr_s, size_t degree)
    {
    //cout<<"using the FVRecons2D constructor with stencil and degress"<<endl;  fflush(NULL);     
    _degree=degree;    
    _Ncoef=_degree;
    _ptr_s=ptr_s;
    _A=new   FVDenseM<double>; 
    _Q=new   FVDenseM<double>;
    _coef= new FVVect<double>;
    _M=new FVVect<double>;
    _Adag=new   FVDenseM<double>;    
    _ref_point=0;
    _reconstruction_type= REC_NULL;
    if(ptr_s->getReferenceType()==FVVERTEX1D) 
        _ref_point=((FVVertex1D *)(_ptr_s->getReferenceGeometry()))->coord;
    if(ptr_s->getReferenceType()==FVCELL1D) 
        _ref_point=((FVCell1D *)(_ptr_s->getReferenceGeometry()))->centroid;
    }  
// destructor    
~FVRecons1D(){if(_A) delete(_A); if(_Q) delete(_Q);if(_coef) delete(_coef);if(_M) delete(_M);if(_Adag) delete(_Adag);}  
FVRecons1D(const FVRecons1D & rec); // copy constructor
FVRecons1D & operator =(const  FVRecons1D &rec) // assigment operator
{
    //cout<<"using the FVRecons1D assigment operator "<<endl; fflush(NULL); 
    _ptr_s=rec._ptr_s;
    _Vertex1DVect=rec._Vertex1DVect;
    _Cell1DVect=rec._Cell1DVect;
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
   
// setStencil    
void setStencil(FVStencil &st){ FVRecons1D::setStencil(&st); }      
void setStencil(FVStencil *ptr_s)
    {
    _ptr_s=ptr_s;
    _ref_point=0;_degree=0;_Ncoef=0;
     if(_ptr_s->getReferenceType()==FVVERTEX1D)
         _ref_point=((FVVertex1D *)(_ptr_s->getReferenceGeometry()))->coord;
     if(_ptr_s->getReferenceType()==FVCELL1D)  
         _ref_point=((FVCell1D *)(_ptr_s->getReferenceGeometry()))->centroid;       
     }
void setStencil(FVStencil &st, size_t degree){ FVRecons1D::setStencil(&st,degree); }      
void setStencil(FVStencil *ptr_s, size_t degree)
    {
    _ptr_s=ptr_s;
    _ref_point=0;   
    _degree=degree; 
    _Ncoef=_degree;
     if(_ptr_s->getReferenceType()==FVVERTEX1D) _ref_point=((FVVertex1D *)(_ptr_s->getReferenceGeometry()))->coord;
     if(_ptr_s->getReferenceType()==FVCELL1D)  _ref_point=((FVCell1D *)(_ptr_s->getReferenceGeometry()))->centroid;  
     }
FVStencil *getStencil() {return(_ptr_s);}       
//others     
void setPolynomialDegree(size_t degree){_degree=degree;_Ncoef=_degree;}    
size_t getPolynomialDegree(){return(_degree); } 
void setReferencePoint(double x){_ref_point.x=x;}
void setReferencePoint(FVPoint1D<double> P){_ref_point=P;}
void setVectorVertex1D( FVVect<double> & u){_Vertex1DVect=&u;}
void setVectorCell1D( FVVect<double> & u){_Cell1DVect=&u;}
void setReconstructionType(size_t rec_type){_reconstruction_type=rec_type;}
size_t getReconstructionType(){return _reconstruction_type;}
void doConservativeMatrix();
void computeConservativeCoef();
void doNonConservativeMatrix();
void computeNonConservativeCoef();
void doMatrix()
    {
     if(_reconstruction_type==REC_NULL) {cout<<"error construction type not defined"<<endl;exit(0);}        
     if(_reconstruction_type==REC_NON_CONSERVATIVE)  FVRecons1D::doNonConservativeMatrix();
     if(_reconstruction_type==REC_CONSERVATIVE)  FVRecons1D::doConservativeMatrix();            
    }
void computeCoef()
    {
     if(_reconstruction_type==REC_NULL) {cout<<"error construction type not defined"<<endl;exit(0);}         
     if(_reconstruction_type==REC_NON_CONSERVATIVE)  FVRecons1D::computeNonConservativeCoef();
     if(_reconstruction_type==REC_CONSERVATIVE)  FVRecons1D::computeConservativeCoef();            
    }
double ConditioningNumber();
void resetCoef(){if (_coef->size()!=_Ncoef) _coef->resize(_Ncoef);(*_coef)=0.;_ref_val=0.;}
double getValue(FVPoint1D<double> P, size_t degree); 
double getValue(FVPoint1D<double> P){return(FVRecons1D::getValue(P,_degree));} 
FVPoint1D<double> getDerivative(FVPoint1D<double> P, size_t degree);
FVPoint1D<double> getDerivative(FVPoint1D<double> P){return(FVRecons1D::getDerivative(P,_degree));}
FVPoint1D<FVPoint1D<double> >getHessian(FVPoint1D<double> P, size_t degree);
FVPoint1D<FVPoint1D<double> >getHessian(FVPoint1D<double> P){return(FVRecons1D::getHessian(P,_degree));}

void clean()
    {
    _A->resize(0);     
    _Adag->resize(0); 
    _Q->resize(0); 
    _coef->resize(0);        
    _M->resize(0);       
    _ptr_s=NULL;
    _Vertex1DVect=NULL;
    _Cell1DVect=NULL;
    _ref_point=0.; _ref_val=0;_degree=0;_Ncoef=0;
    _reconstruction_type= REC_NULL;    
    }
void show(); 
};

FVPoint1D<size_t> alpha1D(size_t k);


#endif // define _FVRECONS1D