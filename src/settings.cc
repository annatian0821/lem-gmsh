#include <map>

#include "settings.h"

namespace mesh {
std::map<unsigned, unsigned> map_element_type_nodes{
    {1, 2},  // 2-node line.
    {2, 3},  // 3-node triangle.
    {3, 4},  // 4-node quadrangle.
    {4, 4}   // 4-node tetrahedron
};
}
