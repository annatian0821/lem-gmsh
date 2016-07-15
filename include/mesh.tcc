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
    read_vertices(file);
    read_elements(file);
    read_surfaces(file);
  }
}

//! Read keywords
void Mesh::read_keyword(std::ifstream& file, std::string keyword) {

  std::string line;
  file.clear();
  file.seekg(0, std::ios::beg);
  while (std::getline(file, line)) {
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

//! Read element ids and list of vertices associated with it
//! \param[in] file Input file stream object of msh file
void Mesh::read_elements(std::ifstream& file) {
  read_keyword(file, "$Elements");

  // Total number of elements
  unsigned nelements;
  file >> nelements;
  // std::cout << "Number of elements = " << element_no << std::endl;

  // Element id, type, object id, and list of vertices
  unsigned elementid = std::numeric_limits<unsigned>::max();
  unsigned type, objectid, listsize, temp;
  std::array<double, 4> vlist;

  std::string line;
  // Iterate through all the elements in the msh file
  for (unsigned i = 0; i < nelements;) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      // Initialize ids and list of vertices
      elementid = std::numeric_limits<unsigned>::max();
      vlist.fill(std::numeric_limits<double>::quiet_NaN());

      // Read element ids, type, object id, and list of vertices
      for (unsigned i = 0; i < 9; ++i) {
        if (i == 0)
          istream >> elementid;
        else if (i == 1) {
          istream >> type;
          switch (type) {
            case 1:
              listsize = 2;
              break;
            case 2:
              listsize = 3;
              break;
            case 4:
              listsize = 4;
              break;
            default:
              std::cout << "Read type error, type = " << type << std::endl;
          }
        } else if (i == 2)
          istream >> temp;
        else if (i == 3)
          istream >> objectid;
        else if (i == 4)
          istream >> temp;
        else
          istream >> vlist.at(i - 5);
      }

      // Create a new element and add it to list
      auto element = std::make_shared<Element>(elementid, vlist, listsize);
      this->element_ptr(element);

      // Calculate centoid coordinates for an element
      element->calculate_centroid(elementid, vlist, vertex_list_ptr_, listsize);

#ifdef DEBUG
      for (unsigned k = 0; k < element_list_ptr_.size(); ++k) {
        auto list = element_list_ptr_.at(k)->vertex_element_list();
        for (unsigned j = 0; j < listsize; ++j) std::cout << list.at(j) << " ";
        std::cout << std::endl;
      }
#endif

#ifdef DEBUG
      // Printing out coordinates for debugging - success -
      for (unsigned i = 0; i < listsize; ++i) {
        auto coordinates = vertex_list_ptr_.at(vlist.at(i) - 1)->coord();
        std::cout << elementid << " " << vlist.at(i) << " " << list_size << " ";
        for (unsigned j = 0; j < coordinates.size(); ++j) {
          std::cout << coordinates.at(j) << " ";
        }
        std::cout << std::endl;
      }
#endif

      // Increment number of element on successful read
      ++i;
    } else
      std::cerr << "Invalid entry for element: " << line << std::endl;
  }
}

//! Read ids and types of surfaces
//! \param[in] file Input file stream object of msh file 
void Mesh::read_surfaces(std::ifstream& file) {
  read_keyword(file, "$PhysicalNames");

  // Total number of surfaces
  unsigned nsurfaces;
  file >> nsurfaces;
  // std::cout << "Number of physical objects = " << surf_no << std::endl;

  // Surface id and type
  unsigned sid = std::numeric_limits<unsigned>::max();
  unsigned stype, temp;
  bool fracsurf;
  std::string objectname;

  std::string line;
  //  Iterate through all surfaces in the msh file
  for (unsigned i = 0; i < nsurfaces;) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      // Initialize ids
      sid = std::numeric_limits<unsigned>::max();

      // Read ids and types
      for (unsigned i = 0; i < 4; ++i) {
        // Read coordinates
        if (i == 0) {
          istream >> stype;
        } else if (i == 1) {
          istream >> sid;
        } else {
          istream >> objectname;
        }
      }
      if (objectname.find("F") == true) {
        fracsurf = true;
      } else {
        fracsurf = false;
      }
      // Create a new vertex and add it to list
      auto surface = std::make_shared<Surface>(sid);
      this->surface_ptr(surface);

      // Increment number of surfaces on successful read
      ++i;

    } else
      std::cerr << "Invalid entry for surface: " << line << std::endl;
  }
}

//! Read ids and coordinates of vertices
//! \param[in] file Input file stream object of msh file
void Mesh::read_vertices(std::ifstream& file) {
  read_keyword(file, "$Nodes");

  // Total number of vertices
  unsigned nvertices;
  file >> nvertices;
  //  std::cout << "Total number of vertices = " << nvertices << std::endl;

  // Vertex id and coordinates
  unsigned vid = std::numeric_limits<unsigned>::max();
  std::array<double, mesh::DIM> vcoordinates;

  std::string line;
  // Iterate through all vertices in the mesh file
  for (unsigned i = 0; i < nvertices;) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      // Initialise ids and coordinates
      vid = std::numeric_limits<unsigned>::max();
      vcoordinates.fill(std::numeric_limits<double>::quiet_NaN());

      // Read ids and coordinates
      istream >> vid;
      for (unsigned j = 0; j < vcoordinates.size(); ++j) {
        istream >> vcoordinates.at(j);
      }

      // Create a new vertex and add to list
      auto vertex = std::make_shared<Vertex>(vid, vcoordinates);
      this->vertex_ptr(vertex);

      // Increament number of vertex on successful read
      ++i;

#ifdef DEBUG
      std::cout << vertex->id() << std::endl;
#endif
    } else
      std::cerr << "Invalid entry for node: " << line << std::endl;
  }
}
