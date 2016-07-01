#ifndef READMESH_ELEMENTS_H_
#define READMESH_ELEMENTS_H_

#include "surfaces.h"
#include "vertex.h"

#include <memory>
#include <vector>

// Element class
// \brief Element for associating elements with surfaces and vertices   

class Elements {
public: 
 // Default constructor (temperory) for debugging only 
 Elements(){}

 // Constructor with element id 
 explicit Elements(const unsigned elementid) : elementid_{elementid} {
   surface_list_ptr_.clear(); 
   vertex_list_ptr_.clear();
 }
 
 // Return id of the element 
 unsigned elementid() const {return elementid_;}

 // set the surface pointer to surface 
 void surface_ptr (const unsigned index, std::shared_ptr<Surfaces> surf); 

 // set the vertex pointer to vertex 
 void vertex_ptr (const unsigned index, std::shared_ptr<Vertex> vert); 

 // Return sufrace pointer for a given index 
 std::shared_ptr<Surfaces> surface_ptr(const unsigned index) const; 

 // Return vertex pointer for a given index 
 std::shared_ptr<Vertex> vertex_ptr(const unsigned index) const; 

 // Return list of surface pointers 
 std::vector<std::shared_ptr<Surfaces>> surface_list_ptr()
   const{
     return surface_list_ptr_; 
   } 

 // Return list of vertex pointers 
 std::vector<std::shared_ptr<Vertex>> vertex_list_ptr()
   const{
     return vertex_list_ptr_; 
   } 

private:  
 unsigned elementid_; 
 std::vector<std::shared_ptr<Surfaces>> surface_list_ptr_; 
 std::vector<std::shared_ptr<Vertex>> vertex_list_ptr_; 

};

#endif // READMESH_ELEMENTS_H_


