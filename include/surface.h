#ifndef READMESH_SURFACE_H_
#define READMESH_SURFACE_H_

#include <array>
#include <memory>
#include <vector>

#include "vertex.h"

//! Surface class
//! \brief Surface class for

class Surface {
 public:
  //! Constructor with surface id
  explicit Surface(const unsigned surface_id) : surface_id_{surface_id} {}

  //! Return id of the surface
  unsigned surfaceid() const { return surface_id_; }

  //! Assign a vector of nodal pointer to the surface
  void assign_nodes(
      const std::vector<std::shared_ptr<Vertex>>& vec_vertices_ptr) {
    vec_vertices_ptr_ = vec_vertices_ptr;
  }

  //! Assign normal vector to the surface
  void normal_vector(const std::array<double, Dim>& normal_vector) {
    normal_vector_ = normal_vector;
  }

  //! Return the vector of vertices forming the surface
  std::vector<std::shared_ptr<Vertex>> vec_vertices_ptr() const {
    return vec_vertices_ptr_;
  }

  //! Return normal vector of the surface
  std::array<double, Dim> normal_vector() const { return normal_vector_; }

  //! Return surface type (frac or not) 
  bool frac_surf() {return frac_surface_; }

 private:
  bool frac_surface_; 
  unsigned surface_id_;
  std::vector<std::shared_ptr<Vertex>> vec_vertices_ptr_;
  std::array<double, Dim> normal_vector_;
};

#endif  // READMESH_SURFACE_H_
