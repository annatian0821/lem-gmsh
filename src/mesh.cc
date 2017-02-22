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
  if (!file.is_open())
    throw std::runtime_error("Specified GMSH file does not exist");
  if (file.good()) {
    read_vertices(file);
    read_elements(file);
    read_surfaces(file);
  }
  file.close();
}

//! Read keywords
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
      const auto frac_key = "Fracture";
      if (this->find_surface(object_name, frac_key)) {
        // Get list of element pointers for surface_id
        auto elements = this->find_element_id(surface_id);
        // Get list of vertex pointers for every element
        for (const auto& element : elements) {
          const auto element_id = element->id();
          auto vertex_id_list = element->vec_vertex_ids();
          // Find fracture pairs
          fracture_pairs_.emplace_back(
              this->node_pairs(element_id, vertex_id_list));
        }
      }

      // Find if its weak plane surface or not
      // Get weak plane node pairs using pointers
      const auto key = "WeakPlane";
      if (this->find_surface(object_name, key)) {
        // Get list of element pointers for surface_id
        auto elements = this->find_element_id(surface_id);
        std::cout << "Elements: "<< elements.size() << '\n';
        // Get list of vertex pointers for every element
        for (const auto& element : elements) {
          const auto element_id = element->id();
          auto vertex_id_list = element->vec_vertex_ids();
          // Find fracture pairs
          weakplane_node_pairs_.emplace_back(
              this->node_pairs(element_id, vertex_id_list));
        }
      }

      this->surface_ptr(surface);
    } else
      std::cerr << "Invalid entry for node: " << line << '\n';
  }
}

//! Find fracture pairs
std::pair<unsigned, unsigned> Mesh::node_pairs(
    unsigned eid, std::vector<unsigned>& vertices) {

  std::pair<unsigned, unsigned> node_pairs = std::make_pair(-1, -1);
  unsigned final_node_id = 0;

  std::sort(vertices.begin(), vertices.end());

  for (const auto& element : elements_) {
    const auto element_id = element->id();
    const auto element_type = element->type();

    if (element_id != eid && element_type == 4) {
      auto vlist = element->vec_vertex_ids();
      std::sort(vlist.begin(), vlist.end());
      std::vector<unsigned> vintersect;
      std::set_intersection(vertices.begin(), vertices.end(), vlist.begin(),
                            vlist.end(), std::back_inserter(vintersect));
      if (vintersect.size() == 3) {
        if (node_pairs.first == -1)
          node_pairs.first = final_node_id;
        else
          node_pairs.second = final_node_id;
      }
      ++final_node_id;
    }
  }
  return node_pairs;
  //  this->add_frac_pair(fracture_pairs_);
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

bool Mesh::align_nodes_on_plane(const std::string& plane, unsigned dir) {

  try {
    std::vector<std::pair<unsigned, unsigned>> node_pairs;
    // Use weak plane or fracture plane
    if (plane == "Fracture")
      node_pairs = fracture_pairs_;
    else if (plane == "WeakPlane")
      node_pairs = weakplane_node_pairs_;
    else
      throw std::runtime_error("Specified plane doesn't exist!");

    double max = 0.;
    double sum = 0.;
    double min = std::numeric_limits<double>::max();
    unsigned size = 0;
    unsigned id = 0;
    // Iterate through all fractures to determine the average, min and max
    // coordinates of fractures
    for (const auto& node_pair : node_pairs) {
      if (node_pair.first != std::numeric_limits<unsigned>::max()) {
        auto centroid1 = volume_elements_.at(node_pair.first)->centroid();
        auto centroid2 = volume_elements_.at(node_pair.second)->centroid();

        if (centroid1.at(dir) > max) max = centroid1.at(dir);
        if (centroid1.at(dir) < min) max = centroid1.at(dir);
        if (centroid2.at(dir) > max) max = centroid2.at(dir);
        if (centroid2.at(dir) < min) min = centroid2.at(dir);

        // Average location of coordinates
        sum += centroid1.at(dir) + centroid2.at(dir);
        size += 2;

        ++id;
      }
    }
    // Evaluate the maximum difference between 2 nodes on either side of the
    // plane
    // Taking 80% of maximum length to reduce the length of nodes on either
    // side.
    const double diff = 0.8 * std::fabs(max - min) / 2.;
    // Average location of the fracture plane
    const double average = sum / size;
    for (const auto& node_pair : node_pairs) {
      if (node_pair.first != std::numeric_limits<unsigned>::max()) {
        auto centroid1 = volume_elements_.at(node_pair.first)->centroid();
        auto centroid2 = volume_elements_.at(node_pair.second)->centroid();

        std::array<double, 3> centroid_min{0.};
        std::array<double, 3> centroid_max{0.};

        for (unsigned i = 0; i < centroid1.size(); ++i) {
          centroid_min.at(i) = (centroid1.at(i) + centroid2.at(i)) / 2.;
          centroid_max.at(i) = (centroid1.at(i) + centroid2.at(i)) / 2.;
        }
        centroid_min.at(dir) = average - diff;
        centroid_max.at(dir) = average + diff;

        // Align fracture to the plane
        if (centroid1.at(dir) > centroid2.at(dir)) {
          volume_elements_.at(node_pair.first)->centroid(centroid_max);
          volume_elements_.at(node_pair.second)->centroid(centroid_min);
        } else {
          volume_elements_.at(node_pair.first)->centroid(centroid_min);
          volume_elements_.at(node_pair.second)->centroid(centroid_max);
        }
      }
    }
    std::cout << "Node pair #: " << id << '\n';
    return true;
  } catch (std::exception& runtime_exception) {
    std::cout << "Caught exception: " << runtime_exception.what() << '\n';
  }
}

//! Print nodes in txt file
void Mesh::write_nodes() {
  std::ofstream nodestream;
  nodestream.open("nodes.txt", std::ofstream::out);
 for (const auto& volume_element : volume_elements_) {
   const auto centroid = volume_element.second->centroid();
   nodestream << std::left << std::setw(10) << centroid.at(0) << '\t'
              << std::setw(10) << centroid.at(1) << '\t' << std::setw(10)
              << centroid.at(2) << '\n';
  }
  nodestream.close();
}

//! Print fracture pairs in txt file
void Mesh::write_fracture_pairs() {
  std::ofstream fracstream;
  fracstream.open("fracture.txt", std::ofstream::out | std::ostream::trunc);
  for (const auto& fracture_pair : fracture_pairs_)
    fracstream << fracture_pair.first << " " << fracture_pair.second << '\n';

  fracstream.close();
}
