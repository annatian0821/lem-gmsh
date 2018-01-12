#include <cstdlib>

#include <iostream>
#include <memory>

#include "mesh.h"

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      std::cout << "Usage: ./lem-gmsh /path/to/mesh_file.msh\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    const std::string filename = argv[1];

    // Creat mesh object
    std::unique_ptr<Mesh> mesh(new Mesh(1));

    // Read mesh file
    mesh->read_mesh(filename);

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
