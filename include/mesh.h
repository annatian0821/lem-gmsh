#ifndef READ_GMSH_MESH_H_
#define READ_GMSH_MESH_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

#include "element.h"
#include "settings.h"
#include "surface.h"
#include "vertex.h"

//! Mesh class
//! \brief Mesh class for creating all elements
class Mesh {
 public:
  //! Default constructor
  explicit Mesh(unsigned id) : id_{id} {}

  // Read mesh file
  void read_msh_file(const std::string& filename);

  // Read keywords from msh file
  void read_keyword(std::ifstream& file, const std::string& keyword);

  // Read elements from msh file
  void read_elements(std::ifstream& file);

  // Read vertices from msh file
  void read_vertices(std::ifstream& file);

  // Read surfaces from msh file
  void read_surfaces(std::ifstream& file);

  // Add a vertex pointer
  void vertex_ptr(std::shared_ptr<Vertex>& vertexptr) {
    vertices_.push_back(vertexptr);
  }

  //! Assign the element pointer index to element
  bool element_ptr(unsigned index, std::shared_ptr<Element>& elementptr);

  //! Assign a surface pointer at a given index
  void surface_ptr(unsigned index,
                   const std::shared_ptr<Surface>& surfaceptr) {
    surfaces_.at(index) = surfaceptr;
  }

  //! Append a surface pointer
  void surface_ptr(const std::shared_ptr<Surface>& surfaceptr) {
    surfaces_.push_back(surfaceptr);
  }

  //! Add an element pointer
  bool element_ptr(const std::shared_ptr<Element>& elementptr) {
    // Check if the vertex exists and is not null before adding
    if ((std::find(std::begin(elements_), std::end(elements_),
                   elementptr) == std::end(elements_)) &&
        (elementptr != nullptr)) {
      elements_.push_back(elementptr);
      return true;
    } else
      return false;
  }

  // Frac pairs
  void frac_pairs(unsigned element_id, std::vector<unsigned>& vlist);

  // Find list of element pointers for a given surface id
  std::vector<std::shared_ptr<Element>> find_element_id(
      unsigned surface_id) const {
    std::vector<std::shared_ptr<Element>> vec_elem_ptr;
    for (auto element_ptr : elements_) {
      if (element_ptr->objectid() == surface_id) {
        vec_elem_ptr.push_back(element_ptr);
      }
    }
    return vec_elem_ptr;
  }

  //! Identify fracture surface
  bool find_fracture_surface(const std::string& object_name) {
    if (object_name.find("Fracture") == true)
      return true;
    else
      return false;
  }

  //! Add frac pair to list
  void add_frac_pair(const std::pair<unsigned, unsigned>& fpair) {
    fracture_pairs_.push_back(fpair);
  }

  //! Return vector of frac pairs
  std::vector<std::pair<unsigned, unsigned>> return_fracture_pairs() const {
    return fracture_pairs_;
  }

  //! Print nodes in txt file
  void write_nodes();

  //! Print fracture pairs in txt file
  void write_fractures();

  //! Add centroid to list
  void add_centroid(const std::array<double, 3>& centroid) {
    centroid_.push_back(centroid);
  }

  //! Return vector of centroid coordinates
  std::vector<std::array<double, 3>> return_vec_centroid() const {
    return centroid_;
  }

 private:
  // Return the vertex pointer for a given index
  std::shared_ptr<Vertex> vertex_ptr(unsigned index) const {
    return vertices_.at(index);
  }

  // Return the vertex pointer for a given vertex id
  std::shared_ptr<Vertex> vertex_ptr_at_id(unsigned id) const {
    std::shared_ptr<Vertex> ver_ptr = nullptr;
    for (auto vertex_ptr : vertices_) {
      if (vertex_ptr->id() == id) ver_ptr = vertex_ptr;
    }
    return ver_ptr;
  }

  // Return the surface pointer for a given index
  std::shared_ptr<Surface> surface_ptr(unsigned index) const {
    return surfaces_.at(index);
  }

  // Return the element pointer for a given index
  std::shared_ptr<Element> element_ptr(unsigned index) const {
    return elements_.at(index);
  }
  //! Index
  unsigned id_{std::numeric_limits<unsigned>::max()};

  //! Vector of element pointers
  std::vector<std::shared_ptr<Element>> elements_;

  //! Vector of surface pointers
  std::vector<std::shared_ptr<Surface>> surfaces_;

  //! Vector of vertex pointers
  std::vector<std::shared_ptr<Vertex>> vertices_;

  //! List of fracture pairs
  std::vector<std::pair<unsigned, unsigned>> fracture_pairs_;

  //! Centroid
  std::vector<std::array<double, 3>> centroid_;
};
#endif  // READ_GMSH_MESH_H_
