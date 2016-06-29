#ifdef READMESH_VERTEX
#define READMESH_VERTEX

#include <array>

// Vertex class
// \brief Vertex for element generation 

class Vertex {
 public: 
  // Constructor with coordinates and id
  Vertex(const std::array<double, 3>& vcoord, const unsigned& vid): vid_{vid}, vcoord_{vcoord}{}
  
  // Assign coordinates to the vertex
  void vcoord(const std::array<double, 3>& vcoord) {vcoord_ = vcoord; }
   
  // Return coordinates of the vertex
  std::array<double, 3> vcoord() const {return vcoord_; }

  // Return id of the vertex
  unsigned vid() const {return vid_; }

 private:  
  std::array<double, 3> vcoord_;
  unsigned vid_;

};

#endif // READMESH_VERTEX
