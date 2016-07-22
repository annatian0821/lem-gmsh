#include <cstdlib>

#include <iostream>
#include <memory>

#include "element.h"
#include "mesh.h"
#include "surface.h"
#include "vertex.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: ./readgmsh /path/to/mesh_file.msh" << std::endl;
    std::cerr << "Incorrect number of arguments" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string filename = argv[1];

  // creat mesh object and read msh file
  std::unique_ptr<Mesh> mesh(new Mesh);
  mesh->read_msh_file(filename);
}
