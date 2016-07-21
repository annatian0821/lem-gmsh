#ifndef READMESH_ELEMENT_H_
#define READMESH_ELEMENT_H_

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <functional>
#include <memory>
#include <vector>

#include "settings.h"
#include "surface.h"
#include "vertex.h"

//! Element class
//! \brief Element for associating element with surfaces and vertices
class Element {
 public:
  //! Constructor with element id
  explicit Element(const unsigned id) : id_{id} {
    surface_list_ptr_.clear();
    vec_vertex_ptr_.clear();
    centroid_ = {0.};
  }

  //! Constructor with id and element type
  Element(const unsigned& id, const unsigned& type, const unsigned& object_id) : id_{id}, type_{type}, object_id_{object_id} {
    vec_vertex_ptr_.clear();
    vec_tags_.clear();
    centroid_ = {0.};
  }

  //! Return id of the element
  unsigned id() const { return id_; }

  //! Return type of element 
  unsigned type() const { return type_; } 

  //! set the surface pointer to surface
  // void surface_ptr(const unsigned index, std::shared_ptr<Surface> surf);

  //! Assign a vertex pointer to an index
  bool vertex_ptr(const unsigned& index, std::shared_ptr<Vertex>& vertex_ptr) {
    if (vertex_ptr) {
      vec_vertex_ptr_.at(index) = vertex_ptr;
      return true;
    } else
      return false;
  }

  //! Add a vertex pointer
  //! \TODO Requires check to see if the vertex exists.
  bool vertex_ptr(std::shared_ptr<Vertex>& vertex_ptr) {
    vec_vertex_ptr_.push_back(vertex_ptr);
  }

  //! Return list of vertex pointers associated with the element
  std::vector<std::shared_ptr<Vertex>> vec_vertex_ptr() {
    return vec_vertex_ptr_;
  }

  // Add a vertex id
  void add_vid(const unsigned id) { vec_vertices_.push_back(id); }

  // Returt list of vertex ids
  std::vector<unsigned> vert_list() { return vec_vertices_; }

  //! Compute centroid of the element
  void compute_centroid();

  //! Retrun centroid of the element
  std::array<double, mesh::DIM> centroid() const { return centroid_; }

  //! Append tag to element
  void tag(const unsigned& tag) { vec_tags_.push_back(tag); }

  //! Return tags
  std::vector<unsigned> vec_tags() { return vec_tags_; }

  //! Return object id
  unsigned objectid() { return object_id_; }

 private:
  //! Element ID
  unsigned id_;
  //! Element type
  unsigned type_;
  //! Centroid of the element
  std::array<double, mesh::DIM> centroid_;
  //! Vector of vertex pointers
  std::vector<std::shared_ptr<Vertex>> vec_vertex_ptr_;
  //! Vector of surface pointers
  std::vector<std::shared_ptr<Surface>> surface_list_ptr_;
  //! Element tags
  std::vector<unsigned> vec_tags_;
  //! Object id
  unsigned object_id_;
  //! List of vertices
  std::vector<unsigned> vec_vertices_;
};

#include "element.tcc"

#endif  // READMESH_ELEMENT_H_
