#ifndef READMESH_ELEMENT_H_
#define READMESH_ELEMENT_H_

//#include "mesh.h"
#include "surface.h"
#include "vertex.h"

#include <memory>
#include <vector>

//! Element class
//! \brief Element for associating element with surfaces and vertices

class Element {
 public:
  //! Default constructor
  Element() {}

  //! Constructor with element id
  explicit Element(const unsigned elementid) : elementid_{elementid} {
    surface_list_ptr_.clear();
    vertex_list_ptr_.clear();
  }

  //! Constructor with id, list of vertices, and list size
  Element(const unsigned& elementid,
          const std::array<double, 4>& vertex_element_list,
          const unsigned& listsize)
      : elementid_{elementid} {
    vertex_element_list_ = vertex_element_list;
    listsize_ = listsize;
  }

  //! Return id of the element
  unsigned elementid() const { return elementid_; }

  //! Return vertex element list
  std::array<double, 4> vertex_element_list() const {
    return vertex_element_list_;
  }

  //! Return list size
  unsigned listsize() const { return listsize_; }

  //! set the surface pointer to surface
  void surface_ptr(const unsigned index, std::shared_ptr<Surface> surf);

  //! set the vertex pointer to vertex
  void vertex_ptr(const unsigned index,
                  std::vector<std::shared_ptr<Vertex>> vertex_list_ptr,
                  const unsigned listsize) {
    vertex_list_ptr_ = vertex_list_ptr;
    listsize_ = listsize;
  }

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

  //! Calculate centroid of vertex pointer
  void calculate_centroid(const unsigned id,
                          std::array<double, 4> vertex_element_list,
                          std::vector<std::shared_ptr<Vertex>> vertex_list_ptr,
                          const unsigned list_size);

  //! Add centroid to list
  void add_centroid(std::array<double, 3>& centroid) { centroid_ = centroid; }

 private:
  unsigned elementid_, listsize_;
  std::array<double, 3> centroid_;
  std::array<double, 4> vertex_element_list_;
  std::vector<std::shared_ptr<Surface>> surface_list_ptr_;
  std::vector<std::shared_ptr<Vertex>> vertex_list_ptr_;
};

#include "element.tcc"

#endif  // READMESH_ELEMENT_H_
