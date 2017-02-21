#ifndef READ_GMSH_VERTEX_H_
#define READ_GMSH_VERTEX_H_

#include <array>

const unsigned Dim = 3;

//! Vertex class
//! \brief Vertex for element generation
class Vertex {
 public:
  //! Constructor with id and coordinates
  Vertex(unsigned id, const std::array<double, Dim>& coord) : id_{id} {
    coord_ = coord;
  }

  //! Assign coordinates to the vertex
  void coord(const std::array<double, Dim>& coord) { coord_ = coord; }

  //! Return coordinates of the vertex
  std::array<double, Dim> coord() const { return coord_; }

  //! Return coordinates of the vertex with vertex id
  std::array<double, Dim> coord(unsigned id) { return coord_; }

  //! Return id of the vertex
  unsigned id() const { return id_; }

 private:
  //! ID of the vertex
  unsigned id_;
  //! Coordinates of the vertex
  std::array<double, Dim> coord_;
};

#endif  // READ_GMSH_VERTEX_H_
