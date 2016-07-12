#include "mesh.h"

//! Check if msh file exists
void Mesh::read_msh_file(const std::string& filename) {

  std::ifstream file;
  file.open(filename.c_str(), std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Msh file does not exist \n";
    std::exit(EXIT_FAILURE);
  }
  if (file.good()) {
    read_msh_vertex(&file);
    read_msh_element(&file);
    read_msh_surface(&file);
  }
}

//! Read keywords
void Mesh::read_keyword(std::ifstream* file, std::string keyword) {

  std::string line;
  file->clear();
  file->seekg(0, std::ios::beg);
  while (std::getline(*file, line)) {
    if (line != keyword) {
      if (line.find(keyword) != std::string::npos) {
        std::cout << "Cannot find keyword: " << keyword << std::endl;
        std::cout << "Line read -" << line << '-' << std::endl;
        break;
      };
    } else {
      std::cout << "Read keyword -" << keyword << "- successfully" << std::endl;
      break;
    }
  }
}

//! Read element ids & vertex list
void Mesh::read_msh_element(std::ifstream* file) {

  read_keyword(file, "$Elements");
  unsigned element_no;
  *file >> element_no;
  std::cout << "Number of elements = " << element_no << std::endl;
  unsigned elementid;
  unsigned temp;
  unsigned type;
  unsigned object_id;
  unsigned j = 1;
  unsigned k = 1;
  std::string line;
  std::array<double, 4> vert_list;
  while (std::getline(*file, line)) {
    std::istringstream istream(line);
    ++k;
    if (k > 2) {
      // to ignore comment line with #
      if (line.find('#') == std::string::npos) {
        if (line != "") {
          while (istream.good()) {
            for (unsigned i = 0; i < 9; ++i) {
              // Read vertices associated with the element
              if (i == 0) {
                istream >> temp;
              } else if (i == 1) {
                istream >> type;
              } else if (i == 2) {
                istream >> temp;
              } else if (i == 3) {
                istream >> object_id;
              } else if (i == 4) {
                istream >> temp;
              } else {
                istream >> vert_list.at(i - 5);
              }
            }
          }
          // temp output for debugging
          std::cout << "vertix list " << vert_list.at(2) << std::endl;
          // Create a new element and push it to mesh
          auto element = std::make_shared<Element>(elementid);
          ++elementid;
          this->element_ptr(element);
          ++j;
          if (j > element_no) {
            break;
          };
        }
      }
    }
  }
}

//! Read Surface ID and Type
void Mesh::read_msh_surface(std::ifstream* file) {

  read_keyword(file, "$PhysicalNames");
  unsigned surf_no;
  *file >> surf_no;
  std::cout << "Number of physical objects = " << surf_no << std::endl;
  unsigned sid = 0;
  unsigned stype;
  unsigned temp;
  unsigned j = 1;
  unsigned k = 1;
  bool frac_surf;
  std::string line;
  std::string object_name;
  while (std::getline(*file, line)) {
    std::istringstream istream(line);
    ++k;
    if (k > 2) {
      // to ignore comment line with #
      if (line.find('#') == std::string::npos) {
        if (line != "") {
          while (istream.good()) {
            for (unsigned i = 0; i < 4; ++i) {
              // Read coordinates
              if (i == 0) {
                istream >> stype;
              } else if (i == 1) {
                istream >> temp;
              } else {
                istream >> object_name;
              }
            }
            if (object_name.find("F") == true) {
              frac_surf = true;
            } else {
              frac_surf = false;
            }
          }
        }
        // Temp output for debugging
        std::cout << "physical object type " << object_name
                  << " fracture surface  " << frac_surf << std::endl;
        // Create a new vertex and push it to mesh
        auto surface = std::make_shared<Surface>(sid);
        ++sid;
        this->surface_ptr(surface);
        ++j;
        if (j > surf_no) {
          break;
        };
      }
    }
  }
}

//! Read vertex ids and coordinates
void Mesh::read_msh_vertex(std::ifstream* file) {

  read_keyword(file, "$Nodes");
  unsigned vert_no;
  *file >> vert_no;
  std::cout << "Number of vertices = " << vert_no << std::endl;
  unsigned vid = 0;
  unsigned temp;
  unsigned j = 1;
  unsigned k = 1;
  std::string line;
  std::array<double, 3> vcoord;
  while (std::getline(*file, line)) {
    std::istringstream istream(line);
    ++k;
    if (k > 2) {
      // to ignore comment line with #
      if (line.find('#') == std::string::npos) {
        if (line != "") {
          while (istream.good()) {
            for (unsigned i = 0; i < 4; ++i) {
              // Read coordinates
              if (i == 0)
                istream >> temp;
              else
                istream >> vcoord.at(i - 1);
            }
          }
          // temp output for debugging
          std::cout << "coordinates " << vcoord << std::endl;
          // Create a new vertex and push it to mesh
          auto vertex = std::make_shared<Vertex>(vid, vcoord);
          ++vid;
          this->vertex_ptr(vertex);
          ++j;
          if (j > vert_no) {
            break;
          };
        }
      }
    }
  }
}
