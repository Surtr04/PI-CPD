//#include "functional.h"
#include "user.h"
#include <omp.h>
#include <limits>
#include <iostream>

void computeFlux (FVMesh2D &m,
                  double *phi, 
                  double *normal_velocities,
                  FVPoint2D<double>* normals,                  
                  double *F,
                  unsigned *left,
                  unsigned *right,
                  FVPoint2D<double> *centroid,
                  double *code,  
                  double *length,                
                  unsigned num_edges,
                  unsigned int dirCode,
                  unsigned int neuCode,
                  double diffusion,
                  Parameter &para) {

    double normal_vel;
    FVPoint2D<double> BB;
    unsigned i;

    #pragma omp parallel for
    for(i = 0; i < num_edges; ++i) {

        normal_vel = normal_velocities[i];

        if(right[i] < numeric_limits<unsigned>::max()) {

            normal_vel < 0 ? F[i] = normal_vel * phi[ right[i] ] : 
                             F[i] = normal_vel * phi[ left[i] ];

            BB = centroid[right[i]] - centroid[left[i]];
            F[i] -= diffusion * (phi[right[i]] - phi[left[i]])/Norm(BB);

        }
        else {
            if(code[i] == dirCode) {

                normal_vel < 0 ? F[i] = normal_vel * Dirichlet(centroid[i],para) :
                                        normal_vel * phi[left[i]];

                BB = centroid[i] - centroid[left[i]];
                F[i] -= diffusion * (phi[right[i]] - phi[left[i]])/Norm(BB);
            }

            if(code[i] == neuCode) {
                F[i] = Neumann(centroid[i],para);
            }
        }

        F[i] *= length[i];

    }


}

void computeResidual(FVMesh2D &m, 
                     double *phi, 
                     double *rhs, 
                     double *Vd, 
                     double *Vn, 
                     double *G, 
                     unsigned *left, 
                     unsigned *right, 
                     double *areas,
                     unsigned num_cells, 
                     unsigned num_edges,
                     double *normal_velocities,
                     FVPoint2D<double>* normals,
                     double *length,
                     FVPoint2D<double> *centroid,
                     double *code,                       
                     unsigned int dirCode,
                     unsigned int neuCode,
                     double diffusion,
                     Parameter &para) {

    double *F = new double[num_edges];
    computeFlux(m,phi,normal_velocities,normals,F,left,right,centroid,code,
                length,num_edges,dirCode,neuCode,diffusion,para);            
    memset(G, 0, num_cells);
    unsigned i;

    
    for (i = 0; i < num_edges; ++i) {
        
        #pragma omp atomic
        G[i] += F[i];

        if(right[i] < numeric_limits<unsigned>::max()) {
            #pragma omp atomic
            G[i] -= F[i];            
        }

    }
    
    for(unsigned i = 0; i < num_cells; ++i) {
        G[i] /= areas[i];
        G[i] -= rhs[i];
    }
}

