#include "matrix_diff.hpp"

namespace la {

dense_matrix vertical_diff(const dense_matrix& A)
{
    unsigned nrows = A.rows();
    unsigned ncols = A.columns();

    dense_matrix local_result(nrows-1, ncols);

    for (unsigned j=0; j<ncols; ++j) // cols index
    {
        for (unsigned i=1; i<nrows; ++i) // rows index
        {
            local_result(i-1,j) = A(i,j)-A(i-1,j);
        }
    }

    return local_result;
}

};
