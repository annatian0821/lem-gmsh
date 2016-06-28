#ifdef READMESH_VERTEX
#define READMESH_VERTEX

#include <vector>
#include <array>

class Vertex {

  private: 
    std::array<double, 3> vcoord;
    std::vector<double> vid; 

};

#endif // READMESH_VERTEX
