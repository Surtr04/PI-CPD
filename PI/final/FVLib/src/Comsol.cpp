#include "Comsol.h"
#include <cstring>
#include <cstdlib>
#include "Gmsh.h"

Comsol::Comsol()
{
  _if_is_open=false,_of_is_open=false; _dim=0; _nb_node=0;_nb_element=0;
}  

Comsol::Comsol(const char *filename)
{
    Comsol::readMesh(filename);
    
}

Comsol::~Comsol()
{
  Comsol::close();
} 

/*--------- read and write mesh -----------*/
//
//  close
//
void Comsol::close()
{
 if(_if_is_open) {_if.close();_if_is_open=false;}
 if(_of_is_open) {_of.close();_of_is_open=false;} 
} 
//
// open and read
//
void Comsol::readMesh(const char *filename)
{
if(_if_is_open)
            {
             cout<<" error opening file:"<<filename<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
             cout<<" an open file exists yet"<<endl;
             exit(0);
            }    
_if.open(filename);
if(!_if.is_open())
            {
             cout<<" error opening file:"<<filename<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
             cout<<" file does not exist"<<endl;
             exit(0);
            }
_if_is_open=true;    
_dim=0;
_name="comsol_mesh";
size_t filesize;
_if.seekg( -1, ios_base::end );
filesize=_if.tellg();
char *ptr,*file_string,auxString[255];
file_string=(char *)malloc(filesize+2);
size_t pos,value;
double f_value=0.;
f_value+=1;// just to avoid the warning
_if.seekg(0);
pos=0;
while (!_if.eof())// read the file
      {
      file_string[pos]=(char) _if.get();
      pos++;
      }     
// the file is now in the string, we now can sparse the data
cleanString(file_string); // remove all the comment and carriage return
// read the header
ptr=file_string;  // pointer to the begining
value= strtoul(ptr, &ptr,0); //the major
value= strtoul(ptr, &ptr,0); //the minor
// ------ tag parameter ----
_tag= strtoul(ptr, &ptr,0); //the number of tag
if(_tag!=1){ cout<<"error tag number in parsing .mphtxt file , must be 1"<<endl; exit(0);}
value= strtoul(ptr, &ptr,0);// first tag (shoud be 5 for the name)
//cout << " the first tag number "<< value << endl;fflush(NULL);
strtos(ptr, &ptr,auxString);// read the name 
//cout << "file name:"<< auxString<<endl;fflush(NULL);
_name.assign(auxString); //keep the file name
// ------ type parameter ----
value= strtoul(ptr, &ptr,0);// number of type shoud be 1
//cout<<" number of type"<<value<<endl;
if(value!=1){ cout<<"error type number in parsing .mphtxt file , must be 1"<<endl; exit(0);}
value= strtoul(ptr, &ptr,0);// type shoud be 3
//cout<<"type value"<<value<<endl;fflush(NULL);
strtos(ptr, &ptr,auxString);// read the type should be obj
//cout << "type="<<auxString << endl;fflush(NULL);
//  read the 0 0 1 sequence
value= strtoul(ptr, &ptr,0);value= strtoul(ptr, &ptr,0);value= strtoul(ptr, &ptr,0);
// -----  mesh parameter ---
value= strtoul(ptr, &ptr,0);// number shoud be 4
//cout<<"mesh value"<<value<<endl;fflush(NULL);
strtos(ptr, &ptr,auxString);// keyword should be mesh
//cout << "keyword="<<auxString << endl;fflush(NULL);
value= strtoul(ptr, &ptr,0);// version shoud be 4
//cout<<"version:"<<value<<endl;fflush(NULL);
_dim= strtoul(ptr, &ptr,0);// dimension
//cout<<"dim="<<_dim<<endl;fflush(NULL);
_nb_node=strtoul(ptr, &ptr,0);// number of node
//cout<<"nb of vertex="<<_nb_node<<endl;fflush(NULL);
_first_label=strtoul(ptr, &ptr,0);// first label
//cout<<"first_label="<<_first_label<<endl;fflush(NULL);
// ----  load all the vertex ----
_node.resize(_nb_node); 
for(size_t i=0;i<_nb_node;i++)
    {
     _node[i].label  = i+1;
     _node[i].coord.x= strtod(ptr, &ptr);
     if(_dim>1) _node[i].coord.y= strtod(ptr, &ptr);     
     if(_dim>2) _node[i].coord.z= strtod(ptr, &ptr);     
    }
// ---  load all the element ---
size_t type_element=GMSH_NODE,dim_element=0;
size_t nb_node_per_element,nb_of_element,nb_parameter_values_per_element;
size_t nb_parameters,nb_geometric_entity_indices,nb_up_down_pairs;
_nb_element_type=strtoul(ptr, &ptr,0);// number of element type
//cout<<"nb element type="<<_nb_element_type<<endl;fflush(NULL);
size_t ref_label_element;
CSElement current_element;
for(size_t i=0;i<_nb_element_type;i++)
    {
    value= strtoul(ptr, &ptr,0);// 
    //cout<<"number of character="<<value<<endl;fflush(NULL);
    strtos(ptr, &ptr,auxString);// read the type should be obj
    //cout << "element type="<<auxString << endl;fflush(NULL);
    if(!strcmp(auxString,"vtx"))   {type_element=GMSH_NODE;dim_element=0;}
    if(!strcmp(auxString,"edg"))   {type_element=GMSH_EDGE;dim_element=1;}
    if(!strcmp(auxString,"tri"))   {type_element=GMSH_TRI;dim_element=2;}
    if(!strcmp(auxString,"quad"))  {type_element=GMSH_QUAD;dim_element=2;}
    if(!strcmp(auxString,"hex"))   {type_element=GMSH_HEXA;dim_element=3;}    
    if(!strcmp(auxString,"tet"))   {type_element=GMSH_TETRA;dim_element=3;}
    if(!strcmp(auxString,"prism")) {type_element=GMSH_PRISM;dim_element=3;}
    if(!strcmp(auxString,"pyr"))   {type_element=GMSH_PYRA;dim_element=3;}
    ref_label_element=_element.size();
// read the elements of the current type
    nb_node_per_element=strtoul(ptr, &ptr,0);
    //cout<<"nb_node_per_element="<<nb_node_per_element<<endl;fflush(NULL);
    nb_of_element=strtoul(ptr, &ptr,0);
    //cout<<"nb_of_element="<<nb_of_element<<endl;fflush(NULL);
    for(size_t j=0;j<nb_of_element;j++)
        {
        current_element.label=_element.size()+1;
        current_element.type_element=type_element;
        current_element.code_elementary=0;
        current_element.code_physical=0;
        current_element.nb_node=nb_node_per_element;
        current_element.dim=dim_element;
        for(size_t k=0;k<nb_node_per_element;k++)    
            current_element.node[k]= strtoul(ptr, &ptr,0)+1;   // careful comsol start the label with 0.
        _element.push_back(current_element);
        }    
    nb_parameter_values_per_element=strtoul(ptr, &ptr,0);
    //cout<<"nb_parameter_values_per_element="<< nb_parameter_values_per_element<<endl;fflush(NULL);
    nb_parameters=strtoul(ptr, &ptr,0);
    //cout<<"nb_parameters="<<nb_parameters<<endl;fflush(NULL);
    for(size_t j=0;j<nb_parameters;j++)
        {
        for(size_t k=0;k<nb_parameter_values_per_element;k++)    
            f_value= strtod(ptr, &ptr);   
        }           
    nb_geometric_entity_indices=strtoul(ptr, &ptr,0);// same thing than domain
    //cout<<"nb_geometric_entity_indices="<<nb_geometric_entity_indices<<endl;fflush(NULL);
    if(nb_geometric_entity_indices==nb_of_element) // the domain or geometric corresponds to the gmsh geometry number
        {
        for(size_t j=0;j<nb_geometric_entity_indices;j++)
            {
            _element[ref_label_element+j].code_elementary= strtoul(ptr, &ptr,0);   
            }
        }
    else
         {
        for(size_t j=0;j<nb_geometric_entity_indices;j++)
            {
            value= strtoul(ptr, &ptr,0);   
            }
        for(size_t j=0;j<nb_of_element;j++)
            {
            _element[ref_label_element+j].code_physical=0;   
            }            
        }       
    nb_up_down_pairs=strtoul(ptr, &ptr,0);
    //cout<<"nb_up_down_pairs="<<nb_up_down_pairs<<endl;fflush(NULL);
    for(size_t j=0;j<nb_up_down_pairs;j++)
        {
        value= strtoul(ptr, &ptr,0);   value= strtoul(ptr, &ptr,0); 
        }
    //cout<<"---- end element treatment ---"<<endl;    
    }
_nb_element=_element.size();
// we have fill all the comsol structure
free(file_string); // free the memory  and leave
}

