#include "functional.h"
#include <mpi.h>

    // while((ptr_c = m.nextCell())) {
    //     size_t i = ptr_c->label-1;                        
    //     //printf ("%d\n",ptr_c->label);            
    //     phi[i]=1;
    //     //printf("compute line number =%lu      \r",i+1);fflush(NULL);        
    //     makeResidual(m,phi,u,rhs,Vd,Vn,G,para); 
    //     G+=b;
    //     A.setColumn(i,G);
    //     phi[i]=0;

    //     }
    //     MPI::COMM_WORLD.Send(&b[0], b.size(), MPI::DOUBLE, 1, 0);                             
    // }

#define TAG_SIZE 0
int rank;
int size;

int contructMatrix(FVMesh2D &m,FVVect<double> &phi, FVVect<double> &G, FVVect<FVPoint2D<double> > &u,
                    FVVect<double> &F, FVVect<double> &Vd, FVVect<double> &Vn, FVVect<double> &b, FVVect<double> &Vphi,
                    FVVect<double> &rhs, FVVect<double> &sol, FVVect<double> &error, FVDenseM<double> &A, Parameter &para) {
    FVCell2D *ptr_c;
    if(rank == 0) {
        while((ptr_c = m.nextCell())) {
        size_t i = ptr_c->label-1;                                
        phi[i]=1;        
        makeResidual(m,phi,u,rhs,Vd,Vn,G,para); 
        G+=b;
        A.setColumn(i,G);
        phi[i]=0;

        }        
    }    

    return 0;
}


int main(int argc, char **argv) {


    MPI::Status status;    
    MPI::Init(argc,argv);    
    rank = MPI::COMM_WORLD.Get_rank();    
    size = MPI::COMM_WORLD.Get_size();    


    Parameter para("param.xml");
    FVMesh2D m(para.getString("meshfile").c_str());
    cout<<"number of cells="<<m.getNbCell()<<" and vertices="<<m.getNbVertex()<<endl;
    


    FVVect<double> phi(m.getNbCell()),G(m.getNbCell());
    FVVect<FVPoint2D<double> > u(m.getNbEdge());
    FVVect<double> F(m.getNbEdge()), Vd(m.getNbEdge()), Vn(m.getNbEdge());
    FVVect<double> Vphi(m.getNbVertex());
    FVVect<double> b(m.getNbCell()),rhs(m.getNbCell()),sol(m.getNbCell()),error(m.getNbCell());
    FVDenseM<double> A(m.getNbCell());
    
    setDirichlet(m,Vd,para);
    setNeumann(m,Vn,para);
    setRHS(m,rhs,para);
    setVelocity(m,u,para);
    setExactSolution(m,sol,para);
    phi=0.;


    makeResidual(m,phi,u,rhs,Vd,Vn,b,para);b*=-1;            
    m.beginCell();
    
    contructMatrix(m,phi,G,u,F,Vd,Vn,Vphi,b,rhs,sol,error,A,para);


    FVCell2D *ptr_c;
     //Resolution of the linear systemcout<<endl;
    if(rank == 0) {
    
        cout<<"Solving the linear system"<<endl;
        A.LUFactorize();
        A.ForwardSubstitution(b) ;
        A.BackwardSubstitution(b) ;
        phi=b;


        // write on file    
        FVio result_file(para.getString("outCfile").c_str(),FVWRITE);
        result_file.put(phi,0.0,"phi");
        result_file.put(sol,0.0,"exact");
        error=phi-sol;result_file.put(error,0.0,"the_error");
        FVio result_fileV(para.getString("outVfile").c_str(),FVWRITE);
        result_fileV.put(Vphi,0.0,"phi");
        

        // we compute the errors
        double err1,errinf;
        errinf=NormMax(error);
        err1=0.;
        m.beginCell();
        while((ptr_c=m.nextCell())) {
            err1+=abs(error[ptr_c->label-1])*ptr_c->area;    
    }
    

    printf("error 1:%e      error infty:%e      \n",err1,errinf);
}
    MPI_Finalize();

    return 0;
}