#ifndef READMESH_MESH_H_
#define READMESH_MESH_H_

#include "element.h"
#include "surface.h"
#include "vertex.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

//! Mesh class 
//! \brief Mesh class for creating all elements 

class Mesh {
 public: 
 //! Default constructor 
 Mesh() { 
   element_list_ptr_.clear(); 
   surface_list_ptr_.clear(); 
   vertex_list_ptr_.clear(); 
 } 
 
 // Read mesh file exists 
 void read_msh_file(const std::string& filename);  

 // Read keywords from msh file  
 void readKeyword(std::ifstream *file, std::string keyword); 

 // Read elements from msh file
 void read_msh_element(const std::string& filename);
 
 // Read vertices from msh file 
 void read_msh_vertex(const std::string& filename);  

 // Set the element pointer index to element 
 void element_ptr(const unsigned index, std::shared_ptr<Element>& elementptr) {
   element_list_ptr_.at(index) = elementptr;
 }

 // Add an element pointer 
 void element_ptr(std::shared_ptr<Element>& elementptr) {
   element_list_ptr_.push_back(elementptr);
  } 

 // Return element pointer for a given index
 std::shared_ptr<Element> element_ptr(const unsigned index) const {
   return element_list_ptr_.at(index);
 }

 // Return list of element pointers 
 std::vector<std::shared_ptr<Element>> element_list_ptr() const { 
  return element_list_ptr_; 
 }   

 // Set the vertex pointer index to vertex 
 void vertex_ptr(const unsigned index, std::shared_ptr<Vertex>& vertexptr) {
   vertex_list_ptr_.at(index) = vertexptr;
 }

 // Add a vertex pointer 
 void vertex_ptr(std::shared_ptr<Vertex>& vertexptr) {
   vertex_list_ptr_.push_back(vertexptr);
 } 

 // Return vertex pointer for a given index
 std::shared_ptr<Vertex> vertex_ptr(const unsigned index) const {
   return vertex_list_ptr_.at(index);
 } 

 // Return list of element pointers 
 std::vector<std::shared_ptr<Vertex>> vertex_list_ptr() const {
  return vertex_list_ptr_;
 }  

 private: 
 std::vector<std::shared_ptr<Element>> element_list_ptr_; 
 std::vector<std::shared_ptr<Surface>> surface_list_ptr_; 
 std::vector<std::shared_ptr<Vertex>> vertex_list_ptr_;  
};

#include "mesh.tcc"

#endif //READMESH_MESH_H_
