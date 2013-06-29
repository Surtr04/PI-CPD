#include "FVStencil.h"

FVStencil::FVStencil(const FVStencil &st) // copy class
{
//cout<<"using the FVStencil copy constructor"<<endl;fflush(NULL);
_nb_geometry=st._nb_geometry;
_pos=st._pos;
_reference_geometry=st._reference_geometry;
_reference_type=st._reference_type;
_P1=st._P1;_P2=st._P2;_P3=st._P3;
_geometry=new vector<void*> ;_type=new vector<size_t>;weight=new vector<double>;
_geometry->resize(_nb_geometry);
_type->resize(_nb_geometry);
weight->resize(_nb_geometry);
for(size_t i=0;i<_nb_geometry;i++)
    {
    (*_geometry)[i]=(* st._geometry)[i];
    (*_type)[i]=(* st._type)[i];
    (*weight)[i]=(* st.weight)[i]; 
    }  
}
void FVStencil::show() 
{
cout<<"======= Stencil composition====="<<endl;    
if (_reference_geometry==NULL) _reference_type=NULL_ENTITY;  
cout<<"== Reference element =="<<endl;    
switch(_reference_type)   
   {
    case NULL_ENTITY: 
    cout<<"No reference  element"<<endl;      
    break;
    case FVVERTEX1D:
    cout<<"FVVertex1D element of label "<< ((FVVertex1D *)_reference_geometry)->label<<endl;
    break;
    case FVCELL1D:
    cout<<"FVCell1D element of label "<< ((FVCell1D *)_reference_geometry)->label<<endl;
    break;    
    case FVVERTEX2D:
    cout<<"FVVertex2D element of label "<< ((FVVertex2D *)_reference_geometry)->label<<endl;
    break;
    case FVEDGE2D:
    cout<<"FVEdge2D element of label "<< ((FVEdge2D *)_reference_geometry)->label<<endl;
    break;      
    case FVCELL2D:
    cout<<"FVCell2D element of label "<< ((FVCell2D *)_reference_geometry)->label<<endl;
    break;  
    case FVVERTEX3D:
    cout<<"FVVertex3D element of label "<< ((FVVertex3D *)_reference_geometry)->label<<endl;
    break;
    case FVEDGE3D:
    cout<<"FVEdge3D element of label "<< ((FVEdge3D *)_reference_geometry)->label<<endl;
    break;      
    case FVFACE3D:
    cout<<"FVFace3D element of label "<< ((FVFace3D *)_reference_geometry)->label<<endl;
    break;      
    case FVCELL3D:
    cout<<"FVCell3D element of label "<< ((FVCell3D *)_reference_geometry)->label<<endl;
    break;  
    default:
    cout<<" Error of element geometry type in FVStencil::show"<<endl;
    }
cout<<"== Stencil contain "<<    _nb_geometry <<" geometrical entity=="<<endl;
if(_geometry==NULL) cout<<"problem with the _geometry, memory not allocated"<<endl;fflush(NULL);
for(size_t i=0;i<_nb_geometry;i++)
    {
    cout<<"Geometrical entity "<<i<<" with weight="<<(*weight)[i]<<" ";    
    switch((*_type)[i])   
        {
        case NULL_ENTITY:
        cout<<"WARNING: NULL type reference element"<<endl;   
        break;
        case FVVERTEX1D:
        cout<<"FVVertex1D element of label "<< ((FVVertex1D *)(*_geometry)[i])->label<<endl;
        break;
        case FVCELL1D:
        cout<<"FVCell1D element of label "<< ((FVCell1D *)(*_geometry)[i])->label<<endl;
        break;    
        case FVVERTEX2D:
        cout<<"FVVertex2D element of label "<< ((FVVertex2D *)(*_geometry)[i])->label<<endl;
        break;
        case FVEDGE2D:
        cout<<"FVEdge2D element of label "<< ((FVEdge2D *)(*_geometry)[i])->label<<endl;
        break;      
        case FVCELL2D:
        cout<<"FVCell2D element of label "<< ((FVCell2D *)(*_geometry)[i])->label<<endl;
        break;  
        case FVVERTEX3D:
        cout<<"FVVertex3D element of label "<< ((FVVertex3D *)(*_geometry)[i])->label<<endl;
        break;
        case FVEDGE3D:
        cout<<"FVEdge3D element of label "<< ((FVEdge3D *)(*_geometry)[i])->label<<endl;
        break;      
        case FVFACE3D:
        cout<<"FVFace3D element of label "<< ((FVFace3D *)(*_geometry)[i])->label<<endl;
        break;      
        case FVCELL3D:
        cout<<"FVCell3D element of label "<< ((FVCell3D *)(*_geometry)[i])->label<<endl;
        break;  
        default:
        cout<<" Error of element geometry type in FVStencil::show"<<endl;
        }
    }
}

