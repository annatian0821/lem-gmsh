#ifndef READMESH_MESH_H_
#define READMESH_MESH_H_

#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

#include "element.h"
#include "settings.h"
#include "surface.h"
#include "vertex.h"

//! Mesh class
//! \brief Mesh class for creating all elements

class Mesh {
 public:
  //! Default constructor
  Mesh() {
    element_list_ptr_.clear();
    surface_list_ptr_.clear();
    vec_vertex_ptr_.clear();
  }

  // Read mesh file exists
  void read_msh_file(const std::string& filename);

  // Read keywords from msh file
  void read_keyword(std::ifstream& file, std::string keyword);

  // Read elements from msh file
  void read_elements(std::ifstream& file);

  // Read vertices from msh file
  void read_vertices(std::ifstream& file);

  // Read surfaces from msh file
  void read_surfaces(std::ifstream& file);

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

  // Set the surface pointer index to surface
  void surface_ptr(const unsigned index, std::shared_ptr<Surface>& surfaceptr) {
    surface_list_ptr_.at(index) = surfaceptr;
  }

  // Add a surface pointer
  void surface_ptr(std::shared_ptr<Surface>& surfaceptr) {
    surface_list_ptr_.push_back(surfaceptr);
  }

  // Return surface pointer for a given index
  std::shared_ptr<Surface> surface_ptr(const unsigned index) const {
    return surface_list_ptr_.at(index);
  }

  // Return list of surface pointers
  std::vector<std::shared_ptr<Surface>> surface_list_ptr() const {
    return surface_list_ptr_;
  }

  // Add a vertex pointer
  void vertex_ptr(std::shared_ptr<Vertex>& vertexptr) {
    vec_vertex_ptr_.push_back(vertexptr);
  }

  // Return vertex pointer for a given index
  std::shared_ptr<Vertex> vertex_ptr(const unsigned index) const {
    return vec_vertex_ptr_.at(index);
  }

  // Return vertex pointer for a given vertex id
  std::shared_ptr<Vertex> vertex_ptr_at_id(const unsigned id) const {
    std::shared_ptr<Vertex> ver_ptr = nullptr;
    for (auto vertex_ptr : vec_vertex_ptr_) {
      if (vertex_ptr->id() == id) ver_ptr = vertex_ptr;
    }
    return ver_ptr;
  }

  // Return list of vertex pointers
  std::vector<std::shared_ptr<Vertex>> vec_vertex_ptr() const {
    return vec_vertex_ptr_;
  }

  // Return list of element ids for a given fracture surface id
  void get_element_ids_per_sid(std::ifstream& file, const unsigned sid);
 
  // Frac pairs
  void frac_pairs(const unsigned element_id, const std::vector<unsigned> vlist);

  // Add frac pair
  void assign_frac_pair(const std::vector<unsigned> frac_pair) {
    frac_pair_ = frac_pair;
  }

  // Return frac pair
  std::vector<unsigned> return_frac_pair() { return frac_pair_; }

  // Find list of element pointers for a given surface id
  std::vector<std::shared_ptr<Element>> find_element_id(
      const unsigned object_id) const {
    std::vector<std::shared_ptr<Element>> vec_elem_ptr; 
    for (auto element_ptr : element_list_ptr_) {
      if (element_ptr->objectid() == object_id) {
        vec_elem_ptr.push_back(element_ptr);
      }
    }
    return vec_elem_ptr;
  }

 private:
  std::vector<std::shared_ptr<Element>> element_list_ptr_;
  std::vector<std::shared_ptr<Surface>> surface_list_ptr_;
  std::vector<std::shared_ptr<Vertex>> vec_vertex_ptr_;
  std::vector<unsigned> frac_pair_;
};

#include "mesh.tcc"

#endif  // READMESH_MESH_H_
