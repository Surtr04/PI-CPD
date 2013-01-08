// ------ FVFastRecons2D.cpp ------
// S. CLAIN 2012/01
#include "FVFastRecons2D.h"


FVFastRecons2D::FVFastRecons2D()  // constructor
{
_AValue=NULL;
_ADerivative=NULL;
_ptr_s=NULL;_Vertex2DVect=NULL;_Edge2DVect=NULL;_Cell2DVect=NULL;
_list_Point=new vector< FVPoint2D<double> *>;
_list_Point->resize(0); 
_ref_point=0.;_degree=0; _nb_row=_nb_col=0.;
_reconstruction_type= REC_NULL;
}
FVFastRecons2D::~FVFastRecons2D() //destructor
{

if(_AValue){delete _AValue; _AValue=NULL;}
if(_ADerivative){delete _ADerivative; _ADerivative=NULL;}
if(_list_Point){ delete _list_Point;_list_Point=NULL;}
}
FVFastRecons2D::FVFastRecons2D(const FVFastRecons2D & frec) // copy constructor
{ 
_ptr_s=frec._ptr_s;
_Vertex2DVect=frec._Vertex2DVect;
_Edge2DVect=frec._Edge2DVect;
_Cell2DVect=frec._Cell2DVect; 
_ref_point=frec._ref_point; 
_degree=frec._degree;
 _nb_row=frec._nb_row;
 _nb_col=frec._nb_col;
 
_reconstruction_type=frec._reconstruction_type;
if(frec._AValue)  {_AValue=new FVVect<double>; }// il manque le resize et la copy
     else {_AValue=NULL;}
if(frec._ADerivative)  {_ADerivative=new  FVVect<FVPoint2D<double> >;}
     else {_ADerivative=NULL;}
if(frec._list_Point) {_list_Point=new vector< FVPoint2D<double> *>;}
     else {_list_Point=NULL;}  
   
}
FVFastRecons2D & FVFastRecons2D::operator =(const  FVFastRecons2D &frec) // assigment operator
{
_ptr_s=frec._ptr_s;
_Vertex2DVect=frec._Vertex2DVect;
_Edge2DVect=frec._Edge2DVect;
_Cell2DVect=frec._Cell2DVect; 
_ref_point=frec._ref_point; 
_degree=frec._degree; 
 _nb_row=frec._nb_row;
 _nb_col=frec._nb_col;
_reconstruction_type=frec._reconstruction_type;
if(frec._AValue)  {_AValue=new FVVect<double>; }// il manque le resize et la copy
     else {_AValue=NULL;}
if(frec._ADerivative)  {_ADerivative=new  FVVect<FVPoint2D<double> >;}
     else {_ADerivative=NULL;}
if(frec._list_Point) {_list_Point=new vector< FVPoint2D<double> *>;}
     else {_list_Point=NULL;}    
return *this;
}
void FVFastRecons2D::clean()
{
if(_AValue){delete _AValue; _AValue=NULL;}
if(_ADerivative){delete _ADerivative; _ADerivative=NULL;}
_ptr_s=NULL;_Vertex2DVect=NULL;_Edge2DVect=NULL;_Cell2DVect=NULL;
_list_Point->resize(0);
_ref_point=0.;_degree=0; _nb_row=_nb_col=0.;
_reconstruction_type= REC_NULL;
}
// setStencil     
void FVFastRecons2D::setStencil(FVStencil *ptr_s)
{
_ptr_s=ptr_s;
_ref_point=0;_degree=0;_Ncoef=0;
if(ptr_s->getReferenceType()==FVVERTEX2D) 
    _ref_point=((FVVertex2D *)(_ptr_s->getReferenceGeometry()))->coord;
if(ptr_s->getReferenceType()==FVEDGE2D)   
    _ref_point=((FVEdge2D *)(_ptr_s->getReferenceGeometry()))->centroid;    
if(ptr_s->getReferenceType()==FVCELL2D)   
    _ref_point=((FVCell2D *)(_ptr_s->getReferenceGeometry()))->centroid;  
}
void FVFastRecons2D::setStencil(FVStencil *ptr_s, size_t degree)
{
_ptr_s=ptr_s;
_ref_point=0;   
_degree=degree; 
_Ncoef=((_degree+2)*(_degree+1))/2-1;
if(ptr_s->getReferenceType()==FVVERTEX2D) 
    _ref_point=((FVVertex2D *)(_ptr_s->getReferenceGeometry()))->coord;
if(ptr_s->getReferenceType()==FVEDGE2D)   
    _ref_point=((FVEdge2D *)(_ptr_s->getReferenceGeometry()))->centroid;    
if(ptr_s->getReferenceType()==FVCELL2D)   
    _ref_point=((FVCell2D *)(_ptr_s->getReferenceGeometry()))->centroid;   
}

