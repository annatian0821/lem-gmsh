#ifndef READMESH_ELEMENT_H_
#define READMESH_ELEMENT_H_

#include "settings.h"
#include "surface.h"
#include "vertex.h"

#include <memory>
#include <vector>

//! Element class
//! \brief Element for associating element with surfaces and vertices
class Element {
 public:

  //! Constructor with element id
  explicit Element(const unsigned id) : id_{id} {
    surface_list_ptr_.clear();
    vec_vertex_ptr_.clear();
  }

  //! Constructor with id and element type
  Element(const unsigned& id, const unsigned& type) : id_{id}, type_{type} {
    vec_vertex_ptr_.clear();
    vec_tags_.clear();
  }

  //! Return id of the element
  unsigned id() const { return id_; }

  //! set the surface pointer to surface
  // void surface_ptr(const unsigned index, std::shared_ptr<Surface> surf);

  //! Assign a vertex pointer to an index
  bool vertex_ptr(const unsigned& index,
                  std::shared_ptr<Vertex>& vertex_ptr) {
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

  // //! Return sufrace pointer for a given index
  // std::shared_ptr<Surface> surface_ptr(const unsigned index) const;

  // //! Return vertex pointer for a given index
  // std::shared_ptr<Vertex> vertex_ptr(const unsigned index) const;

  // //! Return the vector of surface pointers
  // std::vector<std::shared_ptr<Surface>> surface_list_ptr() const {
  //   return surface_list_ptr_;
  // }

  // //! Return the vector of vertex pointers
  // std::vector<std::shared_ptr<Vertex>> vertex_list_ptr() const {
  //   return vertex_list_ptr_;
  // }

  //! Compute centroid of the element
  void compute_centroid();

  //! Retrun centroid of the element
  std::array<double, mesh::DIM> centroid() const { return centroid_; }

  //! Append tag to element
  void tag(const unsigned& tag) { vec_tags_.push_back(tag); }

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
};

#include "element.tcc"

#endif  // READMESH_ELEMENT_H_