//
// open and write
//
void Comsol::writeMesh(const char *filename)
{
if(_of_is_open==true)
    { 
    cout<<"a file is still open: close it before writing a mesh"<<endl;
    }

if((_nb_node==0) || (_nb_element==0))
            {
             cout<<" error in file:"<<filename<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
             cout<<" there is no mesh to save"<<endl;
             return;
            }       
_of.open(filename);
if(!_of.is_open())
            {
             cout<<" error in file:"<<filename<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
             cout<<" can not create the file"<<endl;
             return;
            }
_of_is_open=true;_nb_save=0;     
cout<<"the function is not implemented, sorry"<<endl;
}
//  clean the string, remove all the comment and carriage return (substituted with blank)
void Comsol::cleanString(char *the_string)
{
size_t len,pos;
len=strlen(the_string);
pos=0;
while(pos<len)
    {
    switch((size_t)the_string[pos])
        {
        case 35:
        while((the_string[pos]!=10) && (the_string[pos]!=13))
            the_string[pos++]=32;
        break; 
        case 10:
            the_string[pos++]=32;
        break;
        case 13:
            the_string[pos++]=32;
        break;
        default :
            pos++;
       }
    }
}
void Comsol::show()
{
cout<<"number of node:"<<_nb_node<<"number of element:"<<_nb_element<<" dim="<<_dim<<endl;    
for(size_t i=0;i<_nb_node;i++)
    {
    cout<<"node "<<i<<" with coordinate"<< _node[i].coord.x<<"," << _node[i].coord.y
    <<"," << _node[i].coord.z<<endl;
    }
for(size_t i=0;i<_nb_element;i++)
    {
    cout<<"element "<<i<<" of type"<< _element[i].type_element
    <<"  nb node:" << _element[i].nb_node<<" code elementary:"<<_element[i].code_elementary
    <<", code physical:"<<_element[i].code_physical<<endl;
    cout<<"node labels are:";
    for(size_t j=0;j<_element[i].nb_node;j++)
        cout<<" "<<_element[i].node[j];    
    cout<<endl;
    }    
}
//
//------------- CONVERTISOR  -----------------
//
void Comsol::readComsolPhysical(const char *filename)
{
_cp.readTable(filename);    
}
void Comsol::Gmsh2Comsol(Gmsh &gm)  // convert a Gmsh struct into a Comsol
{
_node.resize(_nb_node=gm.getNbNode());
_element.resize(_nb_element=gm.getNbElement());
//cout<<"nb node"<<_nb_node<<" nb_element"<<_nb_element<<endl;
_dim=gm.getDim();
_name=gm.getName();
for(size_t i=0;i<_nb_node;i++)  // copy the nodes
    {
    _node[i]=(*gm.getNode(i));  
    }
for(size_t i=0;i<_nb_element;i++)  // copy the elements
    {
     GMElement GMel;
     GMel=(*gm.getElement(i)); 
     _element[i].label=GMel.label;
     _element[i].type_element=GMel.type_element;
     _element[i].code_physical=GMel.code_physical; 
     _element[i].code_elementary=GMel.code_elementary;
     _element[i].nb_node=GMel.nb_node;
     _element[i].dim=GMel.dim;
     for(size_t j=0;j<GMel.nb_node;j++)
         _element[i].node[j]=GMel.node[j];
    } 
}
 void Comsol::geo2phys()
 {
FVPoint2D<size_t > geo2phy;
size_t nbCodeVertex,nbCodeEdge, nbCodeFace,nbCodeCell;
size_t geo_code;
nbCodeVertex=_cp.getNbCodeVertex();
nbCodeEdge=_cp.getNbCodeEdge();
nbCodeFace=_cp.getNbCodeFace();
nbCodeCell=_cp.getNbCodeCell();
//_cp.show(); fflush(NULL);
//cout<<"nb of element="<<_nb_element<<endl;
 for(size_t i=0;i<_nb_element;i++)  // copy the elements
    {    
    geo_code=_element[i].code_elementary;
//    cout<<"label="<<i<<", code geo="<<geo_code<<" dim="<<_element[i].dim<<endl;
 
    switch(_element[i].dim)
        {
        case 0: 
        for(size_t j=0;j<nbCodeVertex;j++)
            {
            if(geo_code==_cp.getCodeVertex(j).x) _element[i].code_physical=_cp.getCodeVertex(j).y;    
            }
        break;
        case 1: 
        for(size_t j=0;j<nbCodeEdge;j++)
            {
            if(geo_code==_cp.getCodeEdge(j).x) _element[i].code_physical=_cp.getCodeEdge(j).y;    
            }
        break;
        case 2: 
        for(size_t j=0;j<nbCodeFace;j++)
            {
            if(geo_code==_cp.getCodeFace(j).x) _element[i].code_physical=_cp.getCodeFace(j).y;    
            }
        break;
        case 3: 
        for(size_t j=0;j<nbCodeCell;j++)
            {
            if(geo_code==_cp.getCodeCell(j).x) _element[i].code_physical=_cp.getCodeCell(j).y;    
            }
        break;        
        default:
        cout<<" error  in "<<__FILE__<< " line "<<__LINE__<<endl; 
        cout<<" dim element is not correct, read"<<_element[i].dim<<endl;  
        }
       
    }
 }






































