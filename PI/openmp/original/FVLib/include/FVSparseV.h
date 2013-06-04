// ------ FVSparseV.h ------
// S. CLAIN 2012/03
#ifndef _FVSparseV
#define _FVSparseV

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <FVVect.h>
#define NO_INDEX ((size_t) -1)

class SparseNode
{
public:
    size_t index;  // the indice i or j of the row or column vector
    size_t pos;    // the position in the global data vector
    SparseNode(){index=0;pos=0;}
    ~SparseNode(){;}
    SparseNode(const SparseNode &sn){index=sn.index;pos=sn.pos;};

};
typedef std::vector<SparseNode> Tab_index;



// 
// 
// 
 
template<class T_> class FVSparseV 
{
private:
std::vector<SparseNode> _node; // index table  
std::vector<T_> _data; 
public: 
size_t length; // length of the vector


    FVSparseV();
    ~FVSparseV();
    FVSparseV(size_t );
    FVSparseV(const FVSparseV<T_> &);
    size_t size(){ return _data.size();} 
    void setValue(size_t i, const T_ &val);
    T_ getValue(size_t i)  ;
    size_t getLength(){return(length);}
    void addValue(size_t i, const T_ &val);   
    void multValue(size_t i, const T_ &val);     
    void clean(){    length=0;_node.resize(0);_data.resize(0);}
    void show();
    FVSparseV<T_> & operator=(const T_ &x);
    FVSparseV<T_> & operator/=(const T_ &val);
    FVSparseV<T_> & operator*=(const T_ &val);
    FVSparseV<T_> & operator+=(const T_ &val);
    FVSparseV<T_> & operator-=(const T_ &val);
    FVSparseV<T_> & operator+=(const FVSparseV<T_> &m);
    FVSparseV<T_> & operator-=(const FVSparseV<T_> &m);    
    size_t  exist(Tab_index  &tab,size_t loc)
           {
           for(size_t i=0;i<tab.size();i++)
               { 
                if (tab[i].index==loc) return(i);   
               }
           return NO_INDEX;    
           }
};
template<class T_> FVSparseV<T_>::FVSparseV()
    {  
    length=0;
    _node.resize(0);
    _data.resize(0);
    }
template<class T_> FVSparseV<T_>::~FVSparseV()
    { 
    ;    
    }
template<class T_>
FVSparseV<T_>::FVSparseV(const FVSparseV<T_> &v) 
{
   length=v.length;
   _node.resize(v._node.size()); 
   _data.resize(v._data.size());    
   for(size_t i=0;i<_node.size();i++)
       {
       _node[i]=v._node[i];   
       _data[i]=v._data[i];      
       }
}    
  


template<class T_> 
void FVSparseV<T_>::setValue(size_t i, const T_ &val)
{
size_t ii;    
ii=exist(_node,i); 
if(ii!=NO_INDEX) 
    _data[_node[ii].pos]=val; //if exist set the value
else
    {        // if not creat the value
    SparseNode no;
    no.index=i;no.pos=_data.size(); // now the component is mark and we link with the data vector
    _node.push_back(no); // memorize node
    _data.push_back(val); // memorize data
    if (i+1>length) length=i+1; // set the vector "virtual" dimension
    }
   
}

template<class T_> 
T_ FVSparseV<T_>::getValue(size_t i)
{    
size_t ii;    
ii=exist(_node,i); 
if(ii!=NO_INDEX)  return(_data[_node[ii].pos]);
return(static_cast<T_>(0));
}

template<class T_> 
void FVSparseV<T_>::addValue(size_t i, const T_ &val)
{
    FVSparseV<T_>::setValue(i,FVSparseV<T_>::getValue(i)+val);
}

template<class T_> 
void FVSparseV<T_>::multValue(size_t i, const T_ &val)
{
    FVSparseV<T_>::setValue(i,FVSparseV<T_>::getValue(i)*val);
}


/*--------- MSparse Vector operations ----------*/

template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
 for(size_t i=0;i<_data.size();i++)
       {
       _data[i]=val;    
       }
   return *this;
}

template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator/=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
 for(size_t i=0;i<_data.size();i++)
       {
       _data[i]/=val;    
       }
   return *this;
}

template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator*=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
 for(size_t i=0;i<_data.size();i++)
       {
       _data[i]*=val;    
       }
   return *this;
}
template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator+=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
 for(size_t i=0;i<_data.size();i++)
       {
       _data[i]+=val;    
       }
   return *this;
}
template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator-=(const T_ &val)
{
 // #pragma omp parallel for num_threads(nb_thread)
 for(size_t i=0;i<_data.size();i++)
       {
       _data[i]-=val;    
       }
   return *this;
}


template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator+=(const FVSparseV<T_> &v)
{
//  #pragma omp parallel for num_threads(nb_thread)
size_t ii;
T_ val;
   if(length<v.length)  length=v.length;
   for (size_t i=0; i<v._node.size(); i++)
       {
        ii= v._node[i].index;
        val=v._data[v._node[i].pos];
        FVSparseV<T_>::setValue(ii,FVSparseV<T_>::getValue(ii)+val);
       }
   return *this;
}

template<class T_>
FVSparseV<T_> & FVSparseV<T_>::operator-=(const FVSparseV<T_> &v)
{
//  #pragma omp parallel for num_threads(nb_thread)
size_t ii;
T_ val;
   if(length<v.length)  length=v.length;
   for (size_t i=0; i<v._node.size(); i++)
       {
        ii= v._node[i].index;
        val=v._data[v._node[i].pos];
        FVSparseV<T_>::setValue(ii,FVSparseV<T_>::getValue(ii)-val);
       }
   return *this;
}


template<class T_>    
void FVSparseV<T_>::show()
{
    
cout<<"==== Sparse Vector ======LENGTH==="<<length<<endl;    
for(size_t i=0;i<length;i++)
          
        cout<<FVSparseV<T_>::getValue(i)<<" ";
    cout<<endl;
cout<<"==========================="<<endl;
}
#endif // define _FVSparseV