void FVStencil::setReferenceGeometry(FVVertex1D *ptr)
{
_P1=ptr->coord;
_reference_geometry=(void *) ptr;
_reference_type=FVVERTEX1D;    
}
void FVStencil::addStencil(FVVertex1D *ptr,double w )
{   
weight->push_back(w);    
_geometry->push_back((void *) ptr);
_type->push_back(FVVERTEX1D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVVertex2D *ptr )
{
_P2=ptr->coord;    
_reference_geometry=(void *) ptr;
_reference_type=FVVERTEX2D;    
}
void FVStencil::addStencil(FVVertex2D *ptr,double w ) 
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVVERTEX2D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVVertex3D *ptr )
{
_P3=ptr->coord;    
_reference_geometry=(void *) ptr;
_reference_type=FVVERTEX3D;    
}
void FVStencil::addStencil(FVVertex3D *ptr,double w )
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVVERTEX3D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVCell1D *ptr )
{
_P1=ptr->centroid;    
_reference_geometry=(void *) ptr;
_reference_type=FVCELL1D;    
}
void FVStencil::addStencil(FVCell1D *ptr,double w )
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVCELL1D);
_nb_geometry++;
}
void FVStencil::addStencil(FVCell1D *ptr,double w,size_t the_code)
{
if(ptr->code!=the_code) return;    
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVCELL1D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVCell2D *ptr )
{
_P2=ptr->centroid;      
_reference_geometry=(void *) ptr;
_reference_type=FVCELL2D;    
}
void FVStencil::addStencil(FVCell2D *ptr,double w)
{    
weight->push_back(w);    
_geometry->push_back((void *) ptr);
_type->push_back(FVCELL2D);
_nb_geometry++;
}
void FVStencil::addStencil(FVCell2D *ptr,double w,size_t the_code)
{   
if(ptr->code!=the_code) return;  
weight->push_back(w);    
_geometry->push_back((void *) ptr);
_type->push_back(FVCELL2D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVCell3D *ptr )
{
_P3=ptr->centroid;      
_reference_geometry=(void *) ptr;
_reference_type=FVCELL3D;    
}
void FVStencil::addStencil(FVCell3D *ptr,double w)
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVCELL3D);
_nb_geometry++;
}
void FVStencil::addStencil(FVCell3D *ptr,double w,size_t the_code)
{
if(ptr->code!=the_code) return;  
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVCELL3D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVEdge2D *ptr )
{
_P2=ptr->centroid;      
_reference_geometry=(void *) ptr;
_reference_type=FVEDGE2D;    
} 
void FVStencil::addStencil(FVEdge2D *ptr,double w )
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVEDGE2D);
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVEdge3D *ptr )
{
_P3=ptr->centroid;      
_reference_geometry=(void *) ptr;
_reference_type=FVEDGE3D;    
}
void FVStencil::addStencil(FVEdge3D *ptr,double w )  
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);  
_type->push_back(FVEDGE3D); 
_nb_geometry++;
}
void FVStencil::setReferenceGeometry(FVFace3D *ptr )
{
_P3=ptr->centroid;      
_reference_geometry=(void *) ptr;
_reference_type=FVFACE3D;    
}
void FVStencil::addStencil(FVFace3D *ptr,double w )  
{
weight->push_back(w);       
_geometry->push_back((void *) ptr);
_type->push_back(FVFACE3D);
_nb_geometry++;
} 
//
//
// implementation of addCell Stencil
//
//

