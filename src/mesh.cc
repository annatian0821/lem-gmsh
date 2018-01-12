#include "mesh.h"

//! \brief Check if a msh file exists
//! \param[in] filename Mesh file name
void Mesh::read_mesh(const std::string& filename) {

  std::ifstream file;
  file.open(filename.c_str(), std::ios::in);
  if (!file.is_open())
    throw std::runtime_error("Specified GMSH file does not exist");
  if (file.good()) {
    read_vertices(file);
    read_elements(file);
  }
  file.close();
}

//! \brief Read keywords
//! \param[in] file Input file stream
//! \param[in] keyword Search for keyword
void Mesh::read_keyword(std::ifstream& file, const std::string& keyword) {

  bool read_status = false;
  std::string line;
  file.clear();
  file.seekg(0, std::ios::beg);
  while (std::getline(file, line)) {
    if (line != keyword) {
      if (line.find(keyword) != std::string::npos) {
        break;
      };
    } else {
      std::cout << "Read keyword: " << keyword << " successfully\n";
      read_status = true;
      break;
    }
  }
  if (!read_status) {
    std::cerr << "Cannot find keyword: " << keyword << '\n';
  }
}

//! \brief Read element ids and list of vertices associated with it
//! \details <strong>Element GMSH file format</strong><br/>
//! $Elements<br/>
//! number-of-elements<br/>
//! elm-number elm-type number-of-tags < tag > … node-number-list<br/>
//! …<br/>
//! $EndElements
//! \param[in] file Input file stream object of msh file
void Mesh::read_elements(std::ifstream& file) {
  read_keyword(file, "$Elements");
/*
  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  // Total number of elements
  unsigned nelements;
  istream >> nelements;
  std::cout << "Total number of elements = " << nelements << '\n';

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
  unsigned node_id = std::numeric_limits<unsigned>::max();
  //! Object id
  unsigned object_id = std::numeric_limits<unsigned>::max();
  //! Volume id
  unsigned volume_id = 0;

  // Iterate through all vertices in the mesh file
  for (unsigned i = 0; i < nelements; ++i) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      // Read ids and element type
      istream >> element_id;
      istream >> element_type;
      istream >> ntags;
      istream >> object_id;

      // Create an element pointer
      auto element =
          std::make_shared<Element>(element_id, element_type, object_id);

      // Read element tags
      for (unsigned j = 0; j < ntags - 1; ++j) {
        istream >> tag;
        element->tag(tag);
      }

      // Find the number of nodes for an element type
      nnodes = mesh::map_element_type_nodes.at(element_type);

      for (unsigned nodes = 0; nodes < nnodes; ++nodes) {
        istream >> node_id;
        element->add_vid(node_id);
        auto vptr = this->vertex_ptr_at_id(node_id);
        if (vptr) element->vertex_ptr(vptr);
      }

      // Calculate centroid and print coordinates into nodes.txt
      if (element_type == 4) {
        element->compute_centroid();
        element->volume_id(volume_id);
        if (volume_id != std::numeric_limits<unsigned>::max())
          volume_elements_[volume_id] = element;
        ++volume_id;
      }

      this->element_ptr(element);
    } else
      std::cerr << "Invalid entry for node: " << line << '\n';
  }
  */
}

//! \brief Read ids and coordinates of vertices
//! \param[in] file Input file stream object of msh file
//! \details <strong>File structure for vertices</strong><br/>
//! $Nodes<br/>
//! number-of-nodes<br/>
//! node-number x-coord y-coord z-coord<br/>
//! …<br/>
//! $EndNodes<br/>
void Mesh::read_vertices(std::ifstream& file) {
  read_keyword(file, "$Nodes");

  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  // Total number of vertices
  unsigned nvertices;
  istream >> nvertices;
  std::cout << "Total number of vertices = " << nvertices << '\n';

  // Vertex id and coordinates
  unsigned vid = std::numeric_limits<unsigned>::max();
  Eigen::Vector3d coordinates;

  // Iterate through all vertices in the mesh file
  for (unsigned i = 0; i < nvertices;) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      // Initialise ids and coordinates
      vid = std::numeric_limits<unsigned>::max();

      // Read ids and coordinates
      istream >> vid;
      for (unsigned j = 0; j < coordinates.size(); ++j)
        istream >> coordinates[j];

      // Add vertex coordinates and id to a map
      vertices_[vid] = coordinates;
      
      // Increament number of vertex on successful read
      ++i;
    } else {
      std::cerr << "Invalid entry for node: " << line << '\n';
    }
  }
}
