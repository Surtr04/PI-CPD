#include <cuda.h>
#include "functional.h"




__host__ void prepareMakeFluxCUDA (FVMesh2D &m, FVVect<double> &phi, FVVect< FVPoint2D<double> > &u,
    					          FVVect<double> &Vd,FVVect<double> &Vn, FVVect<double> &F,Parameter &para) {


	FVEdge2D edges[m.getNbEdge()];





}


__device__ void makeFluxCUDA() {

}

