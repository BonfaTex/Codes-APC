//
// Created by Danilo Ardagna on 01/11/23.
//

#include "sigmoid.h"

double sigmoid::eval(double x) const {
    return 1.0 / ( 1.0 + exp(-x) );
}