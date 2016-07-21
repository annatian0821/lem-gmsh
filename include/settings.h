#ifndef READMESH_SETTINGS_H_
#define READMESH_SETTINGS_H_

#include <map>

namespace mesh {
// Mesh dimension
const unsigned DIM = 3;

//! Map of element type and number of nodes
std::map<unsigned, unsigned> map_element_type_nodes{
    {1, 2},  // 2-node line.
    {2, 3},  // 3-node triangle.
    {3, 4},  // 4-node quadrangle.
    {4, 4}   // 4-node tetrahedron
};

}
#endif  // READMESH_SETTINGS_H_
