#ifndef __FVFACE3D_H
#define __FVFACE3D_H
#include <vector>
#include "FVPoint3D.h"
#include "FVLib_config.h"
#include "FVGaussPoint.h"
#include "Parameter.h"
using namespace std;

class FVCell3D;
class FVEdge3D;
class FVVertex3D;
class FVFace3D
{
public:
FVPoint3D<double> centroid;
double perimeter,area;
size_t label, code,nb_vertex,nb_edge,nb_cell,pos_e,pos_v;
FVCell3D *leftCell,*rightCell;  // the two cells
FVVertex3D *vertex[NB_VERTEX_PER_FACE_3D]; // the vertices
FVPoint3D<double> normal;
FVPoint3D<double> LocalNormal[NB_VERTEX_PER_FACE_3D];  // from left to right
FVEdge3D *edge[NB_EDGE_PER_FACE_3D]; // the vertices

     FVFace3D(){leftCell=NULL;rightCell=NULL;nb_vertex=0;nb_edge=0;nb_cell=0;label=0;}
    ~FVFace3D(){;}
    
     FVVertex3D* beginVertex(){pos_v=0;if(pos_v<nb_vertex) return(vertex[0]);else return(NULL);}
     FVVertex3D* nextVertex(){if(pos_v<nb_vertex) return(vertex[pos_v++]);else return(NULL);}  
     FVEdge3D* beginEdge(){pos_e=0;if(pos_e<nb_edge) return(edge[0]);else return(NULL);};
     FVEdge3D* nextEdge(){if(pos_e<nb_edge) return(edge[pos_e++]);else return(NULL);} 
     size_t getLocalIndexVertex(){return pos_v;}
     size_t getLocalIndexEdge(){return pos_e;}
     FVPoint3D<double> getNormal(){return LocalNormal[pos_e-1];}
     void setCode2Edge(size_t val=0)
         {for(size_t i=0;i<nb_edge;i++) 
          if(edge[i]) edge[i]->code=val;}
     void setCode2Vertex(size_t val=0)
         { 
             for(size_t i=0;i<nb_edge;i++) 
                 if(edge[i]) 
                 {edge[i]->setCode2Vertex(val);}   
         } 
     double measure(){return (area);}  
     double  getMeanValue(double (&f)(FVPoint3D<double> ))
     {
     FVEdge3D *ptr_e;
     FVPoint3D<double> P,P1,P2,centroid;
     FVPoint3D<double> GPP;
     FVGaussPoint2D G2D;
     double val,S_global,S,aux;    
     centroid=this->centroid;  
     S_global=0;
     val=0.;
     this->beginEdge();
     while((ptr_e=this->nextEdge()))
         {
         P1=ptr_e->firstVertex->coord;
         P2=ptr_e->secondVertex->coord;
         S=Norm(CrossProduct(P1-centroid,P2-centroid))*0.5;
         if(S<0) S*=-1.;
         aux=0;
         for (size_t i=1;i<=G2D.getNbPoint(5);i++)
            { 
            GPP=G2D.getPoint(5,i);
            P=GPP.x*P1+GPP.y*P2+GPP.z*centroid;
            aux+=G2D.getWeight(5,i)*f(P);
            }    
         val+=aux*S;
         S_global+=S;
         }
     val/=S_global;  
     return(val);          
     }
     double  getMeanValue(double (&f)(FVPoint3D<double> ,Parameter &),Parameter &para)
     {
     FVEdge3D *ptr_e;
     FVPoint3D<double> P,P1,P2,centroid;
     FVPoint3D<double> GPP;
     FVGaussPoint2D G2D;
     double val,S_global,S,aux;    
     centroid=this->centroid;  
     S_global=0;
     val=0.;
     this->beginEdge();
     while((ptr_e=this->nextEdge()))
         {
         P1=ptr_e->firstVertex->coord;
         P2=ptr_e->secondVertex->coord;
         S=Norm(CrossProduct(P1-centroid,P2-centroid))*0.5;
         if(S<0) S*=-1.;
         aux=0;
         for (size_t i=1;i<=G2D.getNbPoint(5);i++)
            { 
            GPP=G2D.getPoint(5,i);
            P=GPP.x*P1+GPP.y*P2+GPP.z*centroid;
            aux+=G2D.getWeight(5,i)*f(P,para);
            }    
         val+=aux*S;
         S_global+=S;
         }
     val/=S_global;  
     return(val);          
     }     
private:

};




inline bool isEqual(FVFace3D *f1, FVFace3D *f2)
     {
      bool is_equal,is_equal_total;
      if(f1->nb_edge!=f2->nb_edge) return false;
      is_equal_total=true;
      for(size_t i=0;i<f1->nb_edge;i++)
         {
          is_equal=false;   
          for(size_t j=0;j<f2->nb_edge;j++)
              if(f1->edge[i]->label==f2->edge[j]->label) is_equal=true;
          is_equal_total=is_equal_total && is_equal;    
         }
       return(is_equal_total);  
     }

#endif // define _FVFACE3D
