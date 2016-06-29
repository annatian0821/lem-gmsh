#ifdef READMESH_VERTEX
#define READMESH_VERTEX

#include <vector>
#include <array>

class Vertex {
  
  private: 
   // creating private variables for coordinates and id  
    std::array<double, 3> vcoord_;
    std::vector<unsigned> vid_; 

  public: 
   // creating public variables for coordinates and id 
    std::array<double, 3> vcoord;
    std::vector<unsigned> vid; 
    
   // Default constructor 
    Vertex(){};

   // Constructor with coordinates and id
    Vertex(const std::array<double, 3>& vcoord, const std::vector<unsigned>& vid): vid_{vid}, vcoord_{vcoord}{}
  
   // Assign coordinates to the vertex
    void vcoord(const std::array<double, 3>& vcoord) {vcoord_ = vcoord; }
   
   // Assign id to the vertex
    void vid(const std::vector<unsigned>& vid) {vid_ = vid; } 
   
   // Return coordinates 
    std::array<double, 3> vcoord() const {return vcoord_; }

   // Return id
    std::vector<unsigned> vid() const {return vid_; }

};

#endif // READMESH_VERTEX
