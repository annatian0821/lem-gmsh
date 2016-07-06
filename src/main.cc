#include <iostream>
#include <memory>

#include "element.h"
#include "surface.h"
#include "vertex.h"
#include "mesh.h" 

int main(int argc, char** argv) {
  unsigned id = 0;
  const unsigned Dim = 3;
  std::array<double, Dim> coord{0., 0., 0.};

  auto vertex = std::make_shared<Vertex>(id, coord);

  std::cout << "Vertex id: " << vertex->id() << std::endl;

  auto surface = std::make_shared<Surface>(id);
 
  // creat mesh object and read msh file
  auto mesh = std::make_shared<Mesh>();
  mesh->read_msh_file("mesh.msh");

}
