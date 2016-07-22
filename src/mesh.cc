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
#ifdef DEBUG
        std::cout << "Cannot find keyword: " << keyword << std::endl;
        std::cout << "Line read -" << line << '-' << std::endl;
#endif
        break;
      };
    } else {
#ifdef DEBUG
      std::cout << "Read keyword -" << keyword << "- successfully" << std::endl;
#endif
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
  std::cout << "Total number of elements = " << nelements << std::endl;

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
  //! Object id
  unsigned object_id = std::numeric_limits<unsigned>::max();

  // Opening nodes.txt file to print centroid coordinates
  std::ofstream nodestream;
  nodestream.open("nodes.txt", std::ofstream::out | std::ostream::trunc);

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
      nnodes = std::numeric_limits<unsigned>::max();
      auto search = mesh::map_element_type_nodes.find(element_type);
      if (search != mesh::map_element_type_nodes.end()) nnodes = search->second;

      if (nnodes != std::numeric_limits<unsigned>::max()) {
        for (unsigned nodes = 0; nodes < nnodes; ++nodes) {
          istream >> nid;
          element->add_vid(nid);
          std::shared_ptr<Vertex> vptr = this->vertex_ptr_at_id(nid);
          if (vptr) element->vertex_ptr(vptr);
        }
      }

      // Calculate centroid and print coordinates into nodes.txt
      if (element_type == 4) {
        element->compute_centroid();
        std::array<double, 3> centroid_ = element->centroid();
        nodestream << std::left << std::setw(10) << centroid_.at(0) << '\t'
                   << std::setw(10) << centroid_.at(1) << '\t' << std::setw(10)
                   << centroid_.at(2) << std::endl;
      }
      this->element_ptr(element);
    } else
      std::cerr << "Invalid entry for node: " << line << std::endl;
  }
  nodestream.close();
}

//! Read ids and types of surfaces
//! \param[in] file Input file stream object of msh file
void Mesh::read_surfaces(std::ifstream& file) {
  read_keyword(file, "$PhysicalNames");

  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  // Total number of surfaces
  unsigned nsurfaces;
  istream >> nsurfaces;
  std::cout << "Number of physical objects = " << nsurfaces << std::endl;

  //! Open up fracture.txt file
  std::ofstream fracstream;
  fracstream.open("fracture.txt", std::ofstream::out | std::ostream::trunc);

  //! Surface ID
  unsigned surface_id = std::numeric_limits<unsigned>::max();
  //! Surface type
  unsigned surface_type = std::numeric_limits<unsigned>::max();
  //! Surface (object) name
  std::string object_name;
  //! List of element ids associated with a fracture object
  std::vector<unsigned> element_list;
  //! List of vertex ids
  std::vector<unsigned> vertex_id_list;

  // Convert number of surfaces into string to initialize object_name
  std::ostringstream convert;
  convert << nsurfaces;
  object_name = convert.str();

  // Iterate through all surfaces in the mesh file
  for (unsigned i = 0; i < nsurfaces; ++i) {
    read_keyword(file, object_name);
    std::string line;
    std::getline(file, line);
    std::istringstream istream(line);

    if (line.find('#') == std::string::npos && line != "") {
      // Read surface type, ids, and names
      istream >> surface_type;
      istream >> surface_id;
      istream >> object_name;

      // Create a surface pointer
      auto surface = std::make_shared<Surface>(surface_id);

      // Find if its fracture surface or not
      auto find = this->find_fracture_surface(object_name);

      // Get fracture pairs using pointers
      if (find == true) {
        // Get list of element pointers for surface_id
        auto vec_elemtptr = this->find_element_id(surface_id);
        // Get list of vertex pointers for every element
        for (const auto& elemptr : vec_elemtptr) {
          auto vec_vertptr = elemptr->vec_vertex_ptr();
          auto eid = elemptr->id();
          // Get list of vertex ids (int) for every element
          vertex_id_list.clear();
          for (const auto& vtr : vec_vertptr) {
            auto vid = vtr->id();
            vertex_id_list.push_back(vid);
          }

          // Print fracture pairs
          this->frac_pairs(eid, vertex_id_list);
          auto fpair = this->return_frac_pair();
          fracstream << fpair.at(0) << " " << fpair.at(1) << std::endl;
        }
      }
      this->surface_ptr(surface);
    } else
      std::cerr << "Invalid entry for node: " << line << std::endl;
  }
  fracstream.close();
}

//! Find fracture pairs
void Mesh::frac_pairs(unsigned eid, std::vector<unsigned> vfraclist) {

  std::vector<unsigned> vlist, frac_pair;
  frac_pair.clear();
  unsigned final_node_id = 0;

  for (const auto& eptr : vec_element_ptr_) {
    auto element_id = eptr->id();
    auto element_type = eptr->type();

    if (element_id != eid && element_type == 4) {
      vlist.clear();
      auto vert_ptr = eptr->vec_vertex_ptr();
      for (const auto& vtr : vert_ptr) {
        auto vid = vtr->id();
        vlist.push_back(vid);
      }
      std::sort(vfraclist.begin(), vfraclist.end());
      std::sort(vlist.begin(), vlist.end());
      std::vector<unsigned> vintersect;
      std::set_intersection(vfraclist.begin(), vfraclist.end(), vlist.begin(),
                            vlist.end(), std::back_inserter(vintersect));
      if (vintersect.size() == 3) {
        frac_pair.push_back(final_node_id);
      }
      ++final_node_id;
    }
  }
  this->assign_frac_pair(frac_pair);
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

  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  // Total number of vertices
  unsigned nvertices;
  istream >> nvertices;
  std::cout << "Total number of vertices = " << nvertices << std::endl;

  // Vertex id and coordinates
  unsigned vid = std::numeric_limits<unsigned>::max();
  std::array<double, mesh::DIM> vcoordinates;

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
