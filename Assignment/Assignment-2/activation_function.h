//
// Created by Danilo Ardagna on 01/11/23.
//

#ifndef NEURALNETWORKS_ACTIVATION_FUNCTION_H
#define NEURALNETWORKS_ACTIVATION_FUNCTION_H
#include <cmath>

class activation_function {
public:
    virtual double eval(double) const = 0;
    virtual ~activation_function() = default;
};

#endif //NEURALNETWORKS_ACTIVATION_FUNCTION_H
