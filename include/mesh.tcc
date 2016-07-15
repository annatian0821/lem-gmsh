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
    // read_surfaces(file);
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

//! File format
//! $Elements
//! number-of-elements
//! elm-number elm-type number-of-tags < tag > … node-number-list
//! …
//! $EndElements
void Mesh::read_elements(std::ifstream& file) {
  read_keyword(file, "$Elements");

  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  // Total number of elements
  unsigned nelements;
  istream >> nelements;

  //! Element ID
  unsigned element_id = std::numeric_limits<unsigned>::max();
  //! Element type
  unsigned element_type = std::numeric_limits<unsigned>::max();
  //! Number of nodes in an element
  unsigned nnodes = std::numeric_limits<unsigned>::max();
  //! Number of tags
  unsigned ntags = std::numeric_limits<unsigned>::max();
  unsigned tag = std::numeric_limits<unsigned>::max();
  //! Node id
  unsigned nid = std::numeric_limits<unsigned>::max();

  // Iterate through all vertices in the mesh file
  for (unsigned i = 0; i < nelements; ++i) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      // Read ids and element type
      istream >> element_id;
      istream >> element_type;
      istream >> ntags;

      // Create an element pointer
      auto element = std::make_shared<Element>(element_id, element_type);

      // Read element tags
      for (unsigned j = 0; j < ntags; ++j) {
        istream >> tag;
        element->tag(tag);
      }

      // Find the number of nodes for an element type
      nnodes = std::numeric_limits<unsigned>::max();
      auto search = mesh::map_element_type_nodes.find(element_type);
      if (search != mesh::map_element_type_nodes.end())
        nnodes = search->second;

      std::cout << "Element: " << element_id;
      if (nnodes !=  std::numeric_limits<unsigned>::max()) {
        for (unsigned nodes = 0; nodes < nnodes; ++nodes) {
          istream >> nid;
          std::shared_ptr<Vertex> vptr = this->vertex_ptr_at_id(nid);
          if (vptr) vertex_ptr(vptr);
          std::cout << " " << vptr->id();
        }
        std::cout << std::endl;
      }
    } else
      std::cerr << "Invalid entry for node: " << line << std::endl;
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

//! $Nodes
//! number-of-nodes
//! node-number x-coord y-coord z-coord
//! …
//! $EndNodes
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
