// ------ FVRecons1D.cpp ------
// S. CLAIN 2011/11
#include "FVRecons1D.h"



FVPoint1D<size_t> alpha1D(size_t k)
{
return(k+1);
}

FVRecons1D::FVRecons1D(const FVRecons1D & rec) // copy constructor
{
//cout<<"using the FVRecons1D copy constructor"<<endl;  fflush(NULL); 
_ptr_s=rec._ptr_s;
_Vertex1DVect=rec._Vertex1DVect;
_Cell1DVect=rec._Cell1DVect;
_ref_point=rec._ref_point; 
_ref_val=rec._ref_val;
_degree=rec._degree;
_Ncoef=rec._Ncoef; 
_reconstruction_type=rec._reconstruction_type;
//
_A=new   FVDenseM<double>; 
_Adag=new   FVDenseM<double>;            
_Q=new   FVDenseM<double>;
_coef= new FVVect<double>; 
_M=new FVVect<double>;
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
}  
             
double FVRecons1D::_evalMean(void *ptr,size_t type,size_t alpha)
{
FVPoint1D<double> P1,P2,P;
double sum;  
FVPoint2D<double> GP;
FVGaussPoint1D GPCell;
switch(type)
   {
    case FVVERTEX1D:
    P=((FVVertex1D *)ptr)->coord;
    return(FVPow(P.x-_ref_point.x,alpha));    
    break;
    case FVCELL1D:
    sum=0.;    
    P1=((FVCell1D *)ptr)->firstVertex->coord;
    P2=((FVCell1D *)ptr)->secondVertex->coord; 
    GP=GPCell.getPoint(5,1);
    P=GP.x*P1+GP.y*P2;
    sum+=GPCell.getWeight(5,1)*FVPow(P.x-_ref_point.x,alpha);
    GP=GPCell.getPoint(5,2);
    P=GP.x*P1+GP.y*P2;
    sum+=GPCell.getWeight(5,2)*FVPow(P.x-_ref_point.x,alpha);
    GP=GPCell.getPoint(5,3);
    P=GP.x*P1+GP.y*P2;
    sum+=GPCell.getWeight(5,3)*FVPow(P.x-_ref_point.x,alpha);
    return(sum);
    break;     
    default:
    cout<<"WARNING: unknow geometrical entity in FVReconstruction1D"<<endl;    
    return(0); 
    break;     
   }
return(0);  
}
// Matrix associated to reconstruction with the conservative reference value 
void FVRecons1D::doConservativeMatrix()
{
if(_reconstruction_type!=REC_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}  
void *ptr;
double weight,h;
FVVect<double> MatCond(_Ncoef);
#ifdef _DEBUGS
if(_ptr_s->nb_geometry<_Ncoef-1)
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"Not enough entities for the reconstruction"<<endl;
#endif

         // create the matrix
_A->resize(_ptr_s->getNbGeometry(),_Ncoef);
_Adag->resize(_Ncoef,_ptr_s->getNbGeometry());
_Q->resize(_ptr_s->getNbGeometry());
_M->resize(_Ncoef); 
FVPoint1D<size_t> al;
size_t alpha1;
//  for the conditioning
h=1;
if(_ptr_s->getReferenceType()==FVCELL1D) h=((FVCell1D *)_ptr_s->getReferenceGeometry())->length;
//
for(size_t j=0;j<_Ncoef;j++)
    { 
     al=alpha1D(j);   
     alpha1=al.x;  
     (*_M)[j]=FVRecons1D::_evalMean(_ptr_s->getReferenceGeometry(),_ptr_s->getReferenceType(),alpha1);
     MatCond[j]=1./FVPow(h,alpha1);     
     _ptr_s->beginGeometry();
     while((ptr=_ptr_s->nextGeometry()))
          {
          size_t i=_ptr_s->getIndex(); 
          weight=(*_ptr_s->weight)[i]*MatCond[j]; 
          weight*=FVRecons1D::_evalMean(ptr,_ptr_s->getType(),alpha1)-(*_M)[j];
          //cout<<"alpha="<<alpha1<<" gives coefficient="<<weight<<endl;     
          //cout<<"alpha="<<alpha1<<" ecart "<<((FVVertex1D *)ptr)->coord.x-_ref_point.x<<" gives coefficient="<<weight<<endl;
          _A->setValue(i,j,weight);
          }
    }
//_A->QRFactorize(*_Q);  
_A->DagMatrix(*_Adag);_Adag->leftMatrixMult(MatCond);
}

