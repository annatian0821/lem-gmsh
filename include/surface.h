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

  //! Find fracture surface using surface id
  // bool findfrac(unsigned surface_id);

  //! Find non-frac surface using surface id
  // bool findsurf(unsigned surface_id);

 private:
  unsigned surface_id_;
  std::vector<std::shared_ptr<Vertex>> vec_vertices_ptr_;
  std::array<double, Dim> normal_vector_;
};

#endif  // READMESH_SURFACE_H_
