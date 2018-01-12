#ifndef LEM_GMSH_MESH_H_
#define LEM_GMSH_MESH_H_

#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

#include <Eigen/Core>

#include "element_map.h"

//! Mesh class
//! \brief Mesh class for creating nodes and elements from GMSH input
class Mesh {
public:
  //! Default constructor
  explicit Mesh(unsigned id) : id_{id} {}

  // Read mesh file
  void read_mesh(const std::string &filename);

  // Read keywords from msh file
  void read_keyword(std::ifstream &file, const std::string &keyword);

  // Read elements from msh file
  void read_elements(std::ifstream &file);

  // Read vertices from msh file
  void read_vertices(std::ifstream &file);

private:
  //! Index
  unsigned id_{std::numeric_limits<unsigned>::max()};

  //! Vector of elements (collection of vertex ids)
  std::map<unsigned, std::vector<unsigned>> elements_;

  //! A map of vertex id and coordinates
  std::map<unsigned, Eigen::Vector3d> vertices_;

  //! Vector of LEM nodes (element centroids)
  std::vector<Eigen::Vector3d> nodes_;
};

#endif // LEM_GMSH_MESH_H_