void FVFastRecons2D::doMatrix() 
{
if(_reconstruction_type==REC_NULL) return;

FVVect<double> Vertex2DVect(_ptr_m->getNbVertex());Vertex2DVect=0.;
FVVect<double> Edge2DVect(_ptr_m->getNbEdge());Edge2DVect=0.;
FVVect<double> Cell2DVect(_ptr_m->getNbCell());Cell2DVect=0.;
FVRecons2D rec(_ptr_s,_degree);
rec.setVectorVertex2D(Vertex2DVect);
rec.setVectorEdge2D(Edge2DVect);
rec.setVectorCell2D(Cell2DVect);
rec.setReconstructionType(_reconstruction_type);
doMatrix();
FVVertex2D *ptr_v;
FVEdge2D *ptr_e;
FVCell2D *ptr_c;
//
if(_reconstruction_type==REC_CONSERVATIVE) 
    {
     _nb_col=_ptr_s->getNbGeometry()+1;
     _nb_row=_list_Point->size(); 
    }
if(_reconstruction_type==REC_NON_CONSERVATIVE)  
    {
     _nb_col=_ptr_s->getNbGeometry();
     _nb_row=_list_Point->size();  
    }   
_AValue->resize(_nb_row*_nb_col);
_ADerivative->resize(_nb_row*_nb_col);
// do the reconstruction
//rec.setStentil(*_ptr_s);
for(size_t j=0;j<_nb_col;j++)
    {
    if(_ptr_s->getType(j)==FVVERTEX2D) 
        {
         ptr_v=(FVVertex2D *) _ptr_s->getGeometry(j);   
         Vertex2DVect[ptr_v->label-1]=1;   
        }
    if(_ptr_s->getType(j)==FVEDGE2D) 
        {
         ptr_e=(FVEdge2D *) _ptr_s->getGeometry(j);   
         Edge2DVect[ptr_e->label-1]=1;   
        }        
    if(_ptr_s->getType(j)==FVCELL2D) 
        {
         ptr_c=(FVCell2D *) _ptr_s->getGeometry(j);   
         Cell2DVect[ptr_c->label-1]=1;   
        } 
    rec.computeCoef();    
    for(size_t i=0;i<_nb_row;i++)
        {
        // compute all the coeff for the diferent point 
        
        (*_AValue)[i*_nb_row+j]=rec.getValue(*(*_list_Point)[j]);
        (*_ADerivative)[i*_nb_row+j]=rec.getDerivative(*(*_list_Point)[j]);
        }
    if(_ptr_s->getType(j)==FVVERTEX2D) 
        {
         ptr_v=(FVVertex2D *) _ptr_s->getGeometry(j);   
         Vertex2DVect[ptr_v->label-1]=0;   
        }
    if(_ptr_s->getType(j)==FVEDGE2D) 
        {
         ptr_e=(FVEdge2D *) _ptr_s->getGeometry(j);   
         Edge2DVect[ptr_e->label-1]=0;   
        }        
    if(_ptr_s->getType(j)==FVCELL2D) 
        {
         ptr_c=(FVCell2D *) _ptr_s->getGeometry(j);   
         Cell2DVect[ptr_c->label-1]=0;   
        }         
    }
    
}
double FVFastRecons2D::getValue(size_t i)
{
double val=0,aux;
FVVertex2D *ptr_v;
FVEdge2D *ptr_e;
FVCell2D *ptr_c;
for(size_t j=0;j<_nb_col;j++)
    {
    if(_ptr_s->getType(j)==FVVERTEX2D) 
        {
         ptr_v=(FVVertex2D *) _ptr_s->getGeometry(j);   
         aux= (*_Vertex2DVect)[ptr_v->label-1];   
        }
    if(_ptr_s->getType(j)==FVEDGE2D) 
        {
         ptr_e=(FVEdge2D *) _ptr_s->getGeometry(j);   
         aux= (*_Edge2DVect)[ptr_e->label-1];   
        }        
    if(_ptr_s->getType(j)==FVCELL2D) 
        {
         ptr_c=(FVCell2D *) _ptr_s->getGeometry(j);   
         aux= (*_Cell2DVect)[ptr_c->label-1];   
        }        
    val+= (*_AValue)[i*_nb_row+j]*aux;   
    }
return(val);    
} 
FVPoint2D<double> FVFastRecons2D::getDerivative(size_t i)
{
FVPoint2D<double> Dval=0;
double aux;
FVVertex2D *ptr_v;
FVEdge2D *ptr_e;
FVCell2D *ptr_c;
for(size_t j=0;j<_nb_col;j++)
    {
    if(_ptr_s->getType(i)==FVVERTEX2D) 
        {
         ptr_v=(FVVertex2D *) _ptr_s->getGeometry(i);   
         aux= (*_Vertex2DVect)[ptr_v->label-1];   
        }
    if(_ptr_s->getType(i)==FVEDGE2D) 
        {
         ptr_e=(FVEdge2D *) _ptr_s->getGeometry(i);   
         aux= (*_Edge2DVect)[ptr_e->label-1];   
        }        
    if(_ptr_s->getType(i)==FVCELL2D) 
        {
         ptr_c=(FVCell2D *) _ptr_s->getGeometry(i);   
         aux= (*_Cell2DVect)[ptr_c->label-1];   
        }        
    Dval+= (*_ADerivative)[i*_nb_row+j]*aux;   
    }
return(Dval);
}