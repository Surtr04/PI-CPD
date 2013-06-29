// ------ FVRecons3D.cpp ------
// S. CLAIN 2011/12/21

#include "FVRecons3D.h"


FVPoint3D<size_t> alpha3D(size_t k1)//k1 start to 0
{
FVPoint3D<size_t> alpha;
size_t d1=1,d2=0,k2;

if(k1>2)  d1+=1;
if(k1>8)  d1+=1;
if(k1>18) d1+=1;
if(k1>33) d1+=1;
k2=k1+1-((d1)*(d1+1)*(d1+2))/6;

if(k2>0)  d2+=1;
if(k2>2)  d2+=1;
if(k2>5)  d2+=1;
if(k2>9)  d2+=1;
if(k2>14) d2+=1;
alpha.z=k2-((d2)*(d2+1))/2;
//cout<<"d1="<<d1<<", d2="<<d2<<", k2="<<k2<<endl;
alpha.y=d2-alpha.z;
alpha.x=d1-alpha.y-alpha.z;
return(alpha);
}

FVRecons3D::FVRecons3D(const FVRecons3D & rec) // copy constructor
{
//cout<<"using the FVRecons3D copy constructor"<<endl;  fflush(NULL);     
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

double FVRecons3D::_evalMean(void *ptr,size_t type,size_t alpha1,size_t alpha2,size_t alpha3)
{
FVPoint3D<double> P1,P2,P;
double sum,S,S_global,aux,V,V_global;
sum=0.;
FVPoint2D<double> GPEdge;
FVPoint3D<double> GPFace;
FVPoint4D<double> GPCell;
FVGaussPoint1D G1D;
FVGaussPoint2D G2D;
FVGaussPoint3D G3D;
FVCell3D *ptr_c;
FVFace3D *ptr_f;
FVEdge3D *ptr_e;
FVVertex3D *ptr_v1,*ptr_v2;
FVPoint3D<double> centroidF,centroidC;
switch(type)
   {
    case FVVERTEX3D:
    P=((FVVertex3D *)ptr)->coord;
    return(FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3));    
    break;
    case FVEDGE3D:
    P1=((FVEdge3D *)ptr)->firstVertex->coord;
    P2=((FVEdge3D *)ptr)->secondVertex->coord; 
    GPEdge=G1D.getPoint(5,1);
    P=GPEdge.x*P1+GPEdge.y*P2;
    sum+=G1D.getWeight(5,1)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3);
    GPEdge=G1D.getPoint(5,2);
    P=GPEdge.x*P1+GPEdge.y*P2;
    sum+=G1D.getWeight(5,2)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3); 
    GPEdge=G1D.getPoint(5,3);
    P=GPEdge.x*P1+GPEdge.y*P2;
    sum+=G1D.getWeight(5,3)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3);    
    return(sum);
    break;   
    case FVFACE3D:
    ptr_f=((FVFace3D *)ptr);
    centroidF=ptr_f->centroid; 
    S_global=0;
    ptr_f->beginEdge();
    while((ptr_e=ptr_f->nextEdge()))
        {
        ptr_v1=ptr_e->firstVertex;
        ptr_v2=ptr_e->secondVertex;
        S= Norm(CrossProduct(ptr_v1->coord-centroidF,ptr_v2->coord-centroidF))*0.5;
        if(S<0) S*=-1.;
        aux=0;
        for (size_t i=1;i<=G2D.getNbPoint(5);i++)
             { 
               GPFace=G2D.getPoint(5,i);
               P=GPFace.x*ptr_v1->coord+GPFace.y*ptr_v2->coord+GPFace.z*centroidF;
               aux+=G2D.getWeight(5,i)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3);
             }    
         sum+=aux*S;
         S_global+=S;
         }
    return(sum/S_global);  
    break;
    case FVCELL3D:
    ptr_c=((FVCell3D *)ptr);
    centroidC=ptr_c->centroid; 
    V_global=0; 
    ptr_c->beginFace();    
    while((ptr_f=ptr_c->nextFace()))
        {
        centroidF=ptr_f->centroid;  
        ptr_f->beginEdge();
        while((ptr_e=ptr_f->nextEdge()))
            {
            ptr_v1=ptr_e->firstVertex;
            ptr_v2=ptr_e->secondVertex;
            V= Det(ptr_v1->coord-centroidC,ptr_v2->coord-centroidC,centroidF-centroidC)/6;
            if(V<0) V*=-1.;
            aux=0;
            for(size_t i=1;i<=G3D.getNbPoint(5);i++)
                { 
                 GPCell=G3D.getPoint(5,i);
                 P=GPCell.x*ptr_v1->coord+GPCell.y*ptr_v2->coord+GPCell.z*centroidF+GPCell.t*centroidC;
                 aux+=G3D.getWeight(5,i)*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3);
                }    
            sum+=aux*V;
            V_global+=V;
            }
        } 
    return(sum/V_global);    
    break;    
    default:
    cout<<"WARNING: unknow geometrical entity in FVReconstruction3D"<<endl;    
    return(0); 
    break;    
   }
