#include <cstdlib>

#include <iostream>
#include <memory>

#include "element.h"
#include "mesh.h"
#include "surface.h"
#include "vertex.h"

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      std::cout << "Usage: ./lem-gmsh /path/to/mesh_file.msh\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    const std::string filename = argv[1];

    // Creat mesh object
    std::unique_ptr<Mesh> mesh(new Mesh(1));

    // Read msh file
    mesh->read_msh_file(filename);

    // Print out fracture pairs and nodes coordinates
    mesh->write_fracture_pairs();

    // Align fractures
    mesh->align_nodes_on_plane("Fracture", 1);

    // Align weakplane
    mesh->align_nodes_on_plane("WeakPlane", 1);

    // Write nodal coordinates
    mesh->write_nodes();

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