// MESH1D
void FVStencil::addCellStencil(FVMesh1D &m,size_t nbcell)  
{

vector<FVVertex1D*> innerVertex,outerVertex;
vector<FVCell1D*> listCell;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex1D *ptr_v,*ptr_vv;
FVCell1D *ptr_c; 
size_t collectCell;
innerVertex.resize(0);outerVertex.resize(0);


// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbCell()<nbcell){cout<<"The mesh does not have enough cells"<<endl;return;}
if (_reference_type==FVCELL1D)
    {
    ptr_c=(FVCell1D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVVERTEX1D)
    {    
     ptr_v=(FVVertex1D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }      
//  at that point we have the innerVertex  and mark the cell and vertex   
listCell.resize(0);
collectCell=0;
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectCell<nbcell)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  collectCell++;   
                  listCell.push_back(ptr_c);
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listCell.size());
vector<size_t> label(listCell.size()); 
FVPoint1D<double> dd;
for(size_t i=0;i<listCell.size();i++)
    {
    ptr_c=listCell[i];  
    dd=ptr_c->centroid-_P1; 
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listCell.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_c=listCell[j-1];listCell[j-1]=listCell[j];listCell[j]=ptr_c;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbcell;i++)
    { 
    FVStencil::addStencil(listCell[i]);
    }   
}
// with code

void FVStencil::addCellStencil(FVMesh1D &m,size_t nbcell,size_t the_code)  
{

vector<FVVertex1D*> innerVertex,outerVertex;
vector<FVCell1D*> listCell;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex1D *ptr_v,*ptr_vv;
FVCell1D *ptr_c; 
size_t collectCell;
innerVertex.resize(0);outerVertex.resize(0);


// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbCell()<nbcell){cout<<"The mesh does not have enough cells"<<endl;return;}
if (_reference_type==FVCELL1D)
    {
    ptr_c=(FVCell1D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVVERTEX1D)
    {    
     ptr_v=(FVVertex1D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }      
//  at that point we have the innerVertex  and mark the cell and vertex   
listCell.resize(0);
collectCell=0;
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectCell<nbcell)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  if(ptr_c->code==the_code)
                      {
                      collectCell++;   
                      listCell.push_back(ptr_c);
                      }
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listCell.size());
vector<size_t> label(listCell.size()); 
FVPoint1D<double> dd;
for(size_t i=0;i<listCell.size();i++)
    {
    ptr_c=listCell[i];  
    dd=ptr_c->centroid-_P1; 
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listCell.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_c=listCell[j-1];listCell[j-1]=listCell[j];listCell[j]=ptr_c;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbcell;i++)
    { 
    FVStencil::addStencil(listCell[i]);
    }   
}
/*
void FVStencil::addCellStencil(FVMesh1D &m,size_t nbcell )  
{    
//  distance function
vector<double> dist(m.getNbCell());
vector<size_t> label(m.getNbCell());
FVCell1D *ptr_c;  
FVPoint1D<double> dd;
for(size_t i=0;i<m.getNbCell();i++)
    {
    ptr_c=m.getCell(i);  
    dd=ptr_c->centroid-_P1;
    dist[ptr_c->label-1]=Norm(dd); 
    label[ptr_c->label-1]=ptr_c->label;  
    }    
// Sort algorithm
size_t aux1;
double aux2;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<m.getNbCell();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux2=dist[j-1];dist[j-1]=dist[j];dist[j]=aux2; // swap dist
          aux1=label[j-1];label[j-1]=label[j];label[j]=aux1;  
          hit++;
          }
       }
    }     
if (nbcell>m.getNbCell()) nbcell=m.getNbCell();
// extract n cell
for(size_t i=1;i<=nbcell;i++)
    FVStencil::addStencil(m.getCell(label[i]-1));
} 
*/

