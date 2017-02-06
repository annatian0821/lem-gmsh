#include "mesh.h"

//! Assign element pointer to a given index
//! \param[in] index Index of the element
//! \param[in] element Element pointer
bool Mesh::element_ptr(unsigned index, std::shared_ptr<Element>& elementptr) {
  if (elementptr) {
    elements_.at(index) = elementptr;
    return true;
  } else
    return false;
}

//! Check if msh file exists
//! \param[in] filename Mesh file name
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
  file.close();
}

//! Read keywords
void Mesh::read_keyword(std::ifstream& file, const std::string& keyword) {

  std::string line;
  file.clear();
  file.seekg(0, std::ios::beg);
  while (std::getline(file, line)) {
    if (line != keyword) {
      if (line.find(keyword) != std::string::npos) {
        std::cerr << "Cannot find keyword: " << keyword << '\n';
        std::cerr << "Line read -" << line << '-' << '\n';
        break;
      };
    } else {
#ifdef DEBUG
      std::cout << "Read keyword -" << keyword << "- successfully\n";
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
        std::array<double, 3> centroid = element->centroid();
        centroids_.push_back(centroid);
      }

      this->element_ptr(element);
    } else
      std::cerr << "Invalid entry for node: " << line << '\n';
  }
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
  std::cout << "Number of physical objects = " << nsurfaces << '\n';

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
      // Get fracture pairs using pointers
      if (this->find_fracture_surface(object_name)) {
        // Get list of element pointers for surface_id
        auto elements = this->find_element_id(surface_id);
        // Get list of vertex pointers for every element
        for (auto& element : elements) {
          const auto element_id = element->id();
          auto vertex_id_list = element->vec_vertex_ids();
          // Find fracture pairs
          this->frac_pairs(element_id, vertex_id_list, element);
        }
      }
      this->surface_ptr(surface);
    } else
      std::cerr << "Invalid entry for node: " << line << '\n';
  }
}

//! Find fracture pairs
void Mesh::frac_pairs(unsigned eid, std::vector<unsigned>& vfraclist,
                      std::shared_ptr<Element>& felement) {

  std::pair<unsigned, unsigned> fracture_pairs_;
  fracture_pairs_ = std::make_pair(-1, -1);
  unsigned final_node_id = 0;

  std::sort(vfraclist.begin(), vfraclist.end());

  for (const auto& element : elements_) {
    const auto element_id = element->id();
    const auto element_type = element->type();

    if (element_id != eid && element_type == 4) {
      auto fcentroid = felement->centroid();
      auto centroid = element->centroid();
      auto vlist = element->vec_vertex_ids();
      std::sort(vlist.begin(), vlist.end());
      std::vector<unsigned> vintersect;
      std::set_intersection(vfraclist.begin(), vfraclist.end(), vlist.begin(),
                            vlist.end(), std::back_inserter(vintersect));
      if (vintersect.size() == 3) {
        // auto x = (fcentroid.at(0) + centroid.at(0)) / 2.;
        // auto y = (fcentroid.at(1) + centroid.at(1)) / 2.;
        // auto z = (fcentroid.at(2) + centroid.at(2)) / 2.;

        // if (fcentroid.at(2) > centroid.at(2)) {
        //   felement->centroid({x, y, z + 0.05});
        //   element->centroid({x, y, z - 0.05});
        // } else {
        //   felement->centroid({x, y, z - 0.05});
        //   element->centroid({x, y, z + 0.05});
        // }

        if (fracture_pairs_.first == -1)
          fracture_pairs_.first = final_node_id;
        else
          fracture_pairs_.second = final_node_id;
      }
      ++final_node_id;
    }
  }
  this->add_frac_pair(fracture_pairs_);
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
  std::cout << "Total number of vertices = " << nvertices << '\n';

  // Vertex id and coordinates
  unsigned vid = std::numeric_limits<unsigned>::max();
  std::array<double, mesh::dim> vcoordinates;

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
      for (auto& vcoordinate : vcoordinates) istream >> vcoordinate;

      // Create a new vertex and add to list
      auto vertex = std::make_shared<Vertex>(vid, vcoordinates);
      this->vertex_ptr(vertex);

      // Increament number of vertex on successful read
      ++i;
    } else
      std::cerr << "Invalid entry for node: " << line << '\n';
  }
}

void Mesh::align_fractures() {
  for (const auto& fracture_pair : fracture_pairs_) {
    auto centroid1 = centroids_.at(fracture_pair.first);
    auto centroid2 = centroids_.at(fracture_pair.second);

    const auto x = (centroid1.at(0) + centroid2.at(0)) / 2.;
    const auto y = (centroid1.at(1) + centroid2.at(1)) / 2.;
    auto z = (centroid1.at(2) + centroid2.at(2)) / 2.;
    double diff = 0.01;
    if (centroid1.at(2) > centroid2.at(2)) {
      centroids_.at(fracture_pair.first) = {x, y, z + diff};
      centroids_.at(fracture_pair.second) = {x, y, z - diff};
    } else {
      centroids_.at(fracture_pair.first) = {x, y, z - diff};
      centroids_.at(fracture_pair.second) = {x, y, z + diff};
    }

  }
}
//! Print nodes in txt file
void Mesh::write_nodes() {
  std::ofstream nodestream;
  nodestream.open("nodes.txt", std::ofstream::out);
 for (const auto& centroid : centroids_) {
   nodestream << std::left << std::setw(10) << centroid.at(0) << '\t'
              << std::setw(10) << centroid.at(1) << '\t' << std::setw(10)
              << centroid.at(2) << '\n';
  }
  nodestream.close();
}

//! Print fracture pairs in txt file
void Mesh::write_fractures() {
  std::ofstream fracstream;
  fracstream.open("fracture.txt", std::ofstream::out | std::ostream::trunc);
  for (const auto& fracture_pair : fracture_pairs_)
    fracstream << fracture_pair.first << " " << fracture_pair.second << '\n';

  fracstream.close();
}
