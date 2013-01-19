#include "FVAdaptative2D.h"

FVAdaptative2D::FVAdaptative2D()  //constructor
{
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++){_ptr_st[i]=NULL;_ptr_rec[i]=NULL;}
_Vertex2DVect=NULL;
_Edge2DVect=NULL;
_Cell2DVect=NULL;
_ptr_m=NULL;
_ptr_c=NULL;
_ptr_e=NULL;
_ptr_v=NULL;
_reference_type=NULL_ENTITY;
}


FVAdaptative2D::~FVAdaptative2D()  //destructor
{
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
     if(_ptr_st[i]) delete _ptr_st[i]; 
     if(_ptr_rec[i]) delete _ptr_rec[i];       
    }    
}

FVAdaptative2D::FVAdaptative2D(const FVAdaptative2D  &ada) // copy constructor
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
}


// clean and show the adaptative class
void FVAdaptative2D::clean()
{
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
     if(_ptr_st[i]) delete _ptr_st[i]; 
     if(_ptr_rec[i]) delete _ptr_rec[i];       
    }     
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++){_ptr_st[i]=NULL;_ptr_rec[i]=NULL;}    
_Vertex2DVect=NULL;
_Edge2DVect=NULL;
_Cell2DVect=NULL;
_ptr_m=NULL;    
_ptr_c=NULL;
_ptr_e=NULL;
_ptr_v=NULL;
_reference_type=NULL_ENTITY;
}
//
void FVAdaptative2D::show()
{
cout<<"===== Adaptative2D===="<<endl;fflush(NULL);
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
    if(_ptr_rec[i]) cout<<"degree "<<i<<" available"<<endl;fflush(NULL);
    } 
    
cout<<"reference element:"<<endl;fflush(NULL);
switch(_reference_type)
    {
    case FVVERTEX2D:
    cout<<"FVVertex2D of label:"<<_ptr_v->label<<endl; fflush(NULL);  
    break;
     case FVEDGE2D:
    cout<<"FVEdge2D of label:"<<_ptr_e->label<<endl;   fflush(NULL);
    break;
    case FVCELL2D:
    cout<<"FVCell2D of label:"<<_ptr_c->label<<endl;  fflush(NULL); 
    break;    
    default:
    cout<<"Reference element has not been defined"<<endl;    
    }
}

