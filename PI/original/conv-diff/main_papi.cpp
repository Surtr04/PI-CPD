#include "functional.h"
#include "papi_errors.h"



void handle_error(int err_no) {
    fprintf(stderr,"\nError: %d - %s\n",err_no,p_errors[err_no].err_code);  
    exit(-1);
}

#define NUM_EVENTS 11

int current_event;        

int papi_events[NUM_EVENTS] = {
    PAPI_TOT_CYC,   /* Total number of cycles           */
    PAPI_TOT_INS,   /* Instructions completed           */
    PAPI_LD_INS,    /* number of load instructions      */
    PAPI_SR_INS,    /* number of store instructions     */  

    PAPI_FP_OPS,    /* Floating point operations        */
    PAPI_FP_INS,    /* Floating point instructions      */  

    PAPI_L1_DCA,    /* L1 data cache accesses           */
    PAPI_L1_DCM,    /* L1 data cache misses             */
    PAPI_L2_DCA,    /* L2 data cache accesses           */
    PAPI_L2_DCM,    /* L2 data cache misses             */
    PAPI_L3_DCA,    /* L3 data cache accesses           */
};


//code stub
/*



int main (int argc, char** argv) {
    //matrix size - w/ op? - event_index
    if(argc < 4){
        fprintf(stderr,"wrong number of arguments");
        exit(1);
    }

    size = atoi(argv[1]);
    op = atoi(argv[2]);
    current_event = atoi(argv[3]);

    m = (matrices*) (malloc(sizeof(matrices)));

    if (!op) {
        
        m->matrixA = initRandMatrix();
        m->matrixB = initUnitMatrix();
        m->matrixC = initMatrix();          
    }
    else {
        m->matrixA = initRandMatrix();
        m->matrixB = transposeMatrix(initUnitMatrix());
        m->matrixC = initMatrix();
    }


    run_papi();

    free(m);

    return 0;

}
*/





int main() {
// declaration
    Parameter para("param.xml");    
    FVMesh2D m(para.getString("meshfile").c_str());
    cout<<"number of cells="<<m.getNbCell()<<" and vertices="<<m.getNbVertex()<<endl;
    FVVect<double> phi(m.getNbCell()),G(m.getNbCell());
    FVVect<FVPoint2D<double> > u(m.getNbEdge());
    FVVect<double> F(m.getNbEdge()),Vd(m.getNbEdge()),Vn(m.getNbEdge());
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


    while((ptr_c=m.nextCell()))    {
        size_t i=ptr_c->label-1;
        phi[i]=1;
        printf("compute line number =%lu      \r",i+1);fflush(NULL);
        makeResidual(m,phi,u,rhs,Vd,Vn,G,para); 
        G+=b;
        A.setColumn(i,G);
        phi[i]=0;
    }


    // Resolution of the linear systemcout<<endl;
    cout<<"Solving the linear system"<<endl;

    //papi

    current_event = atoi(argv[1]);

    int papi_version = PAPI_library_init(PAPI_VER_CURRENT);
    unsigned long long int start_time, end_time;


    check(papi_version != PAPI_VER_CURRENT && papi_version > 0, ERR_PAPI_INIT);
    check(papi_version < 0, ERR_PAPI_INIT2);

    event_set = PAPI_NULL;
    papi_safe(PAPI_create_eventset(&event_set), ERR_PAPI_EVENT_SET);

    PAPI_event_info_t inf;
    papi_safe(PAPI_get_event_info(papi_events[current_event], &inf),ERR_PAPI_GET_EVENT_INFO);

    papi_safe(PAPI_add_event(event_set, papi_events[current_event]), ERR_PAPI_ADD_EVENT);
    start_time = PAPI_get_virt_usec();

    A.LUFactorize();

    //papi_end
    end_time = PAPI_get_virt_usec();
    fprintf(stdout, "%s\t", inf.symbol);
    fprintf(stdout, "\t%llu\t", event_value[0]);    
    fprintf(stdout, "\t%llu\n", end_time - start_time);
    papi_safe(PAPI_remove_event(event_set, papi_events[current_event]), ERR_PAPI_REMOVE_EVENT);

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