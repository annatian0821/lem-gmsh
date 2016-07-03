#ifndef READMESH_VERTEX_H_
#define READMESH_VERTEX_H_

#include <array>

//! Vertex class
//! \brief Vertex for element generation

const unsigned Dim = 3;

class Vertex {
 public:
  //! Constructor with coordinates and id
  Vertex(const unsigned& id, const std::array<double, Dim>& coord)
      : id_{id}, coord_{coord} {}

  //! Assign coordinates to the vertex
  void coord(const std::array<double, Dim>& coord) { coord_ = coord; }

  //! Return coordinates of the vertex
  std::array<double, Dim> coord() const { return coord_; }

  //! Return id of the vertex
  unsigned id() const { return id_; }

 private:
  //! ID of the vertex
  unsigned id_;
  //! Coordinates of the vertex
  std::array<double, Dim> coord_;
};

#endif  // READMESH_VERTEX_H_
