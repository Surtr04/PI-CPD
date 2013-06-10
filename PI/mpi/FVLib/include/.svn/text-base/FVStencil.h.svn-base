#ifndef __FVSTENCIL_H
#define __FVSTENCIL_H
#include "FVLib_config.h"
#include "FVMesh1D.h"
#include "FVMesh2D.h"
#include "FVMesh3D.h"
#include "FVVertex1D.h"
#include "FVCell1D.h"
#include "FVVertex2D.h"
#include "FVEdge2D.h"
#include "FVCell2D.h"
#include "FVVertex3D.h"
#include "FVEdge3D.h"
#include "FVFace3D.h"
#include "FVCell3D.h"
#include "FVSparseV.h"
#include <iostream>
#include <cstdio>
class FVStencil
{
private:
void*  _reference_geometry;
size_t _reference_type;
FVPoint1D<double> _P1;
FVPoint2D<double> _P2;
FVPoint3D<double> _P3;
vector<void*>  *_geometry ; 
vector<size_t> *_type; 
size_t _nb_geometry,_pos;
public:
vector<double> *weight;    

FVStencil()
    { 
    //cout<<"using the FVStencil  default constructor"<<endl;
    _nb_geometry=0;_pos=0;_reference_geometry=NULL;_reference_type=NULL_ENTITY;_geometry=NULL;_type=NULL;
    _geometry=new vector<void*> ;_type=new vector<size_t>;weight=new vector<double>;
    _P1=0;_P2=0;_P3=0;
    _geometry->resize(0);_type->resize(0);weight->resize(0);
    }
~FVStencil()
    {
    if(_geometry) {delete(_geometry);_geometry=NULL;}
    if(_type) {delete(_type);_type=NULL;}
    if(weight) {delete(weight);_type=NULL;}                 
    }  
                
FVStencil(const FVStencil &st); // copy constructor
FVStencil & operator =(const  FVStencil &st) // assigment operator
    {
    //cout<<"using the FVStencil assigment operator "<<endl;
    _nb_geometry=st._nb_geometry;
    _pos=st._pos;
    _reference_geometry=st._reference_geometry;
    _reference_type=st._reference_type;
    _P1=st._P1;_P2=st._P2;_P3=st._P3;                      
    _geometry->resize(_nb_geometry);
    _type->resize(_nb_geometry);
    weight->resize(_nb_geometry);
    for(size_t i=0;i<_nb_geometry;i++)
        {
        (*_geometry)[i]=(* st._geometry)[i];
        (*_type)[i]=(* st._type)[i];
        (*weight)[i]=(* st.weight)[i];
        }
    return *this;
    }
void* beginGeometry(){_pos=0;if(_pos<_nb_geometry) return((*_geometry)[0]);else return(NULL);}
void* nextGeometry(){if(_pos<_nb_geometry) return((*_geometry)[_pos++]);else return(NULL);}   
size_t getIndex(){if(_pos>0) return (_pos-1); else return(0);}
void* getGeometry(size_t i){return ((*_geometry)[i]);}
size_t getType(){if(_pos>0) return((*_type)[_pos-1]); else return(NULL_ENTITY);}
size_t getType(size_t i){return((*_type)[i]);}  
size_t getReferenceType(){return _reference_type;}     
void* getReferenceGeometry(){return (_reference_geometry);}         
size_t getNbGeometry(){return(_nb_geometry);}
void clean()
    {
    _nb_geometry=0;
    _reference_geometry=NULL;
    _reference_type=NULL_ENTITY;
    _geometry->resize(0),
    _type->resize(0);
    weight->resize(0);
    }     
void show();
     //
void addStencil(FVVertex1D *ptr,double w );     
void addStencil(FVVertex1D *ptr ){ FVStencil::addStencil(ptr,1.0);}       
void setReferenceGeometry(FVVertex1D *ptr);

void addStencil(FVVertex2D *ptr,double w ); 
void addStencil(FVVertex2D *ptr ){ FVStencil::addStencil(ptr,1.0);}  
void setReferenceGeometry(FVVertex2D *ptr );
 
void addStencil(FVVertex3D *ptr,double w );     
void addStencil(FVVertex3D *ptr ){ FVStencil::addStencil(ptr,1.0);}       
void setReferenceGeometry(FVVertex3D *ptr ); 

void addStencil(FVCell1D *ptr,double w, size_t the_code);   
void addStencil(FVCell1D *ptr,double w );   
void addStencil(FVCell1D *ptr, size_t the_code){ FVStencil::addStencil(ptr,1.0,the_code);}    
void addStencil(FVCell1D *ptr ){ FVStencil::addStencil(ptr,1.0);}  
void setReferenceGeometry(FVCell1D *ptr );

void addStencil(FVCell2D *ptr,double w, size_t the_code);     
void addStencil(FVCell2D *ptr,double w ); 
void addStencil(FVCell2D *ptr, size_t the_code){ FVStencil::addStencil(ptr,1.0,the_code);}        
void addStencil(FVCell2D *ptr ){ FVStencil::addStencil(ptr,1.0);}
void setReferenceGeometry(FVCell2D *ptr );

void addStencil(FVCell3D *ptr,double w, size_t the_code);   
void addStencil(FVCell3D *ptr,double w );
void addStencil(FVCell3D *ptr, size_t the_code){ FVStencil::addStencil(ptr,1.0,the_code);}   
void addStencil(FVCell3D *ptr ){ FVStencil::addStencil(ptr,1.0);}  
void setReferenceGeometry(FVCell3D *ptr );       

void addStencil(FVEdge2D *ptr,double w );   
void addStencil(FVEdge2D *ptr ){ FVStencil::addStencil(ptr,1.0);}        
void setReferenceGeometry(FVEdge2D *ptr );

void addStencil(FVEdge3D *ptr,double );   
void addStencil(FVEdge3D *ptr ){ FVStencil::addStencil(ptr,1.0);}      
void setReferenceGeometry(FVEdge3D *ptr );  

void addStencil(FVFace3D *ptr, double );  
void addStencil(FVFace3D *ptr ){ FVStencil::addStencil(ptr,1.0);}      
void setReferenceGeometry(FVFace3D *ptr ); 
//
void addCellStencil(FVMesh1D &m, size_t nbcell);     
void addCellStencil(FVMesh2D &m, size_t nbcell);
void addCellStencil(FVMesh3D &m, size_t nbcell);     
void addCellStencil(FVMesh1D &m, size_t nbcell,size_t the_code);     
void addCellStencil(FVMesh2D &m, size_t nbcell,size_t the_code);
void addCellStencil(FVMesh3D &m, size_t nbcell,size_t the_code); 

void addVertexStencil(FVMesh1D &m, size_t nbvertex);   
void addVertexStencil(FVMesh2D &m, size_t nbvertex);     
void addVertexStencil(FVMesh3D &m, size_t nbvertex);  


bool inStencil(FVVertex1D *ptr );     
bool inStencil(FVVertex2D *ptr );     
bool inStencil(FVVertex3D *ptr );      
bool inStencil(FVCell1D *ptr );     
bool inStencil(FVCell2D *ptr );     
bool inStencil(FVCell3D *ptr );        
bool inStencil(FVEdge2D *ptr );     
bool inStencil(FVEdge3D *ptr );      
bool inStencil(FVFace3D *ptr );     
 
private:

};

#endif // define __FVSTENCIL_H