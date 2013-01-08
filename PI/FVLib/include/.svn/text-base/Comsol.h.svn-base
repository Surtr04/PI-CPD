// ------ Comsol.h ------
// S. CLAIN 2012/10
#ifndef _COMSOL
#define _COMSOL

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include<cstdlib>
//#include "XML.h"
#include "FVTools.h"
#include "FVVect.h"
#include "FVio.h"
#include "FVPoint1D.h"
#include "FVPoint2D.h"
#include "FVPoint3D.h"
#include "FVVertex3D.h"
#include "FVLib_config.h"
class Gmsh;
class CSElement
{
public:
    CSElement(){label=0;}
    
size_t label,type_element,code_physical, code_elementary,nb_node,dim;
size_t node[COMSOL_NB_NODE_PER_ELEMENT];
void show()
     {cout<<"--- GMElement: label="<<label<<", type element="<<type_element<<", physical code="<<code_physical
          <<", dim="<<dim<<endl;
      for(size_t i=0;i<nb_node;i++) cout<<"node number="<<node[i]<<endl;
     }
};
class ComsolPhysical
{
 public:
     ComsolPhysical();
     ~ComsolPhysical();
     ComsolPhysical(const char *);     // constructor to read a comsolPhysical file
     void show();
     void readTable(const char *); // read a comsolPhysical file (format .xml)
     FVPoint2D<size_t > getCodeVertex(size_t i){ return _codeVertex[i];}
     FVPoint2D<size_t > getCodeEdge(size_t i){ return _codeEdge[i];}
     FVPoint2D<size_t > getCodeFace(size_t i){ return _codeFace[i];}
     FVPoint2D<size_t > getCodeCell(size_t i){ return _codeCell[i];}     
     size_t getNbCodeVertex(){return _codeVertex.size();}
     size_t getNbCodeEdge(){return _codeEdge.size();}     
     size_t getNbCodeFace(){return _codeFace.size();}            
     size_t getNbCodeCell(){return _codeCell.size();}     
private:
    vector<FVPoint2D<size_t> > _codeVertex,_codeEdge,_codeFace,_codeCell;    
};

class Comsol
{
public:
     Comsol();
     ~Comsol();
     Comsol(const char *);     // constructor to read a comsol file
     void show();
     size_t getNbNode(){return _nb_node;}
     size_t getNbElement(){return _nb_element;}     
     size_t getDim(){return _dim;}            
     string getName(){return _name;}
     
     void readMesh(const char *); // read a comsol file (format .mphtxt)
     void writeMesh(const char *); // write a comsol file (format .mphtxt) 
     void readComsolPhysical(const char *);
     void close();
     void cleanString(char *); // remove all the comment and carriage return
     void Gmsh2Comsol(Gmsh &);  // convert a Gmsh struct into a Comsol
     void geo2phys(); // set the physical code in function of the geometrical code and the table.

     FVVertex3D* getNode(const size_t i){return &(_node[i]);}
     CSElement* getElement(const size_t i){return &(_element[i]);}
private:
    vector<FVVertex3D> _node;
    vector<CSElement> _element;
    ComsolPhysical _cp;
    size_t _nb_node,_nb_element,_dim,_nb_save,_tag,_first_label,_nb_element_type;    
    string _name;
    bool _if_is_open,_of_is_open;
    ifstream  _if;
    ofstream _of;
};


#endif // end of _COMSOL
