// ------ FVFastRecons2D.h ------
// S. CLAIN 2013/01
#ifndef _FVFASTRECONS2D
#define _FVFASTRECONS2D
#include "FVRecons2D.h"

class FVFastRecons2D
{
private:
FVMesh2D *_ptr_m;
FVRecons2D *_rec;
vector< FVPoint2D<double> *> *_list_Point;
size_t _degree,_Ncoef,_reconstruction_type;
size_t _nb_row,_nb_col;
FVPoint2D<double> _ref_point;
FVVect<double> *_Vertex2DVect,*_Edge2DVect,*_Cell2DVect;  
FVStencil * _ptr_s;
FVVect<double> *_AValue;
FVVect<FVPoint2D<double> >*_ADerivative;

// value pour  vertex: matrice double de nb_vertex X nb_element_stencil (+1 si conservatif)
// value pour  edge : matrice double de nb_edge*nb_gauss X nb_element_stencil (+1 si conservatif)
// value pour cell : matrice double de nb_gauss_cell X nb_element_stencil (+1 si conservatif)
// pour Derivative, les matrice sont des <FVPoint2D<double> >
// la derniere colonne contient le coef pour le cas conservatif.
public:
FVFastRecons2D();  // constructor
~FVFastRecons2D(); //destructor
FVFastRecons2D(const FVFastRecons2D &frec); // copy constructor
FVFastRecons2D & operator =(const  FVFastRecons2D &frec); // assigment operator
void clean(); // clean the instance
void show(); // show the instance
//
void setMesh(FVMesh2D &m){_ptr_m=&m;}
FVMesh2D * getMesh(){return _ptr_m;}
void setStencil(FVStencil &st){ FVFastRecons2D::setStencil(&st); }      
void setStencil(FVStencil *ptr_s);
void setStencil(FVStencil &st, size_t degree){ FVFastRecons2D::setStencil(&st,degree); }      
void setStencil(FVStencil *ptr_s, size_t degree);
void setPolynomialDegree(size_t degree);   
size_t getPolynomialDegree(){return(_degree); } 
void setReferencePoint(FVPoint2D<double> P){_ref_point=P;}
void setReconstructionType(size_t rec_type){_reconstruction_type=rec_type;}
size_t getReconstructionType(){return _reconstruction_type;}
void addPoint(FVPoint2D<double> &P){FVFastRecons2D::addPoint(&P);}
void addPoint(FVPoint2D<double> *ptr_P){_list_Point->push_back(ptr_P);}
void doMatrix(); 
// 
void setVectorVertex2D( FVVect<double> & u){_Vertex2DVect=&u;}
void setVectorEdge2D( FVVect<double> & u)  {_Edge2DVect=&u;}
void setVectorCell2D( FVVect<double> & u)  {_Cell2DVect=&u;}
FVVect<double>* getVectorVertex2D( ){return _Vertex2DVect;}
FVVect<double>* getVectorEdge2D( )  {return _Edge2DVect;}
FVVect<double>* getVectorCell2D( )  {return _Cell2DVect;}
double getValue(size_t i); 
FVPoint2D<double> getDerivative(size_t i);


};
#endif // define _FVFASTRECONS2D

// a faire
// 1) dans copy construtor et assigment resize et copy des matrice
// 2) faire doRec 
// 3) faire les getValue et getDerivativeOncell