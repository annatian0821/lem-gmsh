#include "element.h"

//! Compute the centroid of an element
void Element::compute_centroid() {

  centroid_ = {0.};

  // centoid calculated successfully
  for (const auto& vertex : this->vertices_) {
    auto coordinates = vertex->coord();
    std::transform(centroid_.begin(), centroid_.end(), coordinates.begin(),
                   centroid_.begin(), std::plus<double>());
  }

  for (auto& centroid : centroid_) centroid /= vertices_.size();
}