ComsolPhysical::ComsolPhysical()
{
_codeVertex.resize(0);
_codeEdge.resize(0);
_codeFace.resize(0);
_codeCell.resize(0);
}  

ComsolPhysical::ComsolPhysical(const char *filename)
{
    ComsolPhysical::readTable(filename); 
}

ComsolPhysical::~ComsolPhysical()
{
_codeVertex.resize(0);
_codeEdge.resize(0);
_codeFace.resize(0);
_codeCell.resize(0);  
} 
void ComsolPhysical::show()
{   
cout<<"nbCodeVertex="<< _codeVertex.size()<<", nbCodeEdge="<<_codeEdge.size()<<", nbCodeFace="
    <<_codeFace.size()<<", nbCodeCell="<<_codeCell.size()<<endl;
}
//
// open and read
//
void ComsolPhysical::readTable(const char *filename)
{
string xml_files,key,value; 
StringMap attribute; 
StringMap::iterator iter;
SparseXML spxml(filename,xml_files);
size_t code,level;
// open  balise FVLIB 
code=spxml.openBalise("FVLIB");
if (code!=OkOpenBalise)
       {cout<<" No open VFLIB balise found:"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; exit(1);}
// ok it is an FVLIB filename now find the COMSOL_PHYSICAL  balise
code=spxml.openBalise("COMSOL_PHYSICAL");
if (code!=OkOpenBalise)
       {cout<<" No open COMSOL_PHYSICAL balise found:"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; exit(1);}
level=spxml.getLevel();            
FVPoint2D<size_t> geo2phys;


    // the vertex code
code=spxml.openBalise("ComsolVertex",level);
if(code==BadBaliseFormat) 
      {
      cout<<" BadBaliseFormat in parameter balise :"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
      exit(1) ;
      } 
if(code==EndXMLFile)  return ;
if(code==OkOpenBalise)
   {// ok, we have a Balise parameter
   attribute=spxml.getAttribute();              
   iter = attribute.begin(); 
   key=iter->first;value=iter->second; 
   //cout << "Key: '" << key << "', Value: " << value << endl;
   int nbCodeVertex=0;
   if(key=="nbVertexCode") nbCodeVertex=atoi(value.c_str()); 
//   cout<<"nbCodeVertex="<<nbCodeVertex<<endl; 
   _codeVertex.resize(nbCodeVertex);
   spxml.data();
       {
       size_t beginDATA=spxml.getPosition();
       size_t lengthDATA=spxml.getLength();
       char  thedata[lengthDATA+1],*ptr;
       xml_files.copy(thedata,lengthDATA,beginDATA);
       thedata[lengthDATA]=0;
       ptr=thedata;
       for(int i=0;i<nbCodeVertex;i++)
           {
           geo2phys.x=   strtod(ptr, &ptr);
           geo2phys.y=   strtod(ptr, &ptr);    
           _codeVertex[i]=geo2phys;            
           }
       }    
   code=spxml.closeBalise("ComsolVertex");
   }
   
   
   
   // the edge code 
code=spxml.openBalise("ComsolEdge",level);
if(code==BadBaliseFormat) 
      {
      cout<<" BadBaliseFormat in parameter balise :"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
      exit(1) ;
      } 
if(code==EndXMLFile)  return ;
if(code==OkOpenBalise)
   {// ok, we have a Balise parameter
   attribute=spxml.getAttribute();              
   iter = attribute.begin(); 
   key=iter->first;value=iter->second; 
   //cout << "Key: '" << key << "', Value: " << value << endl;
   int nbCodeEdge=0;
   if(key=="nbEdgeCode") nbCodeEdge=atoi(value.c_str()); 
//   cout<<"nbCodeEdge="<<nbCodeEdge<<endl; 
   _codeEdge.resize(nbCodeEdge);
   spxml.data();
       {
       size_t beginDATA=spxml.getPosition();
       size_t lengthDATA=spxml.getLength();
       char  thedata[lengthDATA+1],*ptr;
       xml_files.copy(thedata,lengthDATA,beginDATA);
       thedata[lengthDATA]=0;
       ptr=thedata;
       for(int i=0;i<nbCodeEdge;i++)
           {
           geo2phys.x=   strtod(ptr, &ptr);
           geo2phys.y=   strtod(ptr, &ptr);    
           _codeEdge[i]=geo2phys;            
           }
       }     
   code=spxml.closeBalise("ComsolEdge");
   }
   
   
   
   // the face code 
code=spxml.openBalise("ComsolFace",level);
if(code==BadBaliseFormat) 
      {
      cout<<" BadBaliseFormat in parameter balise :"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
      exit(1) ;
      } 
if(code==EndXMLFile)  return ;
if(code==OkOpenBalise)
   {// ok, we have a Balise parameter
   attribute=spxml.getAttribute();              
   iter = attribute.begin(); 
   key=iter->first;value=iter->second; 
   //cout << "Key: '" << key << "', Value: " << value << endl;
   int nbCodeFace=0;
   if(key=="nbFaceCode") nbCodeFace=atoi(value.c_str()); 
//   cout<<"nbCodeFace="<<nbCodeFace<<endl; 
   _codeFace.resize(nbCodeFace);
   spxml.data();
       {
       size_t beginDATA=spxml.getPosition();
       size_t lengthDATA=spxml.getLength();
       char  thedata[lengthDATA+1],*ptr;
       xml_files.copy(thedata,lengthDATA,beginDATA);
       thedata[lengthDATA]=0;
       ptr=thedata;
       for(int i=0;i<nbCodeFace;i++)
           {
           geo2phys.x=   strtod(ptr, &ptr);
           geo2phys.y=   strtod(ptr, &ptr);    
           _codeFace[i]=geo2phys;            
           }
       }
   code=spxml.closeBalise("ComsolFace");
   }
   
   
   
    // the cell code 
code=spxml.openBalise("ComsolCell",level);
if(code==BadBaliseFormat) 
      {
      cout<<" BadBaliseFormat in parameter balise :"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; 
      exit(1) ;
      } 
if(code==EndXMLFile)  return ;
if(code==OkOpenBalise)
   {// ok, we have a Balise parameter
   attribute=spxml.getAttribute();              
   iter = attribute.begin(); 
   key=iter->first;value=iter->second; 
   //cout << "Key: '" << key << "', Value: " << value << endl;
   int nbCodeCell=0;
   if(key=="nbCellCode") nbCodeCell=atoi(value.c_str()); 
   //cout<<"nbCodeCell="<<nbCodeCell<<endl; 
   _codeCell.resize(nbCodeCell);
   spxml.data();
       {
       size_t beginDATA=spxml.getPosition();
       size_t lengthDATA=spxml.getLength();
       char  thedata[lengthDATA+1],*ptr;
       xml_files.copy(thedata,lengthDATA,beginDATA);
       thedata[lengthDATA]=0;
       ptr=thedata;
       for(int i=0;i<nbCodeCell;i++)
           {
           geo2phys.x=   strtod(ptr, &ptr);
           geo2phys.y=   strtod(ptr, &ptr);    
           _codeCell[i]=geo2phys;            
           }
       }
   code=spxml.closeBalise("ComsolCell");
   }  
   
   
   
   
 // close  Balise  COMSOL_PHYSICAL
code=spxml.closeBalise("COMSOL_PHYSICAL");
if (code!=OkCloseBalise)
       {cout<<" No close COMSOL_PHYSICAL balise found:"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; exit(1);}     
// close  Balise   FVLIB   
code=spxml.closeBalise("FVLIB");
if (code!=OkCloseBalise)
       {cout<<" No close VFLIB balise found:"<<"  in "<<__FILE__<< " line "<<__LINE__<<endl; exit(1);}
}