// MESH2D 
void FVStencil::addCellStencil(FVMesh2D &m,size_t nbcell)  
{
vector<FVVertex2D*> innerVertex,outerVertex;
vector<FVCell2D*> listCell;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex2D *ptr_v,*ptr_vv;
FVCell2D *ptr_c; 
size_t collectCell;
innerVertex.resize(0);outerVertex.resize(0);
// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbCell()<nbcell){cout<<"The mesh does not have enough cells"<<endl;return;}
if (_reference_type==FVCELL2D)
    {
    ptr_c=(FVCell2D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVEDGE2D)
    {
    FVEdge2D *ptr_e=(FVEdge2D *)_reference_geometry;    
    ptr_v=ptr_e->firstVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    ptr_v=ptr_e->secondVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    }
if (_reference_type==FVVERTEX2D)
    {    
     ptr_v=(FVVertex2D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }        
//  at that point we have the innerVertex  and mark the cell and vertex   
listCell.resize(0);
collectCell=0;
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectCell<nbcell)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  collectCell++;   
                  listCell.push_back(ptr_c);
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }    
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listCell.size());
vector<size_t> label(listCell.size()); 
FVPoint2D<double> dd;
for(size_t i=0;i<listCell.size();i++)
    {
    ptr_c=listCell[i];  
    dd=ptr_c->centroid-_P2;
    dist[i]=Norm(dd);  
    }      
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listCell.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_c=listCell[j-1];listCell[j-1]=listCell[j];listCell[j]=ptr_c;  
          hit++;
          }
       }
    }    
// extract n cell
for(size_t i=0;i<nbcell;i++)
    {  
    FVStencil::addStencil(listCell[i]);
    }      
}


// with the code
void FVStencil::addCellStencil(FVMesh2D &m,size_t nbcell, size_t the_code)  
{
vector<FVVertex2D*> innerVertex,outerVertex;
vector<FVCell2D*> listCell;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex2D *ptr_v,*ptr_vv;
FVCell2D *ptr_c; 
size_t collectCell;
innerVertex.resize(0);outerVertex.resize(0);
// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbCell()<nbcell){cout<<"The mesh does not have enough cells"<<endl;return;}
if (_reference_type==FVCELL2D)
    {
    ptr_c=(FVCell2D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVEDGE2D)
    {
    FVEdge2D *ptr_e=(FVEdge2D *)_reference_geometry;    
    ptr_v=ptr_e->firstVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    ptr_v=ptr_e->secondVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    }
if (_reference_type==FVVERTEX2D)
    {    
     ptr_v=(FVVertex2D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }        
//  at that point we have the innerVertex  and mark the cell and vertex   
listCell.resize(0);
collectCell=0;
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectCell<nbcell)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  if(ptr_c->code==the_code)
                      {
                      collectCell++;   
                      listCell.push_back(ptr_c);
                      }
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }    
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listCell.size());
vector<size_t> label(listCell.size()); 
FVPoint2D<double> dd;
for(size_t i=0;i<listCell.size();i++)
    {
    ptr_c=listCell[i];  
    dd=ptr_c->centroid-_P2;
    dist[i]=Norm(dd);  
    }      
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listCell.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_c=listCell[j-1];listCell[j-1]=listCell[j];listCell[j]=ptr_c;  
          hit++;
          }
       }
    }    
