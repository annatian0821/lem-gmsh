#ifndef READMESH_SURFACES_H_
#define READMESH_SURFACES_H_

#include <array>
#include <vector>

// Surface class
// \brief Surface class for 

const unsigned Dim = 3; 

class Surfaces {
 public: 
  // Default constructor (temperory) for debugging only 
  Surfaces(){}

  // Constructor with surface id
  explicit Surfaces(const unsigned surface_id) : surface_id_{surface_id} {}
 
  // Return id of the surface
  unsigned surfaceid() const {return surface_id_;}

  // Assign list of nodes to the surface
  void nodeslist(const std::vector<unsigned>& nodes_list) {nodes_list_ = nodes_list; } 

  // Assign normal vector to the surface
  void normvect(const std::array<double, Dim>& norm_vect) {norm_vect_ = norm_vect; }

  // Return list of nodes of the surface
  std::vector<unsigned> nodes_list() const {return nodes_list_; }

  // Return normal vector of the surface
  std::array<double, Dim> norm_vect() const {return norm_vect_; }

  // Find fracture surfaces using surface id 
  bool findfrac(unsigned surface_id); 

  // Find non-frac surfaces using surface id
  bool findsurf (unsigned surface_id); 

 private: 
  std::vector<unsigned> nodes_list_;
  std::array<double, Dim> norm_vect_; 
  unsigned surface_id_; 

};

#endif // READMESH_SURFACES_H_
 

