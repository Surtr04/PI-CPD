// ------ FVRecons2D.cpp ------
// S. CLAIN 2011/10
#include "FVRecons2D.h"



FVPoint2D<size_t> alpha2D(size_t k)
{
FVPoint2D<size_t> alpha;
size_t d=1;
if(k>1)  d+=1;
if(k>4)  d+=1;
if(k>8)  d+=1;
if(k>13) d+=1;
alpha.x=(((d+1)*(d+2))/2-(k+2));
alpha.y=d-alpha.x;
return(alpha);
}


FVRecons2D::FVRecons2D(const FVRecons2D & rec) // copy constructor
{
//cout<<"using the FVRecons2D copy constructor"<<endl;  fflush(NULL);     
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
_A=new   FVDenseM<double>; 
_Adag=new   FVDenseM<double>;
if(_Adag==NULL){cout<<"problem with _Adag allocation memory in copy constructor"<<endl;}
_Q=new   FVDenseM<double>;
_coef= new FVVect<double>;
_M=new FVVect<double>;
if(_M==NULL){cout<<"problem with _M allocation memory in copy constructor"<<endl;}
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
if(_Adag==NULL){cout<<"problem with _Adag allocation memory in copy constructor"<<endl;}
}  

void FVRecons2D::checkMemory()
{
bool ok=true; 
if(_A==NULL){cout<<"problem with _A allocation memory"<<endl; ok=false;} 
if(_Q==NULL){cout<<"problem with _Q allocation memory"<<endl;ok=false;}    
if(_Adag==NULL){cout<<"problem with _Adag allocation memory"<<endl;ok=false;}    
if(_coef==NULL){cout<<"problem with _coef allocation memory"<<endl;ok=false;}    
if(_M==NULL){cout<<"problem with _M allocation memory "<<endl;ok=false;}
cout<<"ok="<<ok<<endl;
}
// compute mean value (x-c_x)^alpha1(y-c_y)^alpha2 on the geometrical entity
double FVRecons2D::_evalMean(void *ptr,size_t type,size_t alpha1,size_t alpha2)
{
FVPoint2D<double> P1,P2,P;
double sum,S,S_global,aux;  
sum=0.;
FVPoint2D<double> GPEdge;
FVPoint3D<double> GPCell;
FVGaussPoint1D G1D;
FVGaussPoint2D G2D;
// novas variáveis
FVCell2D *ptr_c;
FVEdge2D *ptr_e;
FVVertex2D *ptr_v1,*ptr_v2;
FVPoint2D<double> centroid;

switch(type)
   {
    case FVVERTEX2D:
    P=((FVVertex2D *)ptr)->coord;
    return(FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2));    
    break;
    case FVEDGE2D:
    P1=((FVEdge2D *)ptr)->firstVertex->coord;
    P2=((FVEdge2D *)ptr)->secondVertex->coord; 
    GPEdge=G1D.getPoint(5,1);
    P=GPEdge.x*P1+GPEdge.y*P2;
    sum+=G1D.getWeight(5,1)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2);
    GPEdge=G1D.getPoint(5,2);
    P=GPEdge.x*P1+GPEdge.y*P2;
    sum+=G1D.getWeight(5,2)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2);
    GPEdge=G1D.getPoint(5,3);
    P=GPEdge.x*P1+GPEdge.y*P2;
    sum+=G1D.getWeight(5,3)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2);    
    return(sum); 
    break; 
    //
    case FVCELL2D:
    ptr_c=((FVCell2D *)ptr);
    ptr_c->beginEdge();
    centroid=ptr_c->centroid; 
    S_global=0;
    while((ptr_e=ptr_c->nextEdge()))
        {
        ptr_v1=ptr_e->firstVertex;
        ptr_v2=ptr_e->secondVertex;
        S=Det(ptr_v1->coord-centroid,ptr_v2->coord-centroid)*0.5;
        if(S<0) S*=-1.;
        aux=0;
        for (size_t i=1;i<=G2D.getNbPoint(5);i++)
             { 
               GPCell=G2D.getPoint(5,i);
               P=GPCell.x*ptr_v1->coord+GPCell.y*ptr_v2->coord+GPCell.z*centroid;
               aux+=G2D.getWeight(5,i)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2);
             }    
         sum+=aux*S;
         S_global+=S;
         }
    return(sum/S_global);     
    break;
    default:
    cout<<"WARNING: unknown geometrical entity in FVReconstruction2D, found"<<type<<endl;    
    return(0); 
    break;    
   }
