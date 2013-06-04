// ------ FVSparseMatrice.h ------
// S. CLAIN 2011/07
#ifndef _FVSparseM
#define _FVSparseM
#include <FVSparseV.h>


template<class T_> class FVSparseM 
{
private:
std::vector<Tab_index *> _row,_col; // index table
std::vector<T_>  _a;  // the place for the matrice  
size_t nb_cols,nb_rows,length; // number of rows and columns  , length of the matrix 
public: 

    FVSparseM();
    ~FVSparseM();
    //FVSparseM(size_t );
    //FVSparseM(size_t , size_t );
    FVSparseM(const FVSparseM<T_> &m);
    size_t getNbColumns() {return(nb_cols);}
    size_t getNbRows(){ return(nb_rows);}
    size_t getLength(){ return(length);}     
    void setValue(size_t i, size_t j, const T_ &val);
    T_ getValue(size_t i, size_t j)  ;    
    void addValue(size_t i, size_t j, const T_ &val);      
    void multValue(size_t i, size_t j, const T_ &val);        
    void clean();    
    void show();
    FVSparseM<T_> & operator=(const T_ &x);
    FVSparseM<T_> & operator/=(const T_ &val);
    FVSparseM<T_> & operator*=(const T_ &val);
    FVSparseM<T_> & operator+=(const T_ &val);
    FVSparseM<T_> & operator-=(const T_ &val);
    //FVSparseM<T_> & operator+=(const FVSparseM<T_> &m);
    //FVSparseM<T_> & operator-=(const FVSparseM<T_> &m);    
    //void horizontalMerge(FVSparseM<T_> &m, const FVSparseM<T_> &m,);
    //void verticalMerge(FVSparseM<T_> &m, const FVSparseM<T_> &m,);    
    //FVVect<T_> getColumn(size_t j) const;
    //FVVect<T_> getRow(size_t i) const
    void Mult(const FVVect<T_> &, FVVect<T_> &) const;
    void TransMult(const FVVect<T_> &, FVVect<T_> &) const  ; 
    size_t doGradConj(FVVect<T_> &x,FVVect<T_> &b,double epsi,size_t MaxIter);
    //void Mult(const FVSparseV<T_> &, FVSparseV<T_> &) const;
    //void TransMult(const FVSparseV<T_> &, FVSparseV<T_> &) const  ;     
    size_t  exist(Tab_index  &tab,size_t loc)
           {
           for(size_t i=0;i<tab.size();i++)
               { 
                if (tab[i].index==loc) return(i);   
               }
           return NO_INDEX;    
           }
 
};


//construct an empty matrix
template<class T_> FVSparseM<T_>::FVSparseM()
{
nb_rows = nb_cols = 0,length=0;
_row.resize(0);_col.resize(0);
}
    // destructor: free the memory
template<class T_> FVSparseM<T_>::~FVSparseM()
{
nb_rows = nb_cols = 0,length=0;
for(size_t i=0;i<_row.size();i++)
        if((_row[i])) delete _row[i];
for(size_t j=0;j<_col.size();j++)
        if((_col[j])) delete _col[j];
}    

// copy sparse matrix    
template<class T_>
FVSparseM<T_>::FVSparseM(const FVSparseM<T_> &m) 
{
nb_cols=m.nb_rows;
nb_rows=m.nb_cols;
length=m.length;
for(size_t i=0;i<_row.size();i++)
        if((m._row[i])) {_row[i]=new Tab_index; *_row[i]=*m._row[i];}
for(size_t j=0;j<_col.size();j++)
        if((m._col[j])) {_col[j]=new Tab_index; *_col[j]=*m._col[j];}
_a = m._a;  
}

//   set value
template<class T_>
void FVSparseM<T_>::setValue(size_t i, size_t j, const T_ &val) 
    {
    size_t jj;    
    cout<<"set value in row "<<i<<" and col "<<j<<endl;fflush(NULL);  
    if (i>=nb_rows)  // add more row and initialise it
       {
       cout<<"create new row "<< i<<endl; fflush(NULL);     
        _row.resize(i+1);
        for(size_t k=nb_rows;k<=i;k++)
           // _row[k]=NULL;
        _row[i]=new Tab_index;  
        nb_rows=i+1;   
       }      
    if (j>=nb_cols)
       {
       cout<<"create new col "<< j<<endl; fflush(NULL);                
        _col.resize(j+1);
        for(size_t k=nb_cols;k<=j;k++)
           // _col[k]=NULL;
        _col[j]=new Tab_index;  
        nb_cols=j+1;   
       }       
    jj=exist(*_row[i],j);
    if(jj!=NO_INDEX)
        {
        cout<<"the node exist in row "<<i<<" and col "<<j<<endl;fflush(NULL); 
         _a[(*(_row[i]))[jj].pos]=val; // the node still exist
        }
    else  // we have to create the node for the two index set
        {    
        SparseNode noRow,noCol;
        _a.push_back(val);    
        length=_a.size();
        noRow.index=j;noRow.pos=length-1;
        noCol.index=i;noCol.pos=length-1;    
        cout<<"assing in row "<<i<<endl;fflush(NULL);   
        _row[i]->push_back(noRow); 
        cout<<"assing in col "<<j<<endl;fflush(NULL);   
        _col[j]->push_back(noCol);  
        } 
    }