return(0);  
}
// Matrix associated to reconstruction without the conservative reference value 
void FVRecons3D::doConservativeMatrix()
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
_Adag->resize(_Ncoef,_ptr_s->getNbGeometry());
_Q->resize(_ptr_s->getNbGeometry());
_M->resize(_Ncoef); 
FVPoint3D<size_t> al;
size_t alpha1,alpha2,alpha3;
//  for the conditioning
h=1;
if(_ptr_s->getReferenceType()==FVEDGE3D) h=((FVEdge3D *)_ptr_s->getReferenceGeometry())->length;
if(_ptr_s->getReferenceType()==FVFACE3D) h=sqrt(((FVFace3D *)_ptr_s->getReferenceGeometry())->area);
if(_ptr_s->getReferenceType()==FVCELL3D) h=FVSqrt3(((FVCell3D *)_ptr_s->getReferenceGeometry())->volume);
//
for(size_t j=0;j<_Ncoef;j++)
    { 
     al=alpha3D(j);   
     alpha1=al.x;alpha2=al.y;alpha3=al.z;
     (*_M)[j]=FVRecons3D::_evalMean(_ptr_s->getReferenceGeometry(),_ptr_s->getReferenceType(),alpha1,alpha2,alpha3);
     MatCond[j]=1./FVPow(h,alpha1+alpha2+alpha3);     
     _ptr_s->beginGeometry();
     while((ptr=_ptr_s->nextGeometry()))
          {
          size_t i=_ptr_s->getIndex(); 
          weight=(*_ptr_s->weight)[i]*MatCond[j]; 
          weight*=FVRecons3D::_evalMean(ptr,_ptr_s->getType(),alpha1,alpha2,alpha3)-(*_M)[j];
          _A->setValue(i,j,weight);
          }
    }   
_A->DagMatrix(*_Adag);_Adag->leftMatrixMult(MatCond);    
//_A->QRFactorize(*_Q);
//_A->show();
}
// Matrix associated to reconstruction without the conservative reference value 
void FVRecons3D::doNonConservativeMatrix()
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
FVPoint3D<size_t> al;
size_t alpha1,alpha2,alpha3;
//  for the conditioning
h=1;
if(_ptr_s->getReferenceType()==FVEDGE3D) h=((FVEdge3D *)_ptr_s->getReferenceGeometry())->length;
if(_ptr_s->getReferenceType()==FVFACE3D) h=sqrt(((FVFace3D *)_ptr_s->getReferenceGeometry())->area);
if(_ptr_s->getReferenceType()==FVCELL3D) h=FVSqrt3(((FVCell3D *)_ptr_s->getReferenceGeometry())->volume);
//
_ptr_s->beginGeometry();
while((ptr=_ptr_s->nextGeometry()))
      {
          _A->setValue(_ptr_s->getIndex(),0,(*_ptr_s->weight)[_ptr_s->getIndex()]);
      }
MatCond[0]=1;      
for(size_t j=0;j<_Ncoef;j++)
    {  
     al=alpha3D(j);   
     alpha1=al.x;alpha2=al.y;alpha3=al.z;
     (*_M)[j]=0;
     MatCond[j+1]=1./FVPow(h,alpha1+alpha2+alpha3);     
     _ptr_s->beginGeometry();
     while((ptr=_ptr_s->nextGeometry()))
          {
          size_t i=_ptr_s->getIndex();
          weight=(*_ptr_s->weight)[i]*MatCond[j+1];  
          weight*=  FVRecons3D::_evalMean(ptr,_ptr_s->getType(),alpha1,alpha2,alpha3);
          _A->setValue(i,j+1,weight);
          }
    }  
//_A->QRFactorize(*_Q);
_A->DagMatrix(*_Adag); _Adag->leftMatrixMult(MatCond);
}

