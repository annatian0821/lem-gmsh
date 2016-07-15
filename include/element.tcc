#include "element.h"

//! Calculate the centroid of an element
void Element::calculate_centroid(
    const unsigned elementid, std::array<double, 4> vert_list,
    std::vector<std::shared_ptr<Vertex>> vertex_list_ptr,
    const unsigned list_size) {

#ifdef DEBUG
  for (unsigned j = 0; j < list_size; ++j) std::cout << vert_list.at(j) << " ";
  std::cout << std::endl;
#endif

#ifdef DEBUG
  for (unsigned i = 0; i < list_size; ++i) {
    auto coordinates = vertex_list_ptr.at(vert_list.at(i) - 1)->coord();
    std::cout << elementid << " " << vert_list.at(i) << " " << list_size << " ";
    for (unsigned j = 0; j < coordinates.size(); ++j) {
      std::cout << coordinates.at(j) << " ";
    }
    std::cout << std::endl;
  }
#endif

  std::array<double, 3> centroid = {0.};

  // centoid calculated successfully
  for (unsigned i = 0; i < list_size; ++i) {
    auto coordinates = vertex_list_ptr.at(vert_list.at(i) - 1)->coord();
    centroid.at(0) += coordinates.at(0);
    centroid.at(1) += coordinates.at(1);
    centroid.at(2) += coordinates.at(2);
  }
  centroid.at(0) /= list_size;
  centroid.at(1) /= list_size;
  centroid.at(2) /= list_size;

  // Push centroid back to element
  this->add_centroid(centroid);

#ifdef DEBUG
  std::cout << elementid << " " << centroid.at(0) << " " << centroid.at(1)
            << " " << centroid.at(2) << std::endl;
#endif
}