return(0);  
}
// Matrix associated to reconstruction with the conservative reference value 
void FVRecons2D::doConservativeMatrix()
{
if(_reconstruction_type!=REC_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}  
void *ptr;
double weight,h;
FVVect<double> MatCond(_Ncoef);
#ifdef _DEBUGS
if(_ptr_s->nb_geometry<Ncoef-1)
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"Not enough entities for the reconstruction"<<endl;
#endif
         // create the matrix
_A->resize(_ptr_s->getNbGeometry(),_Ncoef);
if(_Adag==NULL){cout<<"problem with copy constructor"<<endl;}
_Adag->resize(_Ncoef,_ptr_s->getNbGeometry());
_Q->resize(_ptr_s->getNbGeometry());
_M->resize(_Ncoef);
FVPoint2D<size_t> al;
size_t alpha1,alpha2;
//  for the conditioning
h=1;
if(_ptr_s->getReferenceType()==FVEDGE2D) h=((FVEdge2D *)_ptr_s->getReferenceGeometry())->length;
if(_ptr_s->getReferenceType()==FVCELL2D) h=sqrt(((FVCell2D *)_ptr_s->getReferenceGeometry())->area);
//
for(size_t j=0;j<_Ncoef;j++)
    { 
     al=alpha2D(j);   
     alpha1=al.x;alpha2=al.y;  
     (*_M)[j]=FVRecons2D::_evalMean(_ptr_s->getReferenceGeometry(),_ptr_s->getReferenceType(),alpha1,alpha2);
     MatCond[j]=1./FVPow(h,alpha1+alpha2);
     _ptr_s->beginGeometry();
     while((ptr=_ptr_s->nextGeometry()))
          {
          size_t i=_ptr_s->getIndex(); 
          weight=(*_ptr_s->weight)[i]*MatCond[j]; 
          weight*=FVRecons2D::_evalMean(ptr,_ptr_s->getType(),alpha1,alpha2)-(*_M)[j];
          _A->setValue(i,j,weight);
          }
    }
//cout<<"the matrix before the decomposition"<<endl;    
//_A->show();    
//_A->QRFactorize(*_Q);  
_A->DagMatrix(*_Adag);_Adag->leftMatrixMult(MatCond);
}
// Matrix associated to reconstruction without the conservative reference value 
void FVRecons2D::doNonConservativeMatrix()
{
if(_reconstruction_type!=REC_NON_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}  
void *ptr;
double weight,h;
FVVect<double> MatCond(_Ncoef+1);
#ifdef _DEBUGS
if(_ptr_s->nb_geometry<Ncoef)
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"Not enough entities for the reconstruction"<<endl;
#endif
         // create the matrix
_A->resize(_ptr_s->getNbGeometry(),_Ncoef+1);
_Adag->resize(_Ncoef+1,_ptr_s->getNbGeometry());
_Q->resize(_ptr_s->getNbGeometry());
_M->resize(_Ncoef); 
FVPoint2D<size_t> al;
size_t alpha1,alpha2;
//  for the conditioning
h=1;
if(_ptr_s->getReferenceType()==FVEDGE2D) h=((FVEdge2D *)_ptr_s->getReferenceGeometry())->length;
if(_ptr_s->getReferenceType()==FVCELL2D) h=sqrt(((FVCell2D *)_ptr_s->getReferenceGeometry())->area);
//
_ptr_s->beginGeometry();
while((ptr=_ptr_s->nextGeometry()))
      {
          _A->setValue(_ptr_s->getIndex(),0,(*_ptr_s->weight)[_ptr_s->getIndex()]);
      }
MatCond[0]=1;     
for(size_t j=0;j<_Ncoef;j++)
    {  
     al=alpha2D(j);   
     alpha1=al.x;alpha2=al.y;  
     (*_M)[j]=0;
     MatCond[j+1]=1./FVPow(h,alpha1+alpha2);
     _ptr_s->beginGeometry();
     while((ptr=_ptr_s->nextGeometry()))
          {
          size_t i=_ptr_s->getIndex();
          weight=(*_ptr_s->weight)[i]*MatCond[j+1];  
          weight*=  FVRecons2D::_evalMean(ptr,_ptr_s->getType(),alpha1,alpha2);
          _A->setValue(i,j+1,weight);
          }
    }
//_A->QRFactorize(*_Q);  
_A->DagMatrix(*_Adag); _Adag->leftMatrixMult(MatCond);
}


