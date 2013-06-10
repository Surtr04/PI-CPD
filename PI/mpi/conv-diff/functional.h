#include "user.h"
void setDirichlet(FVMesh2D &m,FVVect<double> &Vd,Parameter &para);
void setRHS(FVMesh2D &m,FVVect<double> &rhs,Parameter &para);
void setNeumann(FVMesh2D &m,FVVect<double> &Vn,Parameter &para);
void setVelocity(FVMesh2D &m,FVVect<FVPoint2D<double> > &u,Parameter &para);
void setExactSolution(FVMesh2D &m,FVVect<double> &sol,Parameter &para);
void makeFlux(FVMesh2D &m, FVVect<double> &phi, FVVect< FVPoint2D<double> > &u,
              FVVect<double> &Vd,FVVect<double> &Vn,
              FVVect<double> &F,Parameter &para);
void makeResidual(FVMesh2D &m, FVVect<double> &phi, FVVect< FVPoint2D<double> > &u,
                  FVVect<double> &rhs,FVVect<double> &Vd,FVVect<double> &Vn,
                  FVVect<double> &G,Parameter &para);


double invSqrt(double x);
void makeResidual2(FVMesh2D &m, FVVect<double> &phi, FVVect< FVPoint2D<double> > &u,
                  FVVect<double> &rhs,FVVect<double> &Vd,FVVect<double> &Vn,
                  FVVect<double> &G,Parameter &para);