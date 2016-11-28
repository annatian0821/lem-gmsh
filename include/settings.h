#ifndef READ_GMSH_SETTINGS_H_
#define READ_GMSH_SETTINGS_H_

#include <map>

namespace mesh {
// Mesh dimension
const unsigned dim = 3;

//! Map of element type and number of nodes
const std::map<unsigned, unsigned> map_element_type_nodes{
    {1, 2},  // 2-node line.
    {2, 3},  // 3-node triangle.
    {3, 4},  // 4-node quadrangle.
    {4, 4}   // 4-node tetrahedron
};
}
#endif  // READ_GMSH_SETTINGS_H_