// Polynomial coeffient  with the conservative reference value 
void FVRecons2D::computeConservativeCoef()
{
if(_reconstruction_type!=REC_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}      
FVVect<double> B(_ptr_s->getNbGeometry()),X(_ptr_s->getNbGeometry()); 
void *ptr;
double  geo_val=0;
_ref_val=0;
size_t i,k;
switch(_ptr_s->getReferenceType())
  {
    case FVVERTEX2D:
    #ifdef _DEBUGS
    if(!_Vertex2DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex2DVect is empty"<<endl;
         break;
         }
    #endif
    k= ( (FVVertex2D *) _ptr_s->getReferenceGeometry())->label-1; 
    _ref_val=(*_Vertex2DVect)[k];
    break;
    case FVEDGE2D:
    #ifdef _DEBUGS
    if(!_Edge2DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Edge2DVect is empty"<<endl;
         break;
         }
    #endif
    k=( (FVEdge2D *) _ptr_s->getReferenceGeometry())->label-1;     
    _ref_val=(*_Edge2DVect)[k];    
    break; 
    case FVCELL2D:
    #ifdef _DEBUGS
    if(!_Cell2DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell2DVect is empty"<<endl;
         break;
         }
    #endif        
    k=  ((FVCell2D *) _ptr_s->getReferenceGeometry())->label-1; 
    _ref_val=(*_Cell2DVect)[k];
  }
_ptr_s->beginGeometry();  
while((ptr=_ptr_s->nextGeometry()))
    {
    switch(_ptr_s->getType())
       {
        case FVVERTEX2D:
        #ifdef _DEBUGS
        if(!_Vertex2DVect)
             {
             cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex2DVect is empty"<<endl;
             break;
             }
       #endif   
       k= ((FVVertex2D *) ptr)->label-1; 
       geo_val=(*_Vertex2DVect)[k];
       break;
       case FVEDGE2D:       
       #ifdef _DEBUGS
       if(!_Edge2DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Edge2DVect is empty"<<endl;
           break;
           }
       #endif 
       k=((FVEdge2D *) ptr)->label-1;
       geo_val=(*_Edge2DVect)[k];    
       break; 
       case FVCELL2D:         
       #ifdef _DEBUGS           
       if(!_Cell2DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell2DVect is empty"<<endl;
           break;
           }
       #endif    
       k=  ((FVCell2D *) ptr)->label-1;  
       geo_val=(*_Cell2DVect)[k];
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
void FVRecons2D::computeNonConservativeCoef()
{ 
if(_reconstruction_type!=REC_NON_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}     
FVVect<double> B(_ptr_s->getNbGeometry()),X(_ptr_s->getNbGeometry()); 
void *ptr;
double  geo_val=0;
size_t k,i;

_ptr_s->beginGeometry();  
while((ptr=_ptr_s->nextGeometry()))
    {
    switch(_ptr_s->getType())
       {
        case FVVERTEX2D:
        #ifdef _DEBUGS
        if(!_Vertex2DVect)
             {
             cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex2DVect is empty"<<endl;
             break;
             }
       #endif   
       k= ((FVVertex2D *) ptr)->label-1; 
       geo_val=(*_Vertex2DVect)[k];
       break;
       case FVEDGE2D:       
       #ifdef _DEBUGS
       if(!_Edge2DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Edge2DVect is empty"<<endl;
           break;
           }
       #endif 
       k=((FVEdge2D *) ptr)->label-1;
       geo_val=(*_Edge2DVect)[k];    
       break; 
       case FVCELL2D:         
       #ifdef _DEBUGS           
       if(!_Cell2DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell2DVect is empty"<<endl;
           break;
           }
       #endif    
       k=  ((FVCell2D *) ptr)->label-1;  
       geo_val=(*_Cell2DVect)[k];
       }  
    i=_ptr_s->getIndex();
    B[i]=(*_ptr_s->weight)[i];  
    B[i]*=geo_val;
    }
//_Q->Mult(B, X);
//_A->PartialBackwardSubstitution(X);
_Adag->Mult(B, X);
// create the vector
if (_coef->size()!=_Ncoef) _coef->resize(_Ncoef);
for(size_t i=0;i<_Ncoef;i++) (*_coef)[i]=X[i+1];
_ref_val=X[0];
}
// compute the conditioning numer of the R matrix 
double FVRecons2D::ConditioningNumber()
{
double Min=1.e20,Max=-1.e20,val;
if (_A->nb_cols==0) return(-1.0);
for(size_t i=0;i<_A->nb_cols;i++)
    {
    val=abs(_A->getValue(i,i));
    //cout<<"val["<<i<<"]="<<val<<" ";
    if(Min>val) Min=val;
    if(Max<val) Max=val;
    }
//cout<<endl;    
if (Min>0) return(Max/Min);
return(1.0e20);    
}


double FVRecons2D::getValue(FVPoint2D<double> P,size_t degree)
{
// basic method to replace with horner method
double val=_ref_val;
size_t k,Ncoef;
FVPoint2D<size_t> al; 
size_t alpha1,alpha2;
degree=min(degree,_degree);
Ncoef=(degree+2)*(degree+1);Ncoef/=2;Ncoef--;
//cout<<"reference value="<<_ref_val<<endl;
for(k=0;k<Ncoef;k++)
    {
    al=alpha2D(k);   
    alpha1=al.x;alpha2=al.y;
    //cout<<"coef["<<alpha1<<","<<alpha2<<"]="<<(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;
    val+=(*_coef)[k]*(FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)-(*_M)[k]);
    }
return(val);degree=min(degree,_degree);
Ncoef=(degree+2)*(degree+1);Ncoef/=2;Ncoef--;
}
// compute the gradient
FVPoint2D<double> FVRecons2D::getDerivative(FVPoint2D<double> P, size_t degree) 
{
// basic method to replace with horner method
FVPoint2D<double> val=0.;
size_t k,Ncoef;
FVPoint2D<size_t> al; 
size_t alpha1,alpha2;
degree=min(degree,_degree);
//cout<<"degree is"<<degree<<endl;
Ncoef=(degree+2)*(degree+1);Ncoef/=2;Ncoef--;
for(k=0;k<Ncoef;k++)
    {
    al=alpha2D(k);   
    alpha1=al.x;alpha2=al.y;
    if(alpha1>0)
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha1*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.x+=alpha1*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1-1)*FVPow(P.y-_ref_point.y,alpha2);
        }
    if(alpha2>0)        
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha2*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.y+=alpha2*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2-1);
        }
    }