// extract n cell
for(size_t i=0;i<nbcell;i++)
    {  
    FVStencil::addStencil(listCell[i]);
    }      
}
/*
void FVStencil::addCellStencil(FVMesh2D &m,size_t nbcell )  
{
//  distance function
vector<double> dist(m.getNbCell());
vector<size_t> label(m.getNbCell());
FVCell2D *ptr_c;  
FVPoint2D<double> dd;
for(size_t i=0;i<m.getNbCell();i++)
    {
    ptr_c=m.getCell(i);  
    dd=ptr_c->centroid-_P2;
    dist[ptr_c->label-1]=Norm(dd); 
    label[ptr_c->label-1]=ptr_c->label;  
    }    
// Sort algorithm
size_t aux1;
double aux2;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<m.getNbCell();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux2=dist[j-1];dist[j-1]=dist[j];dist[j]=aux2; // swap dist
          aux1=label[j-1];label[j-1]=label[j];label[j]=aux1;  
          hit++;
          }
       }
    }     
if (nbcell>m.getNbCell()) nbcell=m.getNbCell();
// extract n cell
for(size_t i=1;i<=nbcell;i++)
    { 
    FVStencil::addStencil(m.getCell(label[i]-1));
    }
} 

*/
// MESH3D
void FVStencil::addCellStencil(FVMesh3D &m,size_t nbcell)  
{
vector<FVVertex3D*> innerVertex,outerVertex;
vector<FVCell3D*> listCell;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex3D *ptr_v,*ptr_vv;
FVCell3D *ptr_c; 
size_t collectCell;
innerVertex.resize(0);outerVertex.resize(0);

// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbCell()<nbcell){cout<<"The mesh does not have enough cells"<<endl;return;}
if (_reference_type==FVCELL3D)
    {
    ptr_c=(FVCell3D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVFACE3D)
    {
    FVFace3D *ptr_f=(FVFace3D *)_reference_geometry;    
    ptr_f->beginVertex();
    while((ptr_v=ptr_f->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         } 
    }    
if (_reference_type==FVEDGE3D)
    {
    FVEdge3D *ptr_e=(FVEdge3D *)_reference_geometry;    
    ptr_v=ptr_e->firstVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    ptr_v=ptr_e->secondVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    }
if (_reference_type==FVVERTEX3D)
    {    
     ptr_v=(FVVertex3D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }      
//  at that point we have the innerVertex  and mark the cell and vertex   
listCell.resize(0);
collectCell=0;
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectCell<nbcell)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  collectCell++;   
                  listCell.push_back(ptr_c);
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listCell.size());
vector<size_t> label(listCell.size()); 
FVPoint3D<double> dd;
for(size_t i=0;i<listCell.size();i++)
    {
    ptr_c=listCell[i];  
    dd=ptr_c->centroid-_P3;
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listCell.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_c=listCell[j-1];listCell[j-1]=listCell[j];listCell[j]=ptr_c;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbcell;i++)
    { 
    FVStencil::addStencil(listCell[i]);
    }   
}


// with the code
void FVStencil::addCellStencil(FVMesh3D &m,size_t nbcell,size_t the_code)  
{
vector<FVVertex3D*> innerVertex,outerVertex;
vector<FVCell3D*> listCell;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex3D *ptr_v,*ptr_vv;
FVCell3D *ptr_c; 
size_t collectCell;
innerVertex.resize(0);outerVertex.resize(0);

// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbCell()<nbcell){cout<<"The mesh does not have enough cells"<<endl;return;}
if (_reference_type==FVCELL3D)
    {
    ptr_c=(FVCell3D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVFACE3D)
    {
    FVFace3D *ptr_f=(FVFace3D *)_reference_geometry;    
    ptr_f->beginVertex();
    while((ptr_v=ptr_f->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         markVertex.setValue(ptr_v->label,true);
         } 
    }    
if (_reference_type==FVEDGE3D)
    {
    FVEdge3D *ptr_e=(FVEdge3D *)_reference_geometry;    
    ptr_v=ptr_e->firstVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    ptr_v=ptr_e->secondVertex;
    innerVertex.push_back(ptr_v);
    markVertex.setValue(ptr_v->label,true);
    }
if (_reference_type==FVVERTEX3D)
    {    
     ptr_v=(FVVertex3D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }      
//  at that point we have the innerVertex  and mark the cell and vertex   
listCell.resize(0);
collectCell=0;
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectCell<nbcell)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  if(ptr_c->code==the_code)
                      {
                      collectCell++;   
                      listCell.push_back(ptr_c);
                      }
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listCell.size());
vector<size_t> label(listCell.size()); 
FVPoint3D<double> dd;
for(size_t i=0;i<listCell.size();i++)
    {
    ptr_c=listCell[i];  
    dd=ptr_c->centroid-_P3;
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listCell.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_c=listCell[j-1];listCell[j-1]=listCell[j];listCell[j]=ptr_c;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbcell;i++)
    { 
    FVStencil::addStencil(listCell[i]);
    }   
}

/*
void FVStencil::addCellStencil(FVMesh3D &m,size_t nbcell )  
{
//  distance function
vector<double> dist(m.getNbCell());
vector<size_t> label(m.getNbCell());
FVCell3D *ptr_c;  
FVPoint3D<double> dd;
for(size_t i=0;i<m.getNbCell();i++)
    {
    ptr_c=m.getCell(i);  
    dd=ptr_c->centroid-_P3;
    dist[ptr_c->label-1]=Norm(dd); 
    label[ptr_c->label-1]=ptr_c->label;  
    }    
// Sort algorithm
size_t aux1;
double aux2;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<m.getNbCell();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux2=dist[j-1];dist[j-1]=dist[j];dist[j]=aux2; // swap dist
          aux1=label[j-1];label[j-1]=label[j];label[j]=aux1;  
          hit++;
          }
       }
    }     
if (nbcell>m.getNbCell()) nbcell=m.getNbCell();
// extract n cell
for(size_t i=1;i<=nbcell;i++)
    FVStencil::addStencil(m.getCell(label[i]-1));
} 
*/







































//
//
// implementation of addVertex Stencil
//
//

// MESH1D
void FVStencil::addVertexStencil(FVMesh1D &m,size_t nbvertex)  
{
vector<FVVertex1D*> innerVertex,outerVertex;
vector<FVCell1D*> listCell;
vector<FVVertex1D *> listVertex;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex1D *ptr_v,*ptr_vv;
FVCell1D *ptr_c; 
size_t collectCell,collectVertex;
innerVertex.resize(0);outerVertex.resize(0);
listCell.resize(0);listVertex.resize(0);
collectCell=0;collectVertex=0;
// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbVertex()<nbvertex){cout<<"The mesh does not have enough vertices"<<endl;return;}
if (_reference_type==FVCELL1D)
    {
    ptr_c=(FVCell1D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         listVertex.push_back(ptr_v);
         collectVertex++;
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVVERTEX1D)
    {    
     ptr_v=(FVVertex1D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }   
    
//  at that point we have the innerVertex  and mark the cell and vertex   
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectVertex<nbvertex)
    {
        
    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  collectCell++;   
                  listCell.push_back(ptr_c);
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           listVertex.push_back(ptr_vv);
                           collectVertex++;
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//for(size_t i=0;i<listVertex.size();i++) {cout<<"label:"<<listVertex[i]->label<<endl;}
//  distance function
vector<double> dist(listVertex.size());
vector<size_t> label(listVertex.size()); 
FVPoint1D<double> dd;
for(size_t i=0;i<listVertex.size();i++)
    {
    ptr_v=listVertex[i];  
    dd=ptr_v->coord-_P1;
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listVertex.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_v=listVertex[j-1];listVertex[j-1]=listVertex[j];listVertex[j]=ptr_v;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbvertex;i++)
    { 
    FVStencil::addStencil(listVertex[i]);
    }   
}


// MESH2D 
void FVStencil::addVertexStencil(FVMesh2D &m,size_t nbvertex)  
{
vector<FVVertex2D*> innerVertex,outerVertex;
vector<FVCell2D*> listCell;
vector<FVVertex2D *> listVertex;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex2D *ptr_v,*ptr_vv;
FVCell2D *ptr_c; 
size_t collectCell,collectVertex;
innerVertex.resize(0);outerVertex.resize(0);
listCell.resize(0);listVertex.resize(0);
collectCell=0;collectVertex=0;
// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbVertex()<nbvertex){cout<<"The mesh does not have enough vertices"<<endl;return;}
if (_reference_type==FVCELL2D)
    {
    ptr_c=(FVCell2D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         listVertex.push_back(ptr_v);
         collectVertex++;
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVEDGE2D)
    {
    FVEdge2D *ptr_e=(FVEdge2D *)_reference_geometry;    
    ptr_v=ptr_e->firstVertex;
    innerVertex.push_back(ptr_v);
    listVertex.push_back(ptr_v);
    collectVertex++;
    markVertex.setValue(ptr_v->label,true);
    ptr_v=ptr_e->secondVertex;
    innerVertex.push_back(ptr_v);
    listVertex.push_back(ptr_v);
    collectVertex++;
    markVertex.setValue(ptr_v->label,true);
    }
if (_reference_type==FVVERTEX2D)
    {    
     ptr_v=(FVVertex2D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }      
//  at that point we have the innerVertex  and mark the cell and vertex   
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectVertex<nbvertex)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  collectCell++;   
                  listCell.push_back(ptr_c);
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           listVertex.push_back(ptr_vv);
                           collectVertex++;
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listVertex.size());
vector<size_t> label(listVertex.size()); 
FVPoint2D<double> dd;
for(size_t i=0;i<listVertex.size();i++)
    {
    ptr_v=listVertex[i];  
    dd=ptr_v->coord-_P2;
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listVertex.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_v=listVertex[j-1];listVertex[j-1]=listVertex[j];listVertex[j]=ptr_v;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbvertex;i++)
    { 
    FVStencil::addStencil(listVertex[i]);
    }   
}



// MESH3D
void FVStencil::addVertexStencil(FVMesh3D &m,size_t nbvertex)  
{
vector<FVVertex3D*> innerVertex,outerVertex;
vector<FVCell3D*> listCell;
vector<FVVertex3D *> listVertex;
FVSparseV<bool> markVertex,markCell;
//FVVect<bool> markVertex(m.getNbVertex()+1),markCell(m.getNbCell()+1);
FVVertex3D *ptr_v,*ptr_vv;
FVCell3D *ptr_c; 
size_t collectCell,collectVertex;
innerVertex.resize(0);outerVertex.resize(0);
listCell.resize(0);listVertex.resize(0);
collectCell=0;collectVertex=0;
// make the initial innerVertex 
if (!_reference_geometry){cout<<"No reference geometry, can not make stencil"<<endl; return;}
if (m.getNbVertex()<nbvertex){cout<<"The mesh does not have enough vertices"<<endl;return;}    
if (_reference_type==FVCELL3D)
    {
    ptr_c=(FVCell3D *)_reference_geometry;
    ptr_c->beginVertex();
    while((ptr_v=ptr_c->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         listVertex.push_back(ptr_v);
         collectVertex++;
         markVertex.setValue(ptr_v->label,true);
         }    
    markCell.setValue(ptr_c->label,true);
    }
if (_reference_type==FVFACE3D)
    {
    FVFace3D *ptr_f=(FVFace3D *)_reference_geometry;    
    ptr_f->beginVertex();
    while((ptr_v=ptr_f->nextVertex())) 
         {
         innerVertex.push_back(ptr_v);
         listVertex.push_back(ptr_v);
         collectVertex++;    
         markVertex.setValue(ptr_v->label,true);
         } 
    }    
if (_reference_type==FVEDGE3D)
    {
    FVEdge3D *ptr_e=(FVEdge3D *)_reference_geometry;    
    ptr_v=ptr_e->firstVertex;
    innerVertex.push_back(ptr_v);
    listVertex.push_back(ptr_v);
    collectVertex++;
    markVertex.setValue(ptr_v->label,true);
    ptr_v=ptr_e->secondVertex;
    innerVertex.push_back(ptr_v);
    listVertex.push_back(ptr_v);
    collectVertex++;
    markVertex.setValue(ptr_v->label,true);
    }
if (_reference_type==FVVERTEX3D)
    {    
     ptr_v=(FVVertex3D *)_reference_geometry;    
     innerVertex.push_back(ptr_v);  
     markVertex.setValue(ptr_v->label,true);
    }      
//  at that point we have the innerVertex  and mark the cell and vertex   
//  start to collect the cell coroa by coroa till we have enough cell 
while(collectVertex<nbvertex)
    {

    for(size_t i=0;i<innerVertex.size();i++) // loop on the inner  vertex
         {
         ptr_v=innerVertex[i];    
         ptr_v->beginCell();
         while((ptr_c=ptr_v->nextCell()))
             {
             if(!markCell.getValue(ptr_c->label))
                 {
                  collectCell++;   
                  listCell.push_back(ptr_c);
                  markCell.setValue(ptr_c->label,true); //mark the cell
                  ptr_c->beginVertex();
                  while((ptr_vv=ptr_c->nextVertex()))// maintenant il faut construre laliste des vertex outer
                       {
                       if(!markVertex.getValue(ptr_vv->label))   
                           {
                           outerVertex.push_back(ptr_vv);
                           listVertex.push_back(ptr_vv);
                           collectVertex++;
                           markVertex.setValue(ptr_vv->label,true);
                           }
                       }
                 }
             }
         }    
    // at that point a coroa has been done
    innerVertex=outerVertex; // we initialize the next coroa
    outerVertex.resize(0);
    }
// at that point listCell contains enough cells  
//  distance function
vector<double> dist(listVertex.size());
vector<size_t> label(listVertex.size()); 
FVPoint3D<double> dd;
for(size_t i=0;i<listVertex.size();i++)
    {
    ptr_v=listVertex[i];  
    dd=ptr_v->coord-_P3;
    dist[i]=Norm(dd);  
    }    
// Sort algorithm
double aux;
size_t hit=1;
while(hit)
   {
   hit=0;  
   for(size_t j=1; j<listVertex.size();j++)
      {
      if(dist[j-1]>dist[j])
          {
          aux=dist[j-1];dist[j-1]=dist[j];dist[j]=aux; // swap dist
          ptr_v=listVertex[j-1];listVertex[j-1]=listVertex[j];listVertex[j]=ptr_v;  
          hit++;
          }
       }
    }     
// extract n cell
for(size_t i=0;i<nbvertex;i++)
    { 
    FVStencil::addStencil(listVertex[i]);
    }   
}



//
// check if a geometrical entity belongs to the stencil
//

bool FVStencil::inStencil(FVVertex1D *ptr )  
{   
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVVERTEX1D) continue;   
    if(    ((FVVertex1D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVVertex2D *ptr ) 
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVVERTEX2D) continue;   
    if(    ((FVVertex2D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVVertex3D *ptr )   
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVVERTEX3D) continue;   
    if(    ((FVVertex3D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVCell1D *ptr )     
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVCELL1D) continue;   
    if(    ((FVCell1D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVCell2D *ptr )     
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVCELL2D) continue;   
    if(    ((FVCell2D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVCell3D *ptr )
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVCELL3D) continue;   
    if(    ((FVCell3D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVEdge2D *ptr )     
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVEDGE2D) continue;   
    if(    ((FVEdge2D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVEdge3D *ptr )    
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVEDGE3D) continue;   
    if(    ((FVEdge3D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
bool FVStencil::inStencil(FVFace3D *ptr )    
{
for(size_t i=0;i<_nb_geometry;i++)
    {
    if((*_type)[i] != FVFACE3D) continue;   
    if(    ((FVFace3D *)(*_geometry)[i])->label  ==  ptr->label) {return(true);}
    }
return(false);
}