// =========== set the polynomial functions ========
// code =0 non code specification
// weight<==, no weight
// without stencil use the cell by default.
void FVAdaptative2D::makePolynomial(size_t d, size_t type,size_t code, double weight)
{
if(d>FVAPAPTATIVE_MAX_DEGREE) return;
if(!_ptr_m) cout<<"Mesh has not been defined"<<endl;
if(_ptr_st[d]) return; // the reconstruction have been done for this degree
// first set the reference geometrical entity
_ptr_st[d]=new FVStencil;
switch(_reference_type)
    {
    case FVVERTEX2D:
    _ptr_st[d]->setReferenceGeometry(_ptr_v);   
    break;
     case FVEDGE2D:
    _ptr_st[d]->setReferenceGeometry(_ptr_e);   
    break;
    case FVCELL2D:
    _ptr_st[d]->setReferenceGeometry(_ptr_c);   
    break;    
    default:
    cout<<"Reference element has not been defined in class FVAdaptative2D"<<endl; exit(0);    
    }   
// do the stencil in function of code and weight

if(code) 
    _ptr_st[d]->addCellStencil(*_ptr_m,(d+1)*(d+2),code);
else
    _ptr_st[d]->addCellStencil(*_ptr_m,(d+1)*(d+2));
    // if weight positive, add weight
if(weight>0)
   {FVCell2D *ptr_cc;FVEdge2D *ptr_ee;
   // ici je dois metre les poids en fonction du type deleemt
    switch(_reference_type)
        {
        case FVVERTEX2D:
        _ptr_v->beginCell();
        while((ptr_cc=_ptr_v->nextCell()))
            {
            _ptr_st[d]->addStencil(ptr_cc,weight);
            }    
        break;
        case FVEDGE2D:
        _ptr_st[d]->addStencil(_ptr_e->leftCell,weight);
        if(_ptr_e->rightCell) _ptr_st[d]->addStencil(_ptr_e->rightCell,weight);
        break;
        case FVCELL2D:
        _ptr_c->beginEdge();   
         while((ptr_ee=_ptr_c->nextEdge()))
            {
            if(ptr_ee->rightCell)
                {
                if(_ptr_c==ptr_ee->rightCell)    
                    _ptr_st[d]->addStencil(ptr_ee->leftCell,weight);
                else
                    _ptr_st[d]->addStencil(ptr_ee->rightCell,weight);  
                }
            }         
        break;    
        default:
        cout<<"Reference element has not been defined in class FVAdaptative2D"<<endl; 
        exit(0); 
        }
    }      
// do re construction and the matrix
_ptr_rec[d]=new FVRecons2D;
_ptr_rec[d]->setStencil(*_ptr_st[d],d);   
_ptr_rec[d]->setReconstructionType(type);
_ptr_rec[d]->doMatrix();  
if(_Vertex2DVect) _ptr_rec[d]->setVectorVertex2D(*_Vertex2DVect);
if(_Edge2DVect)_ptr_rec[d]->setVectorEdge2D(*_Edge2DVect);
if(_Cell2DVect)_ptr_rec[d]->setVectorCell2D(*_Cell2DVect);
}
//
// version with a given stencil
void FVAdaptative2D::makePolynomial(FVStencil &st,size_t d, size_t type)
{
if(d>FVAPAPTATIVE_MAX_DEGREE) return;
if(!_ptr_m) cout<<"Mesh has not been defined"<<endl;
if(_ptr_rec[d]) return; // the reconstruction have been done for this degree
// first set the reference geometrical entity
_ptr_st[d]=new FVStencil;
switch(_reference_type)
    {
    case FVVERTEX2D:
    _ptr_st[d]->setReferenceGeometry(_ptr_v);   
    break;
     case FVEDGE2D:
    _ptr_st[d]->setReferenceGeometry(_ptr_e);   
    break;
    case FVCELL2D:
    _ptr_st[d]->setReferenceGeometry(_ptr_c);   
    break;    
    default:
    cout<<"Reference element has not been defined in class FVAdaptative2D"<<endl; exit(0);    
    }
// set the stencil
*_ptr_st[d]=st;
// do re construction and the matrix
_ptr_rec[d]=new FVRecons2D;
_ptr_rec[d]->setStencil(*_ptr_st[d],d);   
_ptr_rec[d]->setReconstructionType(type);
_ptr_rec[d]->doMatrix();   
if(_Vertex2DVect) _ptr_rec[d]->setVectorVertex2D(*_Vertex2DVect);
if(_Edge2DVect)_ptr_rec[d]->setVectorEdge2D(*_Edge2DVect);
if(_Cell2DVect)_ptr_rec[d]->setVectorCell2D(*_Cell2DVect);
  }


  
  
// set the data vector  
void FVAdaptative2D::setVectorVertex2D( FVVect<double> & u)
{
_Vertex2DVect=&u;
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
    if(_ptr_rec[i]) _ptr_rec[i]->setVectorVertex2D(u);
    }
}
void FVAdaptative2D::setVectorEdge2D( FVVect<double> & u)
{
_Edge2DVect=&u;    
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
    if(_ptr_rec[i]) _ptr_rec[i]->setVectorEdge2D(u);
    }
}
void FVAdaptative2D::setVectorCell2D( FVVect<double> & u)
{
_Cell2DVect=&u;    
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
    if(_ptr_rec[i]) _ptr_rec[i]->setVectorCell2D(u);
    }
}

//  compute or reset coefficient
void FVAdaptative2D::computeCoef()
{
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
    if(_ptr_rec[i]) _ptr_rec[i]->computeCoef();
    }
}
void FVAdaptative2D::resetCoef()
{
for(size_t i=0;i<=FVAPAPTATIVE_MAX_DEGREE;i++)
    {
    if(_ptr_rec[i]) _ptr_rec[i]->resetCoef();
    }
}


// return value, derivative and Hessian matrix
double FVAdaptative2D::getValue(FVPoint2D<double> P, size_t d)
{   
if(!_ptr_rec[d]) {cout<<"Alert, polynomial od degree "<<d<<" is not defined"<<endl; exit(0);}
return(_ptr_rec[d]->getValue(P));
}

FVPoint2D<double> FVAdaptative2D::getDerivative(FVPoint2D<double> P, size_t d)
{
if(!_ptr_rec[d]) {cout<<"Alert, polynomial od degree "<<d<<" is not defined"<<endl; exit(0);}    
return(_ptr_rec[d]->getDerivative(P));
}
FVPoint2D<FVPoint2D<double> > FVAdaptative2D::getHessian(FVPoint2D<double> P, size_t d)
{
if(!_ptr_rec[d]) {cout<<"Alert, polynomial od degree "<<d<<" is not defined"<<endl; exit(0);}    
return(_ptr_rec[d]->getHessian(P));   
}