// Polynomial coeffient  with the conservative reference value 
void FVRecons3D::computeConservativeCoef()
{
if(_reconstruction_type!=REC_CONSERVATIVE) {cout<<"error construction type not defined"<<endl;exit(0);}      
FVVect<double> B(_ptr_s->getNbGeometry()),X(_ptr_s->getNbGeometry()); 
void *ptr;
double  geo_val=0;
_ref_val=0;
size_t k,i;
switch(_ptr_s->getReferenceType())
  {
    case FVVERTEX3D:
    #ifdef _DEBUGS
    if(!_Vertex3DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex3DVect is empty"<<endl;
         break;
         }
    #endif
    k= ( (FVVertex3D *) _ptr_s->getReferenceGeometry())->label-1; 
    _ref_val=(*_Vertex3DVect)[k];
    break;
    case FVEDGE3D:
    #ifdef _DEBUGS
    if(!_Edge3DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Edge3DVect is empty"<<endl;
         break;
         }
    #endif
    k=( (FVEdge3D *) _ptr_s->getReferenceGeometry())->label-1;     
    _ref_val=(*_Edge3DVect)[k];    
    break; 
    case FVFACE3D:
    #ifdef _DEBUGS
    if(!_face3DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Face3DVect is empty"<<endl;
         break;
         }
    #endif        
    k=  ((FVFace3D *) _ptr_s->getReferenceGeometry())->label-1; 
    _ref_val=(*_Face3DVect)[k];
    break; 
    case FVCELL3D:
    #ifdef _DEBUGS
    if(!_Cell3DVect)
         {
         cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell3DVect is empty"<<endl;
         break;
         }
    #endif        
    k=  ((FVCell3D *) _ptr_s->getReferenceGeometry())->label-1; 
    _ref_val=(*_Cell3DVect)[k];    
  }
_ptr_s->beginGeometry();  
while((ptr=_ptr_s->nextGeometry()))
    {
    switch(_ptr_s->getType())
       {
        case FVVERTEX3D:
        #ifdef _DEBUGS
        if(!_Vertex3DVect)
             {
             cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex3DVect is empty"<<endl;
             break;
             }
       #endif   
       k= ((FVVertex3D *) ptr)->label-1; 
       geo_val=(*_Vertex3DVect)[k];
       break;
       case FVEDGE3D:       
       #ifdef _DEBUGS
       if(!_Edge3DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Edge3DVect is empty"<<endl;
           break;
           }
       #endif 
       k=((FVEdge3D *) ptr)->label-1;
       geo_val=(*_Edge3DVect)[k];    
       break; 
       case FVFACE3D:         
       #ifdef _DEBUGS           
       if(!_Face3DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Face3DVect is empty"<<endl;
           break;
           }
       #endif    
       k=  ((FVFace3D *) ptr)->label-1;  
       geo_val=(*_Face3DVect)[k];
       break; 
       case FVCELL3D:         
       #ifdef _DEBUGS           
       if(!_Cell3DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell3DVect is empty"<<endl;
           break;
           }
       #endif    
       k=  ((FVCell3D *) ptr)->label-1;  
       geo_val=(*_Cell3DVect)[k];       
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
void FVRecons3D::computeNonConservativeCoef()
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
        case FVVERTEX3D:
        #ifdef _DEBUGS
        if(!_Vertex3DVect)
             {
             cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Vertex3DVect is empty"<<endl;
             break;
             }
       #endif   
       k= ((FVVertex3D *) ptr)->label-1; 
       geo_val=(*_Vertex3DVect)[k];
       break;
       case FVEDGE3D:       
       #ifdef _DEBUGS
       if(!_Edge3DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Edge3DVect is empty"<<endl;
           break;
           }
       #endif 
       k=((FVEdge3D *) ptr)->label-1;
       geo_val=(*_Edge3DVect)[k];    
       break; 
       case FVFACE3D:         
       #ifdef _DEBUGS           
       if(!_Face3DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Face3DVect is empty"<<endl;
           break;
           }
       #endif    
       k=  ((FVFace3D *) ptr)->label-1;  
       geo_val=(*_Face3DVect)[k];
       break; 
       case FVCELL3D:         
       #ifdef _DEBUGS           
       if(!_Cell3DVect)
           {
           cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"vector _Cell3DVect is empty"<<endl;
           break;
           }
       #endif    
       k=  ((FVCell3D *) ptr)->label-1;  
       geo_val=(*_Cell3DVect)[k];       
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
double FVRecons3D::ConditioningNumber()
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
double FVRecons3D::getValue(FVPoint3D<double> P,size_t degree)
{
// basic method to replace with horner method
double val=_ref_val;
size_t k,Ncoef;
FVPoint3D<size_t> al; 
size_t alpha1,alpha2,alpha3;
degree=min(degree,_degree);
Ncoef=(degree+2)*(degree+1)*(degree+3);Ncoef/=6;Ncoef--;
//cout<<"reference value="<<_ref_val<<endl;
for(k=0;k<Ncoef;k++)
    {
    al=alpha3D(k);   
    alpha1=al.x;alpha2=al.y;alpha3=al.z;
    //cout<<"coef["<<alpha1<<","<<alpha2<<","<<alpha3<<"]="<<(*_coef)[k]<<" with M="<<(*_M)[k]<<endl;
    val+=(*_coef)[k]*(FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3)-(*_M)[k]);
    }
return(val);
}
// compute the gradient
FVPoint3D<double> FVRecons3D::getDerivative(FVPoint3D<double> P, size_t degree)
{
// basic method to replace with horner method
FVPoint3D<double> val=0.;
size_t k,Ncoef;
FVPoint3D<size_t> al; 
size_t alpha1,alpha2,alpha3;
degree=min(degree,_degree);
Ncoef=(degree+2)*(degree+1)*(degree+3);Ncoef/=6;Ncoef--;
for(k=0;k<Ncoef;k++)
    {
    al=alpha3D(k);   
    alpha1=al.x;alpha2=al.y;alpha3=al.z;
    if(alpha1>0)
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<","<<alpha3<<"]="<<alpha1*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.x+=alpha1*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1-1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3);
        }
    if(alpha2>0)        
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<","<<alpha3<<"]="<<alpha2*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.y+=alpha2*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2-1)*FVPow(P.z-_ref_point.z,alpha3);
        }
    if(alpha3>0)        
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<","<<alpha3<<"]="<<alpha3*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.z+=alpha3*(*_coef)[k]*FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3-1);
        }        

    }