// Matrix associated to reconstruction without the conservative reference value 
void FVRecons1D::doNonConservativeMatrix() 
{
if(_reconstruction_type!=REC_NON_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}     
void *ptr;
double weight,h;
FVVect<double> MatCond(_Ncoef+1);
#ifdef _DEBUGS
if(_ptr_s->nb_geometry<_Ncoef)
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"Not enough entities for the reconstruction"<<endl;
#endif

         // create the matrix
_A->resize(_ptr_s->getNbGeometry(),_Ncoef+1);
_Adag->resize(_Ncoef+1,_ptr_s->getNbGeometry());
_Q->resize(_ptr_s->getNbGeometry());
_M->resize(_Ncoef); 
FVPoint1D<size_t> al;
size_t alpha1;
//  for the conditioning
h=1;
if(_ptr_s->getReferenceType()==FVCELL1D) h=((FVCell1D *)_ptr_s->getReferenceGeometry())->length;
//
_ptr_s->beginGeometry();
while((ptr=_ptr_s->nextGeometry()))
      {
          _A->setValue(_ptr_s->getIndex(),0,(*_ptr_s->weight)[_ptr_s->getIndex()]);
      }
MatCond[0]=1;       
for(size_t j=0;j<_Ncoef;j++)
    { 
     al=alpha1D(j);   
     alpha1=al.x;  
     (*_M)[j]=0;
     MatCond[j+1]=1./FVPow(h,alpha1);
     _ptr_s->beginGeometry();
     while((ptr=_ptr_s->nextGeometry()))
          {
          size_t i=_ptr_s->getIndex();
          weight=(*_ptr_s->weight)[i]*MatCond[j+1];  
          weight*=  FVRecons1D::_evalMean(ptr,_ptr_s->getType(),alpha1);
          _A->setValue(i,j+1,weight); 
          }
    } 
//_A->QRFactorize(*_Q);  
_A->DagMatrix(*_Adag); _Adag->leftMatrixMult(MatCond);
}
// Polynomial coeffient  with the conservative reference value 
void FVRecons1D::computeConservativeCoef()
{
if(_reconstruction_type!=REC_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);} 
FVVect<double> B(_ptr_s->getNbGeometry()),X(_ptr_s->getNbGeometry()); 
void *ptr;
double  geo_val=0;
_ref_val=0;
size_t k,i;
switch(_ptr_s->getReferenceType())
  {
    case FVVERTEX1D:
    k= ( (FVVertex1D *) _ptr_s->getReferenceGeometry())->label-1; 
    #ifdef _DEBUGS
    if(!_Vertex1DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex1DVect is empty"<<endl;
         break;
         }
    #endif
    _ref_val=(*_Vertex1DVect)[k];
    break;
    case FVCELL1D:
    #ifdef _DEBUGS
    if(!_Cell1DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell1DVect is empty"<<endl;
         break;
         }
    #endif        
    k=  ((FVCell1D *) _ptr_s->getReferenceGeometry())->label-1; 
    _ref_val=(*_Cell1DVect)[k];
  } 

_ptr_s->beginGeometry();
while((ptr=_ptr_s->nextGeometry()))
    {
    switch(_ptr_s->getType())
       {
        case FVVERTEX1D:
        #ifdef _DEBUGS
        if(!_Vertex1DVect)
             {
             cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex1DVect is empty"<<endl;
             break;
             }
       #endif      
       k= ((FVVertex1D *) ptr)->label-1; 
       geo_val=(*_Vertex1DVect)[k];
       break; 
       case FVCELL1D:  
       #ifdef _DEBUGS           
       if(!_Cell1DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell1DVect is empty"<<endl;
           break;
           }
       #endif 
       k=  ((FVCell1D *) ptr)->label-1;  
       geo_val=(*_Cell1DVect)[k];
       } 
    i=_ptr_s->getIndex();
    B[i]=(*_ptr_s->weight)[i];  
    B[i]*=geo_val-_ref_val;
    }       
