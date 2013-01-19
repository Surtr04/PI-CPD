#include "functional.h"
#include <omp.h>



double invSqrt(double x) {
    double xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(double*)&i;
    x = x*(1.5f-xhalf*x*x);
    
    return x;
}

// compute source term
void setRHS(FVMesh2D &m,FVVect<double> &rhs,Parameter &para) {     
    FVCell2D *ptr_c;  
    m.beginCell();

    while((ptr_c=m.nextCell())) {
        rhs[ptr_c->label-1]=ptr_c->getMeanValue(RHS,para);
    }   
} 



// initialize the Dirichelt vector
void setDirichlet(FVMesh2D &m,FVVect<double> &Vd,Parameter &para) {
    FVEdge2D *ptr_e;    
    m.beginEdge();
    while((ptr_e=m.nextEdge())) {     
        Vd[ptr_e->label-1]=ptr_e->getMeanValue(Dirichlet,para);
    }     
}



// initialize the Neumann vector
void setNeumann(FVMesh2D &m,FVVect<double> &Vn,Parameter &para) {  
    FVEdge2D *ptr_e;    
    m.beginEdge();
    while((ptr_e=m.nextEdge())) {        
        Vn[ptr_e->label-1]=ptr_e->getMeanValue(Neumann,para);
    } 
} 


// initialize the velocity
void setVelocity(FVMesh2D &m,FVVect<FVPoint2D<double> > &u,Parameter &para) {  
    FVEdge2D *ptr_e;    
    m.beginEdge();
    
    while((ptr_e=m.nextEdge())) {        
        u[ptr_e->label-1].x=Xvelocity(ptr_e->centroid,para);
        u[ptr_e->label-1].y=Yvelocity(ptr_e->centroid,para);
    } 
} 


// initialize exact solution
void setExactSolution(FVMesh2D &m,FVVect<double> &sol,Parameter &para) {     
    FVCell2D *ptr_c;  
    m.beginCell();
    while((ptr_c=m.nextCell())) {
        sol[ptr_c->label-1]=ptr_c->getMeanValue(solExact,para);
    }   
}  




void makeFlux(FVMesh2D &m, FVVect<double> &phi, FVVect< FVPoint2D<double> > &u,
              FVVect<double> &Vd,FVVect<double> &Vn,
              FVVect<double> &F,Parameter &para) {

    FVEdge2D *ptr_e;
    double leftPhi,rightPhi,normal_velocity;
    FVPoint2D<double> BB;
    m.beginEdge();

    //avoid getting static values in loops
    const unsigned int dirCode = para.getUnsigned("DirichletCode");
    const unsigned int neuCode = para.getUnsigned("NeumannCode");
    const double difusion = getDiffusion(ptr_e,para);

    //for(ptr_e = m.beginEdge(); m.nextEdge(); ptr_e = m.nextEdge )
    while((ptr_e=m.nextEdge())) {    
        
        normal_velocity=Dot(u[ptr_e->label-1],ptr_e->normal);  
        leftPhi=phi[ptr_e->leftCell->label-1];
        
        if(ptr_e->rightCell) {
            // edge has the code = 0    
            rightPhi=phi[ptr_e->rightCell->label-1];
            // compute the convection contribution
            if(normal_velocity<0)
                F[ptr_e->label-1]=normal_velocity*rightPhi;
            else
                F[ptr_e->label-1]=normal_velocity*leftPhi;   
            // compute the diffusive contribution
            BB=ptr_e->rightCell->centroid-ptr_e->leftCell->centroid;            
            
            F[ptr_e->label-1]-=difusion*(rightPhi-leftPhi)/Norm(BB); 

        }
    else {
        //  we are on the boundary
        if(ptr_e->code == dirCode) {
            
            // we have a Dirichlet condition
            rightPhi=Dirichlet(ptr_e->centroid,para);
            // compute the convection contribution
            if(normal_velocity<0)
                F[ptr_e->label-1]=normal_velocity*rightPhi;
            else
                F[ptr_e->label-1]=normal_velocity*leftPhi;   
            // compute the diffusive contribution
            BB=ptr_e->centroid-ptr_e->leftCell->centroid;
            F[ptr_e->label-1]-=difusion*(rightPhi-leftPhi)/Norm(BB); 
            }
         if(ptr_e->code == neuCode) {
            // we have a Neumann condition 
            F[ptr_e->label-1]=Neumann(ptr_e->centroid,para);
            }
        }

    // here, we have all the data to compute the flux
    F[ptr_e->label-1]*=ptr_e->length;
    }
}

void makeResidual(FVMesh2D &m, FVVect<double> &phi, FVVect< FVPoint2D<double> > &u,
                  FVVect<double> &rhs,FVVect<double> &Vd,FVVect<double> &Vn,
                  FVVect<double> &G,Parameter &para) {

    FVEdge2D *ptr_e;   
    FVCell2D *ptr_c;
    FVVect<double> F(m.getNbEdge());
    makeFlux(m,phi,u,Vd,Vn,F,para);
    G=0.;
    m.beginEdge();

    //#pragma omp parallel for
    for(unsigned int i = 0; i < m.getNbEdge(); i++) {
        
        ptr_e=m.nextEdge();
        
        
        ptr_c=ptr_e->leftCell;
        G[ptr_c->label-1]+=F[ptr_e->label-1];
        
        if((ptr_c=ptr_e->rightCell)) {
            G[ptr_c->label-1]-=F[ptr_e->label-1];    
        }        
    }    

    for(size_t j=0;j<m.getNbCell();j++) {
        G[j]/=m.getCell(j)->area;   
        G[j]-=rhs[j];
    }
}