return(val);
}

FVPoint3D<FVPoint3D<double> > FVRecons3D::getHessian(FVPoint3D<double> P, size_t degree)
{
    
FVPoint3D<FVPoint3D<double> >val;
val.x.x=val.x.y=val.x.z=0.;
val.y.x=val.y.y=val.y.z=0.;
val.z.x=val.z.y=val.z.z=0.;
size_t k,Ncoef;
FVPoint3D<size_t> al; 
size_t alpha1,alpha2,alpha3;
degree=min(degree,_degree);
//cout<<"degree is"<<degree<<endl;
Ncoef=(degree+2)*(degree+1)*(degree+3);Ncoef/=6;Ncoef--;
for(k=0;k<Ncoef;k++)
    {
    al=alpha3D(k);   
    alpha1=al.x;alpha2=al.y;alpha3=al.z;
    if(alpha1>1)
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha1*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.x.x+=alpha1*(alpha1-1)*(*_coef)[k]*
                 FVPow(P.x-_ref_point.x,alpha1-2)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3);
        }
    if(alpha2>1)        
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha2*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.y.y+=alpha2*(alpha2-1)*(*_coef)[k]*
                 FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2-2)*FVPow(P.z-_ref_point.z,alpha3);
        }
    if(alpha3>1)        
        {
        //cout<<"power["<<alpha1<<","<<alpha2<<"]="<<alpha2*(*_coef)[k]<<" com M="<<(*_M)[k]<<endl;  
        val.z.z+=alpha3*(alpha3-1)*(*_coef)[k]*
                 FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3-2);
        }        
    if((alpha1>0)&&(alpha2>0))
        {
        val.x.y+= alpha1*alpha2*(*_coef)[k]*
                 FVPow(P.x-_ref_point.x,alpha1-1)*FVPow(P.y-_ref_point.y,alpha2-1)*FVPow(P.z-_ref_point.z,alpha3);  
        val.y.x=val.x.y;    
        }
    if((alpha1>0)&&(alpha3>0))
        {
        val.x.z+= alpha1*alpha3*(*_coef)[k]*
                 FVPow(P.x-_ref_point.x,alpha1-1)*FVPow(P.y-_ref_point.y,alpha2)*FVPow(P.z-_ref_point.z,alpha3-1);  
        val.z.x=val.x.z;    
        }
    if((alpha2>0)&&(alpha3>0))
        {
        val.y.z+= alpha2*alpha3*(*_coef)[k]*
                 FVPow(P.x-_ref_point.x,alpha1)*FVPow(P.y-_ref_point.y,alpha2-1)*FVPow(P.z-_ref_point.z,alpha3-1);  
        val.z.y=val.y.z;    
        }        
    }
return(val);
}
void FVRecons3D::show()
{
FVPoint3D<size_t> al; 
size_t alpha1,alpha2,alpha3; 
cout<<"FVRecons3D of entity "<<_ptr_s->getType()<<endl;
cout<<"grau [0,0,0], coef:"<<_ref_val <<" and M."<<0<<endl;
for(size_t k=0;k<_Ncoef;k++)
    {
    al=alpha3D(k);   
    alpha1=al.x;alpha2=al.y;alpha3=al.z;
    cout<<"grau ["<<alpha1<<","<<alpha2<<","<<alpha3<<"], coef:"<<(*_coef)[k]<<" and M."<<(*_M)[k]<<endl;
    }
}
