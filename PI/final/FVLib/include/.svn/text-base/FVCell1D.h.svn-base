#ifndef __FVCELL1D_H
#define __FVCELL1D_H
#include "FVPoint1D.h"
#include "FVGaussPoint.h"
#include "Parameter.h"

class FVVertex1D;
class FVCell1D
{
public:
FVPoint1D<double> centroid;
double length;
size_t label,code,nb_vertex;
FVVertex1D *firstVertex,*secondVertex; // the two vertices
FVPoint1D<double> first_normal,second_normal; // normal exterior


     FVCell1D(){firstVertex=NULL;secondVertex=NULL;label=0;_pos_v=0;}
    ~FVCell1D(){;}  
     double measure(){return (length);}
     FVVertex1D* beginVertex(){_pos_v=0;return(firstVertex);}
     FVVertex1D* nextVertex(){
                              if(_pos_v==0) {_pos_v++;return(firstVertex);}
                              if(_pos_v==1) {_pos_v++;return(secondVertex);}
                              return(NULL);} 
    size_t getLocalIndexVertex(){return _pos_v;}
    void setCode2Vertex(size_t val=0)
         {if (firstVertex) firstVertex->code=val;if(secondVertex) secondVertex->code=val;}
    double  getMeanValue(double (&f)(FVPoint1D<double> ))
    {
    FVPoint1D<double> P,P1,P2;
    FVPoint2D<double> GP;
    FVGaussPoint1D G1D;
    double val=0;
    P1=this->firstVertex->coord;
    P2=this->secondVertex->coord; 
    for(size_t i=1;i<=3;i++)
       {
       GP=G1D.getPoint(5,i);
       P=GP.x*P1+GP.y*P2;
       val+=G1D.getWeight(5,i)*f(P);
       }
    return(val);   
    }
    double  getMeanValue(double (&f)(FVPoint1D<double> ,Parameter &),Parameter &para)
    {
    FVPoint1D<double> P,P1,P2;
    FVPoint2D<double> GP;
    FVGaussPoint1D G1D;
    double val=0;
    P1=this->firstVertex->coord;
    P2=this->secondVertex->coord; 
    for(size_t i=1;i<=3;i++)
       {
       GP=G1D.getPoint(5,i);
       P=GP.x*P1+GP.y*P2;
       val+=G1D.getWeight(5,i)*f(P,para);
       }
   return(val);    
   }         
private:
size_t _pos_v;
};

inline bool isEqual(FVCell1D *c1, FVCell1D *c2)
     {
      bool is_equal1 = false, is_equal2 = false;  
      if(c1->firstVertex->label==c2->firstVertex->label) is_equal1=true;   
      if(c1->firstVertex->label==c2->secondVertex->label) is_equal1=true;
      if(c1->secondVertex->label==c2->firstVertex->label) is_equal2=true;
      if(c1->secondVertex->label==c2->secondVertex->label) is_equal2=true;
      return(is_equal1 && is_equal2);
     }

#endif // define _FVCELL1D
