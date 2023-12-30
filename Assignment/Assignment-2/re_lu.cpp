//
// Created by Danilo Ardagna on 01/11/23.
//

#include "re_lu.h"


double re_lu::eval(double x) const {
    if (x>0)
        return x;
    else
        return 0;
}