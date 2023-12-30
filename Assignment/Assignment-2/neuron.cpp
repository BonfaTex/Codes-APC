//
// Created by Danilo Ardagna on 01/11/23.
//

#include "neuron.h"

neuron::neuron(size_t input_size, const ptr_act_function & p_a_f) {
    p_act_func = p_a_f;
    bias = 0;
    weights = la::dense_matrix(input_size,1, 1.0);
}

double neuron::eval(const la::dense_matrix & input_vect) const{

    la::dense_matrix weights_T = weights.transposed();

    la::dense_matrix sum_wi_xi = weights_T*input_vect;

    return p_act_func->eval(*sum_wi_xi.data()+bias);
}