//_Q->Mult(B, X);
//_A->PartialBackwardSubstitution(X);
_Adag->Mult(B, X);
// create the vector
if (_coef->size()!=_Ncoef) _coef->resize(_Ncoef);
for(size_t i=0;i<_Ncoef;i++) (*_coef)[i]=X[i];
}
// Polynomial coeffient  without the conservative reference value 
void FVRecons1D::computeNonConservativeCoef()
{
if(_reconstruction_type!=REC_NON_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}    
FVVect<double> B(_ptr_s->getNbGeometry()),X(_ptr_s->getNbGeometry()); 
void *ptr;
double  geo_val=0;
_ref_val=0;
size_t k,i;

_ptr_s->beginGeometry();
while((ptr=_ptr_s->nextGeometry()))
    {
    switch(_ptr_s->getType())
       {
        case FVVERTEX1D:
        #ifdef _DEBUGS
        if(!_Vertex1DVect)
             {
             cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex1DVect is empty"<<endl;
             break;
             }
       #endif      
       k= ((FVVertex1D *) ptr)->label-1; 
       geo_val=(*_Vertex1DVect)[k];
       break; 
       case FVCELL1D:  
       #ifdef _DEBUGS           
       if(!_Cell1DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell1DVect is empty"<<endl;
           break;
           }
       #endif 
       k=  ((FVCell1D *) ptr)->label-1;  
       geo_val=(*_Cell1DVect)[k];
       } 
  
    B[_ptr_s->getIndex()]=geo_val;    
    i=_ptr_s->getIndex();
    B[i]=(*_ptr_s->weight)[i];  
    B[i]*=geo_val;
    }   
_Adag->Mult(B, X);   
//_Q->Mult(B, X);
//_A->PartialBackwardSubstitution(X);
// create the vector
if (_coef->size()!=_Ncoef) _coef->resize(_Ncoef);
for(size_t i=0;i<_Ncoef;i++) (*_coef)[i]=X[i+1];
_ref_val=X[0];
}
// compute the conditioning numer of the R matrix 
double FVRecons1D::ConditioningNumber()
{
double Min=1.e20,Max=0,val;
if (_A->nb_cols==0) return(-1.0);
for(size_t i=0;i<_A->nb_cols;i++)
    {
    val=abs(_A->getValue(i,i));
    if(Min>val) Min=val;
    if(Max<val) Max=val;
    }
if (Min>0) return(Max/Min);
return(1.0e20);    
}
double FVRecons1D::getValue(FVPoint1D<double> P,size_t degree)
{
double val=_ref_val;
size_t k,Ncoef;
FVPoint1D<size_t> al;
size_t alpha1;
degree=min(degree,_degree);
Ncoef=degree;
//cout<<"valeur de reference:"<<val<<endl;
for(k=0;k<Ncoef;k++)
    {
    al=alpha1D(k);   
    alpha1=al.x;  
    val+=(*_coef)[k]*(FVPow(P.x-_ref_point.x,alpha1)-(*_M)[k]);
    //cout<<"coef "<<k<<"="<<(*_coef)[k]<<" alapuissance "<<alpha1<<" et M="<<(*_M)[k]<<endl;
    }
return(val);
}
// comopute the derivative
FVPoint1D<double> FVRecons1D::getDerivative(FVPoint1D<double> P, size_t degree) 
{
FVPoint1D<double> val=0.;
size_t k;
FVPoint1D<size_t> al;
size_t alpha1,Ncoef;
degree=min(degree,_degree);
Ncoef=degree;
for(k=0;k<Ncoef;k++)
    {
    al=alpha1D(k);   
    alpha1=al.x;  
    val.x+=(*_coef)[k]*alpha1*FVPow(P.x-_ref_point.x,alpha1-1);
    //cout<<"coef "<<k<<"="<<alpha1*(*_coef)[k]<<" alapuissance "<<alpha1-1<<" et M="<<(*_M)[k]<<endl;
    }
return(val);
}

FVPoint1D<FVPoint1D<double> > FVRecons1D::getHessian(FVPoint1D<double> P, size_t degree)
{
    
FVPoint1D<FVPoint1D<double> >val;
val.x.x=0.;
size_t k;
FVPoint1D<size_t> al;
size_t alpha1,Ncoef;
degree=min(degree,_degree);
Ncoef=degree;
for(k=0;k<Ncoef;k++)
    {
    al=alpha1D(k);   
    alpha1=al.x;  
    if(alpha1>1)
        val.x.x+=(*_coef)[k]*alpha1*(alpha1-1)*FVPow(P.x-_ref_point.x,alpha1-2);
    //cout<<"coef "<<k<<"="<<alpha1*(*_coef)[k]<<" alapuissance "<<alpha1-1<<" et M="<<(*_M)[k]<<endl;
    }
return(val);
}
void FVRecons1D::show()
{
cout<<"FVRecons1D of entity "<<_ptr_s->getType()<<endl;
    cout<<"grau [0], coef:"<<_ref_val<<" and M.0"<<endl;
for(size_t k=0;k<_Ncoef;k++)
    {
    cout<<"grau ["<<k+1<<"], coef:"<<(*_coef)[k]<<" and M."<<(*_M)[k]<<endl;
    }
}





