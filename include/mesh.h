#ifndef READMESH_MESH_H_
#define READMESH_MESH_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
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
    vec_element_ptr_.clear();
    vec_surface_ptr_.clear();
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

  // Add a vertex pointer
  void vertex_ptr(std::shared_ptr<Vertex>& vertexptr) {
    vec_vertex_ptr_.push_back(vertexptr);
  }

  //! Assign the element pointer index to element
  bool element_ptr(const unsigned index, std::shared_ptr<Element>& elementptr) {
    if (elementptr) {
      vec_element_ptr_.at(index) = elementptr;
      return true;
    } else
      return false;
  }

  //! Assign a surface pointer at a given index
  void surface_ptr(const unsigned& index,
                   std::shared_ptr<Surface>& surfaceptr) {
    vec_surface_ptr_.at(index) = surfaceptr;
  }

  //! Append a surface pointer
  void surface_ptr(std::shared_ptr<Surface>& surfaceptr) {
    vec_surface_ptr_.push_back(surfaceptr);
  }

  //! Add an element pointer
  bool element_ptr(std::shared_ptr<Element>& elementptr) {
    // Check if the vertex exists and is not null before adding
    if ((std::find(std::begin(vec_element_ptr_), std::end(vec_element_ptr_),
                   elementptr) == std::end(vec_element_ptr_)) &&
        (elementptr != nullptr)) {
      vec_element_ptr_.push_back(elementptr);
      return true;
    } else
      return false;
  }

  // Frac pairs
  void frac_pairs(const unsigned element_id, const std::vector<unsigned> vlist);

  // Find list of element pointers for a given surface id
  std::vector<std::shared_ptr<Element>> find_element_id(
      const unsigned object_id) const {
    std::vector<std::shared_ptr<Element>> vec_elem_ptr;
    for (auto element_ptr : vec_element_ptr_) {
      if (element_ptr->objectid() == object_id) {
        vec_elem_ptr.push_back(element_ptr);
      }
    }
    return vec_elem_ptr;
  }

  //! Identify fracture surface
  bool find_fracture_surface(const std::string object_name) {
    if (object_name.find("Fracture") == true)
      return true;
    else
      return false;
  }

  //! Add frac pair to list
  void add_frac_pair(std::pair<unsigned, unsigned> fpair) {
    frac_pair_2_.push_back(fpair);
  }

  //! Return vector of frac pairs 
  std::vector<std::pair<unsigned, unsigned>> return_frac_pair_2() { 
    return frac_pair_2_; 
  } 

  //! Print nodes in txt file 
  void write_nodes(); 

  //! Print fracture pairs in txt file 
  void write_fractures(); 

  //! Add centroid to list 
  void add_centroid(std::array<double, 3> centroid) { 
    centroid_.push_back(centroid); 
  } 

  //! Return vector of centroid coordinates 
  std::vector<std::array<double, 3>> return_vec_centroid () { 
    return centroid_; 
  } 

 private:
  // Return the vertex pointer for a given index
  std::shared_ptr<Vertex> vertex_ptr(const unsigned index) const {
    return vec_vertex_ptr_.at(index);
  }

  // Return the vertex pointer for a given vertex id
  std::shared_ptr<Vertex> vertex_ptr_at_id(const unsigned id) const {
    std::shared_ptr<Vertex> ver_ptr = nullptr;
    for (auto vertex_ptr : vec_vertex_ptr_) {
      if (vertex_ptr->id() == id) ver_ptr = vertex_ptr;
    }
    return ver_ptr;
  }

  // Return the surface pointer for a given index
  std::shared_ptr<Surface> surface_ptr(const unsigned index) const {
    return vec_surface_ptr_.at(index);
  }

  // Return the element pointer for a given index
  std::shared_ptr<Element> element_ptr(const unsigned index) const {
    return vec_element_ptr_.at(index);
  }

  //! Vector of element pointers
  std::vector<std::shared_ptr<Element>> vec_element_ptr_;
  //! Vector of surface pointers
  std::vector<std::shared_ptr<Surface>> vec_surface_ptr_;
  //! Vector of vertex pointers
  std::vector<std::shared_ptr<Vertex>> vec_vertex_ptr_;
  std::vector<std::pair<unsigned, unsigned>> frac_pair_2_;
  std::vector<std::array<double, 3>> centroid_; 
};
#endif  // READMESH_MESH_H_
