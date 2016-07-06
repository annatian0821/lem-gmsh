#include "mesh.h"

//! Check if msh file exists 
void Mesh::read_msh_file(const std::string& filename) {

  std::ifstream file; 
  file.open(filename.c_str(), std::ios::in); 
  if (!file.is_open()) { 
    std::cerr << "Msh file does not exist \n"; 
    std::exit(EXIT_FAILURE);  
  } 
  if (file.good()){ 
    read_msh_element(filename);  
    read_msh_vertex(filename);
  } 
} 

//! Read keywords
void Mesh::readKeyword(std::ifstream *file, std::string keyword) { 
  
  std::string line;
  std::getline(*file, line);
  if (line != keyword) {
    std::cout << "Cannot find keyword: " << keyword << std::endl;
    std::cout << "Line read -" << line << '-' << std::endl; 
  } else {
    std::cout << "Read keyword -" << keyword << "- successfully" << std::endl;
  }
} 

//! Read element ids & vertex list 
void Mesh::read_msh_element(const std::string& filename) { 

  std::ifstream file;  
  readKeyword(&file, "$Elements"); 
  unsigned element_no; 
  file >> element_no; 
  std::cout << "Number of elements = " << element_no << std::endl; 
  unsigned elementid;
  unsigned temp;  
  std::string line;
  std::array<double, 4> vert_list;  
   while (std::getline(file, line)) {
    std::istringstream istream(line);
    // to ignore comment line with #
    if(line.find('#') == std::string::npos) {
      if (line != "") {
        for (unsigned i = 0; i < 8; ++i) {
         // Read vertices associated with the element 
         if (i<=4){
           istream >> temp; 
         } else { 
           istream >> vert_list.at(i-5);
         } 
         }
        }
      }
     // Create a new element and push it to mesh 
     auto element = std::make_shared<Element>(elementid);
     ++elementid;
     this->element_ptr(element);
  }
}   

//! Read vertex ids and coordinates 
void Mesh::read_msh_vertex(const std::string& filename) {
  
  std::ifstream file; 
  readKeyword(&file, "$Nodes"); 
  unsigned vert_no;
  file >> vert_no;
  std::cout << "Number of vertices = " << vert_no << std::endl;
  unsigned vid = 0;
  unsigned temp; 
  std::string line; 
  std::array<double, 3> vcoord; 
  while (std::getline(file, line)) { 
    std::istringstream istream(line);
    // to ignore comment line with #
    if(line.find('#') == std::string::npos) {
      if (line != "") {
       for (unsigned i = 0; i < 4; ++i) { 
         // Read coordinates
         if (i==0){
           istream >> temp; 
         } else { 
           istream >> vcoord.at(i-1); 
         } 
       } 
      } 
      // Create a new vertex and push it to mesh 
      auto vertex = std::make_shared<Vertex>(vid, vcoord); 
      ++vid; 
      this->vertex_ptr(vertex);
    } 
 } 
}


