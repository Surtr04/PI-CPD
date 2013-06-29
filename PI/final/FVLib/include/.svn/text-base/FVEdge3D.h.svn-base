#ifndef __FVEDGE3D_H
#define __FVEDGE3D_H
#include <vector>
#include "FVPoint3D.h"
#include "FVLib_config.h"
#include "FVGaussPoint.h"
#include "Parameter.h"
using namespace std;


class FVVertex3D;
class FVEdge3D
{
public:
public:
FVPoint3D<double> centroid;
double length;
size_t label, code,nb_vertex;
FVVertex3D *firstVertex,*secondVertex; // the two vertices
     FVEdge3D(){firstVertex=NULL;secondVertex=NULL;nb_vertex=0;label=0;_pos_v=0;}
    ~FVEdge3D(){;} 
FVVertex3D* beginVertex(){_pos_v=0;return(firstVertex);}
FVVertex3D* nextVertex(){
                              if(_pos_v==0) {_pos_v++;return(firstVertex);}
                              if(_pos_v==1) {_pos_v++;return(secondVertex);}
                              return(NULL);}     
    void setCode2Vertex(size_t val=0)
         {if (firstVertex) firstVertex->code=val;if(secondVertex) secondVertex->code=val;} 
    double measure(){return (length);}  
    double  getMeanValue(double (&f)(FVPoint3D<double> ))
    {
    FVPoint3D<double> P,P1,P2;
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
    double  getMeanValue(double (&f)(FVPoint3D<double> ,Parameter &),Parameter &para)
    {
    FVPoint3D<double> P,P1,P2;
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



inline bool isEqual(FVEdge3D *e1, FVEdge3D *e2)
     {
      bool is_equal1 = false, is_equal2 = false;  
      if(e1->firstVertex->label==e2->firstVertex->label) is_equal1=true;   
      if(e1->firstVertex->label==e2->secondVertex->label) is_equal1=true;
      if(e1->secondVertex->label==e2->firstVertex->label) is_equal2=true;
      if(e1->secondVertex->label==e2->secondVertex->label) is_equal2=true;
      return(is_equal1 && is_equal2);
     }
#endif // define _FVEDGE3D