return(val);
}

FVPoint2D<FVPoint2D<double> > FVRecons2D::getHessian(FVPoint2D<double> P, size_t degree)
{
    
FVPoint2D<FVPoint2D<double> >val;
val.x.x=val.y.x=val.x.y=val.y.y=0.;
size_t k,Ncoef;
FVPoint2D<size_t> al; 
size_t alpha1,alpha2;
degree=min(degree,_degree);
//cout<<"degree is"<<degree<<endl;
Ncoef=(degree+2)*(degree+1);Ncoef/=2;Ncoef--;
for(k=0;k<Ncoef;k++)
    {
    al=alpha2D(k);   
    alpha1=al.x;alpha2=al.y;
    if(alpha1>1)
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha1*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.x.x+=alpha1*(alpha1-1)*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1-2)*FVPow(P.y-_ref_point.y,alpha2);
        }
    if(alpha2>1)        
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha2*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.y.y+=alpha2*(alpha2-1)*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2-2);
        }
    if((alpha1>0)&&(alpha2>0))
        {
        val.y.x+= alpha1*alpha2*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1-1)*FVPow(P.y-_ref_point.y,alpha2-1);  
        val.x.y=val.y.x;    
        }
    }
return(val);
}

void FVRecons2D::show()
{
FVPoint2D<size_t> al; 
size_t alpha1,alpha2; 
cout<<"FVRecons2D of entity "<<_ptr_s->getType()<<endl;
for(size_t k=0;k<_Ncoef;k++)
    {
    al=alpha2D(k);   
    alpha1=al.x;alpha2=al.y;
    cout<<"grau ["<<alpha1<<","<<alpha2<<"], coef:"<<(*_coef)[k]<<" and M."<<(*_M)[k]<<endl;
    }
}