//   get value    
template<class T_>    
T_ FVSparseM<T_>::getValue(size_t i, size_t j)  
{
    size_t jj;    
    //cout<<"i="<<i<<" j="<<j<<endl; fflush(stdout);
    if ((i> nb_rows) || (j> nb_cols)) return static_cast<T_>(0);  //outside of the matrix
    if (_row[i]==NULL) return static_cast<T_>(0);  
    jj=exist(*_row[i],j);
    if(jj==NO_INDEX) return static_cast<T_>(0);
    else
        return(_a[(*(_row[i]))[jj].pos]);
     
}    
    
    
 //   add value
template<class T_>
void FVSparseM<T_>::addValue(size_t i, size_t j, const T_ &val)
    {
    FVSparseM<T_>::setValue(i,j,FVSparseM<T_>::getValue(i,j)+val);
    }
 //   mult value
template<class T_>
void FVSparseM<T_>::multValue(size_t i, size_t j, const T_ &val)
    {
    FVSparseM<T_>::setValue(i,j,FVSparseM<T_>::getValue(i,j)*val);
    }

 template<class T_>    
void FVSparseM<T_>::show()
{
    
cout<<"==== MATRIX ===="<<nb_rows<<"X"<<nb_cols<<"===LENGTH==="<<length<<endl;    
for(size_t i=0;i<nb_rows;i++)
    {

    for(size_t j=0;j<nb_cols;j++)
        cout<<FVSparseM<T_>::getValue(i,j)<<" ";
    cout<<endl;
    }   
cout<<"==========================="<<endl;
cout<<"TAB_VALUE"<<endl;
for(size_t i=0;i<_a.size();i++) cout<<_a[i]<<" ";
cout<<endl;
}

 template<class T_>    
void FVSparseM<T_>::clean()
{
nb_rows = nb_cols = 0,length=0;
for(size_t i=0;i<_row.size();i++)
        if((_row[i])) delete _row[i];
for(size_t j=0;j<_col.size();j++)
        if((_col[j])) delete _col[j];  
_row.resize(1);_col.resize(1); 
_row[0]=NULL;_col[0]=NULL;        
}
//  Operators

template<class T_>
FVSparseM<T_> & FVSparseM<T_>::operator/=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
   for (size_t i=0; i<length; i++)
      _a[i] /= val;
   return *this;
}

template<class T_>
FVSparseM<T_> & FVSparseM<T_>::operator*=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
   for (size_t i=0; i<length; i++)
      _a[i] *= val;
   return *this;
}
template<class T_>
FVSparseM<T_> & FVSparseM<T_>::operator-=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
   for (size_t i=0; i<length; i++)
      _a[i] -= val;
   return *this;
}

template<class T_>
FVSparseM<T_> & FVSparseM<T_>::operator+=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
   for (size_t i=0; i<length; i++)
      _a[i] += val;
   return *this;
}

template<class T_>
FVSparseM<T_> & FVSparseM<T_>::operator=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
   for (size_t i=0; i<length; i++)
      _a[i] = val;
   return *this;
}


 
 
 
 
 /*--------- Matrix Vector operations ----------*/
 
// compute y=A*x
template<class T_>
void FVSparseM<T_>::Mult(const FVVect<T_> &x, FVVect<T_> &y) const
    {
#ifdef _DEBUGS
    size_t err=(x.size()<nb_cols)+2*(y.size()<nb_rows);
    if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif  
    y = static_cast<T_>(0);
//#pragma omp parallel for num_threads(nb_thread)
    for (size_t i=0; i<nb_rows; i++)
        {
        if(!_row[i]) continue; // no line i so y[i)=0     
        for (size_t jj=0; jj<(_row[i])->size(); jj++)
            {
             //cout<<"i="<<i<<" j="<<  (*(row[i]))[jj].index<<" val="<< a[(*(row[i]))[jj].pos]<<endl;
             y[i] += _a[(*(_row[i]))[jj].pos] * x[(*(_row[i]))[jj].index];
            }
        }
    }
// compute y=A^T*x
template<class T_>
void FVSparseM<T_>::TransMult(const FVVect<T_> &x, FVVect<T_> &y) const
    {
#ifdef _DEBUGS
    size_t err=(x.size()<nb_rows)+2*(y.size()<nb_cols);
    if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif         
    y = static_cast<T_>(0);
//#pragma omp parallel for num_threads(nb_thread)    
    for (size_t j=0; j<nb_cols; j++)
        {
        if(!_col[j]) continue; // no column j, y[i]=0     
        for (size_t ii=0; ii<_col[j]->size(); ii++)
            y[j] += _a[(*(_col[j]))[ii].pos] * x[(*(_col[j]))[ii].index];
        }
    } 
 /*--------- Matrix Matrix operations ----------*/ 
template<class T_>
size_t FVSparseM<T_>::doGradConj(FVVect<T_> &x,FVVect<T_> &b,double epsi,size_t MaxIter)
{
#ifdef _DEBUGS
size_t err=(x.size()<nb_cols)+2*(b.size()<nb_cols);
if(err) cout<<" in file "<<__FILE__<<", line "<<__LINE__<<"index out of range, error code="<<err<<endl;
#endif  
size_t iter=0;
FVVect<T_> p(nb_cols),r(nb_cols),z(nb_cols);
Mult(x,r);r-=b;r*=-1;p=r; 
double erro=Norm(r),d,nu,mu;
while((erro>epsi)&&(iter<MaxIter))
    {
    iter++;   
    Mult(p,z);
    d=Dot(r,r);nu=d/Dot(r,z);
    x+=nu*p;r-=nu*z;erro=NormMax(r);
    mu=Dot(r,r)/d;
    p*=mu;p+=r;
    }
return(iter);
}
#endif // define _FVSparseM

 
 