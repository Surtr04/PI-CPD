#include <iostream>
#include "FVLib.h"
enum{
    NULL_FORMAT=0,
    XML_FORMAT,
    GMSH_FORMAT,
    COMSOL_FORMAT
};
int main(int argc, char *argv[])
{
   
if (argc < 3) 
        {
        cout<<"Wrong format"<<endl;    
        cout<<"Convert xml->gmsh: fvcm mesh.xml mesh.msh "<<endl;
        cout<<"Convert gmsh->xml: fvcm mesh.msh mesh.xml "<<endl;
        cout<<"Convert mphtxt->xml: fvcm mesh.mphtxt mesh.xml "<<endl;
        exit(0);
        }
size_t code_in=NULL_FORMAT,code_out=NULL_FORMAT;        
string    file_in=argv[1];
string    file_out=argv[2];
size_t l;
l=file_in.length();
string label_in;label_in.insert(0,file_in,l-4,4);
l=file_out.length();
string label_out;label_out.insert(0,file_out,l-4,4);
if(!label_in.compare(".xml"))  code_in=XML_FORMAT;
if(!label_in.compare(".msh"))  code_in=GMSH_FORMAT;
if(!label_in.compare("htxt"))  code_in=COMSOL_FORMAT;
if(!label_out.compare(".xml"))  code_out=XML_FORMAT;
if(!label_out.compare(".msh"))  code_out=GMSH_FORMAT;

//cout<<"code_in="<<code_in<<", code out="<<code_out<<endl;
if(code_in==code_out) {cout<<"WARNING: same file type"<<endl;return(1);} // nothing to do
if(!code_in) {cout<<"ERROR: unknown input file format"<<endl;exit(0);}
if(!code_out) {cout<<"ERROR: unknown output file format"<<endl;exit(0);}
// treat xml->gmsh
FVMesh1D m1;
FVMesh2D m2;
FVMesh3D m3;
Gmsh mg;
Comsol mc;
if( (code_in==GMSH_FORMAT) && (code_out==XML_FORMAT))
     {
      cout<<"converting msh->xml"<<endl;
      mg.readMesh(file_in.c_str());
      if(mg.getDim()==1) 
          {cout<<"1D mesh"<<endl;
           m1.Gmsh2FVMesh(mg); 
           m1.setName("fvcm convertor");  
           m1.write(file_out.c_str());
          }
      if(mg.getDim()==2) 
          {cout<<"2D mesh"<<endl;
           m2.Gmsh2FVMesh(mg); 
           m2.setName("fcgm convertor");  
           m2.write(file_out.c_str());
          }  
      if(mg.getDim()==3) 
          {cout<<"3D mesh"<<endl;
           m3.Gmsh2FVMesh(mg); 
           m3.setName("fvcm convertor");  
           m3.write(file_out.c_str());
          }          
      cout<<"done"<<endl;
      exit(0);
     }
// treat gmsh->xml
if((code_in==XML_FORMAT) && (code_out==GMSH_FORMAT))
     {
      cout<<"converting xml->msh"<< endl;  
      if(m3.read(file_in.c_str())==FVOK) {cout<<"3D mesh"<<endl;mg.FVMesh2Gmsh(m3);}
      if(m2.read(file_in.c_str())==FVOK) {cout<<"2D mesh"<<endl;mg.FVMesh2Gmsh(m2);}      
      if(m1.read(file_in.c_str())==FVOK) {cout<<"1D mesh"<<endl;mg.FVMesh2Gmsh(m1);}
      cout<<"conversion done"<<endl;fflush(NULL);
      mg.writeMesh(file_out.c_str());
      cout<<"done"<<endl;  
      exit(0);
     }
 // treat mphtxt->xml    
if((code_in==COMSOL_FORMAT)&& (code_out==GMSH_FORMAT))
    {
    cout<<"converting mphtxt->xml"<<endl;
    mc.readMesh(file_in.c_str());
    //mc.show();
    if(argc==4) 
        {
        string file_phy=argv[3];
        mc.readComsolPhysical(file_phy.c_str());
        mc.geo2phys();
        }
    mg.Comsol2Gmsh(mc);
    //mg.show();
    mg.writeMesh(file_out.c_str());     
    cout<<"done"<<endl;  
    exit(0);
    }
cout<<"invalid combination"<<endl;    
}
