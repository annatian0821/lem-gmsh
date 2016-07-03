#ifndef READMESH_ELEMENT_H_
#define READMESH_ELEMENT_H_

#include "surface.h"
#include "vertex.h"

#include <memory>
#include <vector>

//! Element class
//! \brief Element for associating element with surfaces and vertices

class Element {
 public:
  //! Constructor with element id
  explicit Element(const unsigned elementid) : elementid_{elementid} {
    surface_list_ptr_.clear();
    vertex_list_ptr_.clear();
  }

  //! Return id of the element
  unsigned elementid() const { return elementid_; }

  //! set the surface pointer to surface
  void surface_ptr(const unsigned index, std::shared_ptr<Surface> surf);

  //! set the vertex pointer to vertex
  void vertex_ptr(const unsigned index, std::shared_ptr<Vertex> vert);

  //! Return sufrace pointer for a given index
  std::shared_ptr<Surface> surface_ptr(const unsigned index) const;

  //! Return vertex pointer for a given index
  std::shared_ptr<Vertex> vertex_ptr(const unsigned index) const;

  //! Return the vector of surface pointers
  std::vector<std::shared_ptr<Surface>> surface_list_ptr() const {
    return surface_list_ptr_;
  }

  //! Return the vector of vertex pointers
  std::vector<std::shared_ptr<Vertex>> vertex_list_ptr() const {
    return vertex_list_ptr_;
  }

 private:
  unsigned elementid_;
  std::vector<std::shared_ptr<Surface>> surface_list_ptr_;
  std::vector<std::shared_ptr<Vertex>> vertex_list_ptr_;
};

#endif  // READMESH_ELEMENT_H_
