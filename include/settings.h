#ifndef READMESH_SETTINGS_H_
#define READMESH_SETTINGS_H_

#include <map>

namespace mesh {
// Mesh dimension
const unsigned DIM = 3;

//! Map of element type and number of nodes
extern std::map<unsigned, unsigned> map_element_type_nodes;
}
#endif  // READMESH_SETTINGS_H_
