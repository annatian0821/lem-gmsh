#ifndef READ_GMSH_ELEMENT_MAP_H_
#define READ_GMSH_ELEMENT_MAP_H_

#include <map>

namespace mesh {
// Mesh dimension
const unsigned dim = 3;

//! Map of element type and number of vertices
const std::map<unsigned, unsigned> map_element_type_vertices{
    {1, 2},  // 2-node line.
    {2, 3},  // 3-node triangle.
    {3, 4},  // 4-node quadrangle.
    {4, 4}   // 4-node tetrahedron
};
}
#endif  // READ_GMSH_ELEMENT_MAP_H_
