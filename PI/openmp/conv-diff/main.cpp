#include "functional.h"

int main() {
// declaration
    Parameter para("param.xml");    
    FVMesh2D m(para.getString("meshfile").c_str());
    cout<<"number of cells="<<m.getNbCell()<<" and vertices="<<m.getNbVertex()<<endl;
    
    FVVect<double> phi(m.getNbCell()),G(m.getNbCell());
    FVVect<FVPoint2D<double> > u(m.getNbEdge());
    FVVect<double> F(m.getNbEdge()), Vd(m.getNbEdge()), Vn(m.getNbEdge());
    FVVect<double> Vphi(m.getNbVertex());
    FVVect<double> b(m.getNbCell()),rhs(m.getNbCell()),sol(m.getNbCell()),error(m.getNbCell());
    FVDenseM<double> A(m.getNbCell());

    // declaration done
    //
    // initialisation
    setDirichlet(m,Vd,para);
    setNeumann(m,Vn,para);
    setRHS(m,rhs,para);
    setVelocity(m,u,para);
    setExactSolution(m,sol,para);
    phi=0.;
    // initialisation done
    //
    // solving the system
      // compute b
    makeResidual(m,phi,u,rhs,Vd,Vn,b,para);b*=-1;
         // compute the matrix
    FVCell2D *ptr_c;
    m.beginCell();


    while((ptr_c = m.nextCell()))    {
        size_t i=ptr_c->label-1;
        phi[i]=1;
        printf("compute line number =%lu      \r",i+1);fflush(NULL);    
        makeResidual(m,phi,u,rhs,Vd,Vn,G,para); 
        G+=b;
        A.setColumn(i,G);
        phi[i]=0;
    }


     //Resolution of the linear systemcout<<endl;
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
    
    return 0;
}