int main() {
// declaration
    Parameter para("param.xml");    
    FVMesh2D m(para.getString("meshfile").c_str());
    cout<<"number of cells=" << m.getNbCell() << " and vertices=" << m.getNbVertex() << endl;
    
    //FVVect<double> phi(m.getNbCell());//G(m.getNbCell());
    // FVVect<FVPoint2D<double> > u(m.getNbEdge());
    // FVVect<double> F(m.getNbEdge()), Vd(m.getNbEdge()), Vn(m.getNbEdge());
    // FVVect<double> Vphi(m.getNbVertex());
    // FVVect<double> b(m.getNbCell()),rhs(m.getNbCell()),sol(m.getNbCell()),error(m.getNbCell());
     FVDenseM<double> A(m.getNbCell());

    const unsigned num_cells = m.getNbCell();
    const unsigned num_edges = m.getNbEdge();
    const unsigned int dirCode = para.getUnsigned("DirichletCode");
    const unsigned int neuCode = para.getUnsigned("NeumannCode");
    const double diffusion = getDiffusion(NULL,para);

    double* phi = new double[num_cells];
    double* G = new double[num_cells];
    double* rhs = new double[num_cells];
    double* b = new double[num_cells];
    double* sol = new double[num_cells];
    double* error = new double[num_cells];
    double* areas = new double[num_cells];
    
    double* F = new double[num_edges];
    double* Vd = new double[num_edges];
    double* Vn = new double[num_edges];
    unsigned* left = new unsigned[num_cells];
    unsigned* right = new unsigned[num_cells];
    FVPoint2D<double>* normals = new FVPoint2D<double>[num_edges];
    double* normal_velocities = new double[num_edges];
    FVPoint2D<double>* centroid = new FVPoint2D<double>[num_edges];
    double* code = new double[num_edges];
    double* length = new double[num_edges];


    for(unsigned e = 0; e < num_edges; ++e) {

        FVEdge2D *edge = m.getEdge(e);
        FVPoint2D<double> p;
        
        p.x = Xvelocity(edge->centroid,para);
        p.y = Xvelocity(edge->centroid,para);

        normal_velocities[e] = Dot(p,edge->normal);        
        left[e] = edge->leftCell->label - 1;
        right[e] = ( edge->rightCell ) ? edge->rightCell->label - 1 : numeric_limits<unsigned>::max();
        Vd[e] = edge->getMeanValue(Dirichlet,para);
        Vn[e] = edge->getMeanValue(Neumann,para);       
        normals[e] = edge->normal;  
        centroid[e] = edge->centroid;
        code[e] = edge->code;
        length[e] = edge->length;

    }    

    for(unsigned c = 0; c < num_cells; ++c) {

        FVCell2D *cell = m.getCell(c);
        rhs[c] = cell->getMeanValue(RHS,para);
        sol[c] = cell->getMeanValue(solExact,para);
        areas[c] = cell->area;               

    }





    // declaration done
    //
    // initialisation
    // setDirichlet(m,Vd,para);
    // setNeumann(m,Vn,para);
    // setRHS(m,rhs,para);
    // setVelocity(m,u,para);
    // setExactSolution(m,sol,para);
    // phi=0.;
    memset(phi, 0, num_cells);
    // // initialisation done
    // //
    // // solving the system
    //   // compute b    

    computeResidual(m,phi,rhs,Vd,Vn,G,left,right,areas,num_cells,num_edges,normal_velocities,normals,length,centroid,code,dirCode,neuCode,diffusion,para);
     //makeResidual(m,phi,u,rhs,Vd,Vn,b,para);b*=-1;
    //      // compute the matrix
    // FVCell2D *ptr_c;
    // m.beginCell();

    unsigned i;
    
    for (i = 0; i < num_cells; ++i) {

        phi[i] = 1;
        printf("compute line number =%u      \r",i+1);fflush(NULL);
        computeResidual(m,phi,rhs,Vd,Vn,G,left,right,areas,num_cells,num_edges,normal_velocities,normals,length,centroid,code,dirCode,neuCode,diffusion,para);
        
        // for (unsigned j = 0; j < num_cells; ++i) {            
        //     G[i] += b[i];
        // }
        //A.setColumn(i,G);
        phi[i] = 0;

    }

    // while((ptr_c = m.nextCell()))    {
    //     size_t i=ptr_c->label-1;
    //     phi[i]=1;
    //     printf("compute line number =%lu      \r",i+1);fflush(NULL);
    //     makeResidual(m,phi,u,rhs,Vd,Vn,G,para); 
    //     G+=b;
    //     A.setColumn(i,G);
    //     phi[i]=0;
    // }


    //  //Resolution of the linear systemcout<<endl;
    // cout<<"Solving the linear system"<<endl;
    // A.LUFactorize();
    // A.ForwardSubstitution(b) ;
    // A.BackwardSubstitution(b) ;
    // phi=b;


    // // write on file    
    // FVio result_file(para.getString("outCfile").c_str(),FVWRITE);
    // result_file.put(phi,0.0,"phi");
    // result_file.put(sol,0.0,"exact");
    // error=phi-sol;result_file.put(error,0.0,"the_error");
    // FVio result_fileV(para.getString("outVfile").c_str(),FVWRITE);
    // result_fileV.put(Vphi,0.0,"phi");
    

    // // we compute the errors
    // double err1,errinf;
    // errinf=NormMax(error);
    // err1=0.;
    // m.beginCell();
    // while((ptr_c=m.nextCell())) {
    //     err1+=abs(error[ptr_c->label-1])*ptr_c->area;    
    // }
    

    // printf("error 1:%e      error infty:%e      \n",err1,errinf);

    delete[] G;
    delete[] phi;
    delete[] areas;
    delete[] code;
    delete[] centroid;
    delete[] Vn;
    delete[] Vd;
    delete[] b;

    
    return 0;
}