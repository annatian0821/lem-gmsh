#ifndef READMESH_VERTEX_H_
#define READMESH_VERTEX_H_

#include <array>

// Vertex class
// \brief Vertex for element generation 

const unsigned Dim = 3;

class Vertex {
 public:
  // Default constructor (temperory) for debuggin only 
  Vertex(){}

  // Constructor with coordinates and id
  Vertex(const std::array<double, Dim>& vcoord, const unsigned& vid): vid_{vid}, vcoord_{vcoord}{}
  
  // Assign coordinates to the vertex
  void vcoord(const std::array<double, Dim>& vcoord) {vcoord_ = vcoord; }
   
  // Return coordinates of the vertex
  std::array<double, Dim> vcoord() const {return vcoord_; }

  // Return id of the vertex
  unsigned vid() const {return vid_; }

 private: 
  std::array<double, Dim> vcoord_;
  unsigned vid_;

};

#endif // READMESH_VERTEX_H_
