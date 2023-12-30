//
// Created by Danilo Ardagna on 01/11/23.
//

#include "nn_model.h"

la::dense_matrix nn_model::predict(const la::dense_matrix &input_vector) const {

    std::vector<la::dense_matrix> result;
    result.push_back(input_vector);

    for (size_t k = 0; k<layers.size(); ++k) {
        result.push_back( layers.at(k).eval(result.at(k)) );
    }

    return result.at(layers.size());
}

void nn_model::add_layer(const layer & l) {

    layers.push_back(l);

}
