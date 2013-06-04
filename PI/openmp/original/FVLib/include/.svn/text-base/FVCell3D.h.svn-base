#ifndef __FVCELL3D_H
#define __FVCELL3D_H
#include <vector>
#include "FVPoint3D.h"
#include "FVLib_config.h"
#include "FVGaussPoint.h"
#include "Parameter.h"
using namespace std;

class FVVertex3D;
class FVEdge3D;
class FVFace3D;
class FVCell3D
{
public:
FVPoint3D<double> centroid;
size_t label,code,nb_vertex,nb_face;
size_t pos_f,pos_v;
double surface,volume;
FVVertex3D* vertex[NB_VERTEX_PER_CELL_3D] ; // the  vertices
FVFace3D* face[NB_FACE_PER_CELL_3D];     // the face
FVPoint3D<double>  cell2face[NB_FACE_PER_CELL_3D]; // normal exterior for each face


     FVCell3D(){nb_vertex=0;nb_face=0;label=0;}
    ~FVCell3D(){;}  
     double measure(){return (volume);}
     FVVertex3D* beginVertex(){pos_v=0;if(pos_v<nb_vertex) return(vertex[0]);else return(NULL);}
     FVVertex3D* nextVertex(){if(pos_v<nb_vertex) return(vertex[pos_v++]);else return(NULL);}  
     FVFace3D* beginFace(){pos_f=0;if(pos_f<nb_face) return(face[0]);else return(NULL);};
     FVFace3D* nextFace(){if(pos_f<nb_face) return(face[pos_f++]);else return(NULL);}  
     size_t getLocalIndexVertex(){return pos_v;}
     size_t getLocalIndexFace(){return pos_f;}    
     FVPoint3D<double> getCell2Face(){return cell2face[pos_f-1];}
     void setCode2Face(size_t val=0)
         {for(size_t i=0;i<nb_face;i++) 
          if(face[i]) face[i]->code=val;}     
     void setCode2Edge(size_t val=0)
         {for(size_t i=0;i<nb_face;i++) 
          if(face[i]) face[i]->setCode2Edge(val);}
     void setCode2Vertex(size_t val=0)
         { 
             for(size_t i=0;i<nb_face;i++) 
                 if(face[i]) 
                 {face[i]->setCode2Vertex(val);}   
         } 
     double  getMeanValue(double (&f)(FVPoint3D<double> ))
     {
     double val,V_global,V,aux;    
     FVFace3D *ptr_f;
     FVEdge3D *ptr_e;
     FVPoint3D<double> P,P1,P2,centroid_f,centroid_c;
     FVPoint4D<double> GPPP;
     FVGaussPoint3D G3D;
     centroid_c=this->centroid; 
     V_global=0; 
     val=0.;
     this->beginFace();    
     while((ptr_f=this->nextFace()))
         {
         centroid_f=ptr_f->centroid;  
         ptr_f->beginEdge();
         while((ptr_e=ptr_f->nextEdge()))
             {
             P1=ptr_e->firstVertex->coord;
             P2=ptr_e->secondVertex->coord;
             V= Det(P1-centroid_c,P2-centroid_c,centroid_f-centroid_c)/6;
             if(V<0) V*=-1.;
             aux=0;
             for(size_t i=1;i<=G3D.getNbPoint(5);i++)
                 {              
                 GPPP=G3D.getPoint(5,i);
                 P=GPPP.x*P1+GPPP.y*P2+GPPP.z*centroid_f+GPPP.t*centroid_c;
                 aux+=G3D.getWeight(5,i)*f(P);
                 }    
             val+=aux*V;
             V_global+=V;
             }
         } 
     return(val/V_global);      
     }
     double  getMeanValue(double (&f)(FVPoint3D<double> ,Parameter &),Parameter &para)     
     {
     FVFace3D *ptr_f;
     FVEdge3D *ptr_e;
     FVPoint3D<double> P,P1,P2,centroid_f,centroid_c;
     FVPoint4D<double> GPPP;
     FVGaussPoint3D G3D;
     double val,V_global,V,aux;
     centroid_c=this->centroid; 
     V_global=0; 
     val=0.;
     this->beginFace();    
     while((ptr_f=this->nextFace()))
         {
         centroid_f=ptr_f->centroid;  
         ptr_f->beginEdge();
         while((ptr_e=ptr_f->nextEdge()))
             {
             P1=ptr_e->firstVertex->coord;
             P2=ptr_e->secondVertex->coord;
             V= Det(P1-centroid_c,P2-centroid_c,centroid_f-centroid_c)/6;
             if(V<0) V*=-1.;
             aux=0;
             for(size_t i=1;i<=G3D.getNbPoint(5);i++)
                 {              
                 GPPP=G3D.getPoint(5,i);
                 P=GPPP.x*P1+GPPP.y*P2+GPPP.z*centroid_f+GPPP.t*centroid_c;
                 aux+=G3D.getWeight(5,i)*f(P,para);
                 }    
             val+=aux*V;
             V_global+=V;
             }
         } 
     return(val/V_global);      
     }     
private:

};



inline bool isEqual(FVCell3D *c1, FVCell3D *c2)
     {
      bool is_equal,is_equal_total;
      if(c1->nb_face!=c2->nb_face) return false;
      is_equal_total=true;
      for(size_t i=0;i<c1->nb_face;i++)
         {
          is_equal=false;   
          for(size_t j=0;j<c2->nb_face;j++)
              if(c1->face[i]->label==c2->face[j]->label) is_equal=true;
          is_equal_total=is_equal_total && is_equal;    
         }
       return(is_equal_total);  
     }

#endif // define _FVCELL3D
