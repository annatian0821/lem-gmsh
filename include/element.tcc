#include "element.h"

//! Compute the centroid of an element
void Element::compute_centroid() {

  centroid_ = {0.};

  // centoid calculated successfully
  for (const auto vertex_ptr : this->vec_vertex_ptr_) {
    auto coordinates = vertex_ptr->coord();
    std::transform(centroid_.begin(), centroid_.end(), coordinates.begin(),
                   centroid_.begin(), std::plus<double>());
  }

  for (auto& centroid : centroid_) centroid /= vec_vertex_ptr_.size();

#ifdef DEBUG
  std::cout << this->id() << " " << centroid_.at(0) << " " << centroid_.at(1)
            << " " << centroid_.at(2) << vec_vertex_ptr_.size() <<  std::endl;
#endif
}
