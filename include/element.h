#ifndef READ_GMSH_ELEMENT_H_
#define READ_GMSH_ELEMENT_H_

#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
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
  explicit Element(unsigned id) : id_{id} {
    surface_list_ptr_.clear();
    vertices_.clear();
    centroid_ = {0.};
  }

  //! Constructor with id and element type
  Element(unsigned id, unsigned type, unsigned object_id)
      : id_{id}, type_{type}, object_id_{object_id} {
    vertices_.clear();
    vec_tags_.clear();
    centroid_ = {0.};
  }

  //! Return id of the element
  unsigned id() const { return id_; }

  //! Return type of element
  unsigned type() const { return type_; }

  //! Assign a vertex pointer to an index
  bool vertex_ptr(unsigned index, std::shared_ptr<Vertex>& vertex_ptr) {
    if (vertex_ptr) {
      vertices_.at(index) = vertex_ptr;
      return true;
    } else
      return false;
  }

  //! Add a vertex pointer
  bool vertex_ptr(std::shared_ptr<Vertex>& vertex_ptr) {
    // Check if the vertex exists and is not null before adding
    if ((std::find(std::begin(vertices_), std::end(vertices_),
                   vertex_ptr) == std::end(vertices_)) &&
        (vertex_ptr != nullptr)) {
      vertices_.push_back(vertex_ptr);
      return true;
    } else
      return false;
  }

  //! Return vector of  vertex ids forming the element
  std::vector<unsigned> vec_vertex_ids() {
    std::vector<unsigned> vec_vertex_ids_;
    vec_vertex_ids_.clear();
    for (const auto& vtr : vertices_) {
      auto vid = vtr->id();
      vec_vertex_ids_.push_back(vid);
    }
    return vec_vertex_ids_;
  }

  // Add a vertex id
  void add_vid(unsigned id) { vec_vertices_.push_back(id); }

  //! Compute centroid of the element
  void compute_centroid();

  //! Assign centroid of the element
  void centroid(const std::array<double, mesh::dim>& centroid) {
    centroid_ = centroid;
  }

  //! Assign centroid of the element
  void centroid_at(unsigned index, double coordinate) {
    centroid_.at(index) = coordinate;
  }

  //! Return centroid of the element
  std::array<double, mesh::dim> centroid() const { return centroid_; }

  //! Append tag to element
  void tag(unsigned tag) { vec_tags_.push_back(tag); }

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
  std::array<double, mesh::dim> centroid_;
  //! Vector of vertex pointers
  std::vector<std::shared_ptr<Vertex>> vertices_;
  //! Vector of surface pointers
  std::vector<std::shared_ptr<Surface>> surface_list_ptr_;
  //! Element tags
  std::vector<unsigned> vec_tags_;
  //! Object id
  unsigned object_id_;
  //! List of vertices
  std::vector<unsigned> vec_vertices_;
};
#endif  // READ_GMSH_ELEMENT_H_
