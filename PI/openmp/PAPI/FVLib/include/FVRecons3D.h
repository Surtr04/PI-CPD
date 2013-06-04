// ------ FVRecons3D.h ------
// S. CLAIN 2011/10
#ifndef _FVRECONS3D
#define _FVRECONS3D
#include "FVMesh3D.h"
#include "FVStencil.h"
#include "FVCell3D.h"
#include "FVVect.h"
#include "FVDenseM.h"
#include "FVPoint3D.h"
#include "FVPoint4D.h"
#include "FVGaussPoint.h"
#include "FVLib_config.h"
#include "FVTools.h"

class FVRecons3D
{
private:
FVPoint3D<double> _ref_point;
FVVect<double> *_Vertex3DVect,*_Edge3DVect,*_Face3DVect,*_Cell3DVect;    
FVVect<double> *_coef,*_M;
FVStencil * _ptr_s;
FVDenseM<double> *_A,*_Q,*_Adag;
double _evalMean(void *ptr,size_t type,size_t alpha1, size_t alpha2,size_t alpha3); 
double _ref_val;
size_t _degree,_Ncoef,_reconstruction_type;

public:
FVRecons3D()
    {
    //cout<<"using the FVRecons3D  default constructor"<<endl;  fflush(NULL);     
    _ptr_s=NULL;_Vertex3DVect=NULL;_Edge3DVect=NULL;_Face3DVect=NULL;_Cell3DVect=NULL;
    _reconstruction_type= REC_NULL;
    _A=new   FVDenseM<double>; 
    _Q=new   FVDenseM<double>;
    _coef= new FVVect<double>;
    _M=new FVVect<double>;
    _Adag=new   FVDenseM<double>;
    _ref_point=0.; _ref_val=0;_degree=0;_Ncoef=0;_reconstruction_type= REC_NULL;
    }
FVRecons3D(FVStencil *ptr_s)
    {
     //cout<<"using the FVRecons3D constructor with stencil"<<endl;    fflush(NULL);    
    _ptr_s=ptr_s;
    _A=new   FVDenseM<double>; 
    _Q=new   FVDenseM<double>;
    _coef= new FVVect<double>;
    _M=new FVVect<double>;
    _Adag=new   FVDenseM<double>; 
    _ref_point=0;_degree=0;_Ncoef=0;_reconstruction_type= REC_NULL;
    if(ptr_s->getReferenceType()==FVVERTEX3D) _ref_point=((FVVertex3D *)(_ptr_s->getReferenceGeometry()))->coord;
    if(ptr_s->getReferenceType()==FVEDGE3D)   _ref_point=((FVEdge3D *)(_ptr_s->getReferenceGeometry()))->centroid;    
    if(ptr_s->getReferenceType()==FVFACE3D)   _ref_point=((FVFace3D *)(_ptr_s->getReferenceGeometry()))->centroid;
    if(ptr_s->getReferenceType()==FVCELL3D)   _ref_point=((FVCell3D *)(_ptr_s->getReferenceGeometry()))->centroid;    
    }
FVRecons3D(FVStencil *ptr_s, size_t degree)
    {
    //cout<<"using the FVRecons2D constructor with stencil and degress"<<endl;  fflush(NULL);     
    _degree=degree;    
    _Ncoef=((_degree+3)*(_degree+2)*(_degree+1))/6-1;
    _ptr_s=ptr_s;
    _A=new   FVDenseM<double>; 
    _Q=new   FVDenseM<double>;
    _coef= new FVVect<double>;
    _M=new FVVect<double>;
    _Adag=new   FVDenseM<double>; 
    _ref_point=0;
    _reconstruction_type= REC_NULL;
    if(ptr_s->getReferenceType()==FVVERTEX3D) _ref_point=((FVVertex3D *)(_ptr_s->getReferenceGeometry()))->coord;
    if(ptr_s->getReferenceType()==FVEDGE3D)   _ref_point=((FVEdge3D *)(_ptr_s->getReferenceGeometry()))->centroid;    
    if(ptr_s->getReferenceType()==FVFACE3D)   _ref_point=((FVFace3D *)(_ptr_s->getReferenceGeometry()))->centroid;
    if(ptr_s->getReferenceType()==FVCELL3D)   _ref_point=((FVCell3D *)(_ptr_s->getReferenceGeometry()))->centroid;   
    }    
// destructor       
~FVRecons3D(){if(_A) delete(_A); if(_Q) delete(_Q);if(_coef) delete(_coef);if(_M) delete(_M);}  
FVRecons3D(const FVRecons3D & rec); // copy constructor
FVRecons3D & operator =(const  FVRecons3D &rec) // assigment operator
    {
    //cout<<"using the FVRecons3D assigment operator "<<endl; fflush(NULL); 
    _ptr_s=rec._ptr_s;
    _Vertex3DVect=rec._Vertex3DVect;
    _Edge3DVect=rec._Edge3DVect;
    _Face3DVect=rec._Face3DVect;
    _Cell3DVect=rec._Cell3DVect;
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
void setStencil(FVStencil &st){ FVRecons3D::setStencil(&st); }     
void setStencil(FVStencil *ptr_s)
    {
    _ptr_s=ptr_s;
    _ref_point=0;_degree=0;_Ncoef=0;
    if(ptr_s->getReferenceType()==FVVERTEX3D) _ref_point=((FVVertex3D *)(_ptr_s->getReferenceGeometry()))->coord;
    if(ptr_s->getReferenceType()==FVEDGE3D)   _ref_point=((FVEdge3D *)(_ptr_s->getReferenceGeometry()))->centroid;    
    if(ptr_s->getReferenceType()==FVFACE3D)   _ref_point=((FVFace3D *)(_ptr_s->getReferenceGeometry()))->centroid;
    if(ptr_s->getReferenceType()==FVCELL3D)   _ref_point=((FVCell3D *)(_ptr_s->getReferenceGeometry()))->centroid;          
     }
void setStencil(FVStencil &st, size_t degree){ FVRecons3D::setStencil(&st,degree); }      
void setStencil(FVStencil *ptr_s, size_t degree)
    {
    _ptr_s=ptr_s;
    _ref_point=0;   
    _degree=degree; 
    _Ncoef=((_degree+3)*(_degree+2)*(_degree+1))/6-1;
    if(ptr_s->getReferenceType()==FVVERTEX3D) _ref_point=((FVVertex3D *)(_ptr_s->getReferenceGeometry()))->coord;
    if(ptr_s->getReferenceType()==FVEDGE3D)   _ref_point=((FVEdge3D *)(_ptr_s->getReferenceGeometry()))->centroid;    
    if(ptr_s->getReferenceType()==FVFACE3D)   _ref_point=((FVFace3D *)(_ptr_s->getReferenceGeometry()))->centroid;
    if(ptr_s->getReferenceType()==FVCELL3D)   _ref_point=((FVCell3D *)(_ptr_s->getReferenceGeometry()))->centroid;       
     }
FVStencil *getStencil() {return(_ptr_s);}       
//other    
void setPolynomialDegree(size_t degree){_degree=degree;_Ncoef=((_degree+3)*(_degree)*(_degree+1))/6-1;}    
size_t getPolynomialDegree(){return(_degree); } 
void setReferencePoint(FVPoint3D<double> P){_ref_point=P;}
void setVectorVertex3D( FVVect<double> & u){_Vertex3DVect=&u;}
void setVectorEdge3D( FVVect<double> & u){_Edge3DVect=&u;}
void setVectorFace3D( FVVect<double> & u){_Face3DVect=&u;}
void setVectorCell3D( FVVect<double> & u){_Cell3DVect=&u;}
void setReconstructionType(size_t rec_type){_reconstruction_type=rec_type;}
size_t getReconstructionType(){return _reconstruction_type;}
void doConservativeMatrix();
void computeConservativeCoef();
void doNonConservativeMatrix();
void computeNonConservativeCoef();
void doMatrix()
    {
     if(_reconstruction_type==REC_NULL) {cout<<"error construction type not defined"<<endl;exit(0);}          
     if(_reconstruction_type==REC_NON_CONSERVATIVE)  FVRecons3D::doNonConservativeMatrix();
     if(_reconstruction_type==REC_CONSERVATIVE)  FVRecons3D::doConservativeMatrix();            
    }
void computeCoef()
    {
     if(_reconstruction_type==REC_NULL) {cout<<"error construction type not defined"<<endl;exit(0);}          
     if(_reconstruction_type==REC_NON_CONSERVATIVE)  FVRecons3D::computeNonConservativeCoef();
     if(_reconstruction_type==REC_CONSERVATIVE)  FVRecons3D::computeConservativeCoef();            
    }
double ConditioningNumber();
void resetCoef(){if (_coef->size()!=_Ncoef) _coef->resize(_Ncoef);(*_coef)=0.;_ref_val=0.;}
double getValue(FVPoint3D<double> P, size_t degree );    
double getValue(FVPoint3D<double> P){return(FVRecons3D::getValue(P,_degree));}    
FVPoint3D<double> getDerivative(FVPoint3D<double> P, size_t degree);
FVPoint3D<double> getDerivative(FVPoint3D<double> P){return(FVRecons3D::getDerivative(P,_degree));}
FVPoint3D<FVPoint3D<double> >getHessian(FVPoint3D<double> P, size_t degree);
FVPoint3D<FVPoint3D<double> >getHessian(FVPoint3D<double> P){return(FVRecons3D::getHessian(P,_degree));}
void clean()
    {
    _A->resize(0); _Q->resize(0);_coef->resize(0);_M->resize(0);_Adag->resize(0);
    _ptr_s=NULL;_Vertex3DVect=NULL;_Edge3DVect=NULL;_Face3DVect=NULL;_Cell3DVect=NULL;
    _ref_point=0.; _ref_val=0;_degree=0;_Ncoef=0;
        _reconstruction_type= REC_NULL;  
    }   
void show();      
};

FVPoint3D<size_t> alpha3D(size_t k1);
#endif // define _FVRECONS3D




