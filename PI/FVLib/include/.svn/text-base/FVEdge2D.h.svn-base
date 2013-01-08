#ifndef __FVEDGE2D_H
#define __FVEDGE2D_H
#include <vector>
#include "FVPoint2D.h"
#include "FVLib_config.h"
#include "FVGaussPoint.h"
#include "Parameter.h"
using namespace std;

class FVCell2D;
class FVVertex2D;
class FVEdge2D
{
public:
FVPoint2D<double> centroid;
double length;
size_t label, code,nb_vertex,nb_cell;
FVCell2D *leftCell,*rightCell;  // the two cells
FVVertex2D *firstVertex,*secondVertex; // the two vertices
FVPoint2D<double> normal;  // from left to right
     FVEdge2D(){leftCell=NULL;rightCell=NULL;firstVertex=NULL;secondVertex=NULL;label=0;_pos_v=0;}
    ~FVEdge2D(){;}  
FVVertex2D* beginVertex(){_pos_v=0;return(firstVertex);}
FVVertex2D* nextVertex(){
                              if(_pos_v==0) {_pos_v++;return(firstVertex);}
                              if(_pos_v==1) {_pos_v++;return(secondVertex);}
                              return(NULL);} 
size_t getLocalIndexVertex(){return _pos_v;}
void setCode2Vertex(size_t val=0)
         {if (firstVertex) firstVertex->code=val;if(secondVertex) secondVertex->code=val;}    
double measure(){return (length);}    

double  getMeanValue(double (&f)(FVPoint2D<double> ))
    {
    FVPoint2D<double> P,P1,P2;
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
double  getMeanValue(double (&f)(FVPoint2D<double> ,Parameter &),Parameter &para)
    {
    FVPoint2D<double> P,P1,P2;
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


inline bool isEqual(FVEdge2D *e1, FVEdge2D *e2)
     {
      bool is_equal1 = false, is_equal2 = false;  
      if(e1->firstVertex->label==e2->firstVertex->label) is_equal1=true;   
      if(e1->firstVertex->label==e2->secondVertex->label) is_equal1=true;
      if(e1->secondVertex->label==e2->firstVertex->label) is_equal2=true;
      if(e1->secondVertex->label==e2->secondVertex->label) is_equal2=true;
      return(is_equal1 && is_equal2);
     }
#endif // define _FVEDGE2D
