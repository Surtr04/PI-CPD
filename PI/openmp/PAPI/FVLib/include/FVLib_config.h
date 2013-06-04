// ------  FVLIB_config.h ------
#ifndef _FVLIB_Config 
#define _FVLIB_Config 

#define INF_MIN (-1.E+100)
#define SUP_MAX (1.E+100)
#define FVDOUBLE_PRECISION 1.E-17
#define FVKRYLOV_PRECISION 1.E-10
#define FVEPSI 1.E-12
#define FVPRECISION 12
#define FVCHAMP 20
#define FVCHAMPINT 10
#define FVAPAPTATIVE_MAX_DEGREE 5


#define NB_VERTEX_PER_CELL_2D 9 
#define NB_EDGE_PER_CELL_2D 9
#define NB_CELL_PER_VERTEX_2D 15  // this value is checked
#define NB_VERTEX_PER_FACE_3D 9
#define NB_EDGE_PER_FACE_3D 9
#define NB_VERTEX_PER_CELL_3D 9  
#define NB_FACE_PER_CELL_3D 9
#define NB_CELL_PER_VERTEX_3D 70// this value is checked
#define GMSH_NB_NODE_PER_ELEMENT 9
#define COMSOL_NB_NODE_PER_ELEMENT 9
//#define NB_ENTITY_PER_STENCIL 40

#define MINUS_THREE_DIM  2147483648
#define MINUS_TWO_DIM    1073741824
#define MINUS_ONE_DIM     536870912
#define FVLIB_PI 3.141592653589793238


#include <string>
#include <map>
typedef  std::map<std::string,std::string> StringMap; 



enum FVFile{
           FVNULL     =  0,
           FVOK       ,
           FVREAD     ,
           FVWRITE    ,
           FVENDFILE  ,
           FVNOFILE   ,
           FVWRONGDIM ,
           FVERROR    ,
           VERTEX     ,
           CELL       ,
};
enum FVReconstruction{
           REC_NULL = 0,
           REC_CONSERVATIVE,
           REC_NON_CONSERVATIVE,
};           
enum EntityCode{
           NULL_ENTITY=0,
           FVVERTEX1D,
           FVVERTEX2D,
           FVVERTEX3D,
           FVCELL1D,
           FVCELL2D,
           FVCELL3D,
           FVEDGE2D,
           FVEDGE3D,
           FVFACE3D,
};
enum GMSHTypeElement{
           GMSH_EDGE=1,
           GMSH_TRI,
           GMSH_QUAD,
           GMSH_TETRA,
           GMSH_HEXA,
           GMSH_PRISM,
           GMSH_PYRA,
           GMSH_NODE=15,  
};
enum BaliseCode{
           BadBaliseFormat=0,
           EndXMLFile,
           NoOpenBalise,
           NoCloseBalise,
           OkOpenBalise,
           OkCloseBalise,
           NoAttribute,
           OkAttribute,
};
#endif // define _FVLIB_Config
