#ifndef __FVVERTEX1D_H
#define __FVVERTEX1D_H
#include <vector>
#include "FVPoint1D.h"
#include "FVGaussPoint.h"
#include "Parameter.h"
class FVCell1D;
class FVVertex1D
{
public:
FVPoint1D<double> coord, normal;
size_t label, code,pos_c;
FVCell1D *leftCell,*rightCell;
     FVVertex1D(){leftCell=NULL;rightCell=NULL;label=0;coord=0;normal=0;}
    ~FVVertex1D(){;}  
     FVCell1D* beginCell(){pos_c=0;return(leftCell);};
     FVCell1D* nextCell()
         {
          if(pos_c==0) {pos_c++;return(leftCell);}
          if(pos_c==1) {pos_c++;return(rightCell);}         
          return(NULL);
        }  
     double measure(){return (1.);}   
     double  getMeanValue(double (&f)(FVPoint1D<double> ))
     {
     return(f(this->coord));    
     }
     double  getMeanValue(double (&f)(FVPoint1D<double> ,Parameter &),Parameter &para)
     {
     return(f(this->coord,para));     
     }     
private:

};


inline bool isEqual(FVVertex1D *v1, FVVertex1D *v2)
     {
      if(v1->label==v2->label) return true; else return false;   
     }
#endif // define _FVVERTEX1D
