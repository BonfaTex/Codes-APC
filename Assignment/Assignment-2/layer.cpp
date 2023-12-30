//
// Created by Danilo Ardagna on 01/11/23.
//

#include "layer.h"

layer::layer(size_t input_size, size_t output_size, const ptr_act_function &p_a_f) {
    layer::input_size = input_size;
    layer::output_size = output_size;

    for (size_t i=0; i<output_size; ++i) {
        neuron ne(input_size, p_a_f);
        neurons.push_back(ne);
    }
}

la::dense_matrix layer::eval(const la::dense_matrix & input_vector) const{
    using size_type = la::dense_matrix::size_type;

    la::dense_matrix result(output_size, input_vector.columns());

    for (size_type i = 0; i < result.rows(); ++i) {
        result(i,0) = neurons.at(i).eval(input_vector);
    }

    return result;
}

size_t layer::get_input_size() const {
    return input_size;
}

size_t layer::get_output_size() const {
    return output_size;
}
