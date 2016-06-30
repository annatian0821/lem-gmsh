#ifndef READMESH_ELEMENTS_H_
#define READMESH_ELEMENTS_H_

#include "surfaces.h"
#include "vertex.h"

#include <memory>
#include <vector>

// Element class
// \brief Element for associating elements with surfaces and vertices   

using SurfacePtr = std::shared_ptr<Surfaces>; 
using VertexPtr = std::shared_ptr<Vertex>;

class Elements {
public: 
 // Default constructor (temperory) for debugging only 
 Elements(){}

 // Constructor with element id 
 explicit Elements(const unsigned elementid) : elementid_{elementid} {
   surface_list_.clear();
   vertex_list_.clear();
   surface_list_ptr_.clear(); 
   vertex_list_ptr_.clear();
 }
 
 // Assign list of surfaces to the element 
 void surface_list(const std::vector<unsigned>& surface_list) {surface_list_ = surface_list;}

 // Assign list of vertices to the element 
 void vertex_list(const std::vector<unsigned>& vertex_list) {vertex_list_ = vertex_list;}

 // Return id of the element 
 unsigned elementid() const {return elementid_;}

 // Return list of surfaces for a given element
 std::vector<unsigned> surface_list(const unsigned elementid) const {return surface_list_; }

 // Return list of vertices for a given element
 std::vector<unsigned> vertex_list(const unsigned elementid) const {return vertex_list_; }

 // set the surface pointer to surface 
 void surface_ptr (const unsigned index, SurfacePtr surf); 

 // set the vertex pointer to vertex 
 void vertex_ptr (const unsigned index, VertexPtr vert); 

 // Return sufrace pointer for a given index 
 SurfacePtr surface_ptr(const unsigned index) const; 

 // Return vertex pointer for a given index 
 VertexPtr vertex_ptr(const unsigned index) const; 

 // Return list of surface pointers 
 std::vector<SurfacePtr> surface_list_ptr()
   const{
     return surface_list_ptr_; 
   } 

 // Return list of vertex pointers 
 std::vector<VertexPtr> vertex_list_ptr()
   const{
     return vertex_list_ptr_; 
   } 

private:  
 unsigned elementid_; 
 std::vector<unsigned> surface_list_; 
 std::vector<unsigned> vertex_list_; 
 std::vector<SurfacePtr> surface_list_ptr_; 
 std::vector<VertexPtr> vertex_list_ptr_; 

};

#endif // READMESH_ELEMENTS_H_


