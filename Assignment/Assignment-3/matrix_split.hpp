#include <string>
#include <mpi.h>

#include "dense_matrix.hpp"

namespace la {

dense_matrix split_cols(const dense_matrix& A);
dense_matrix split_cols2(const dense_matrix& A);
dense_matrix split_cols3(const dense_matrix& A);
};
