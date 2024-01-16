#include "matrix_assemble.hpp"

namespace la {

dense_matrix assemble_cols(const dense_matrix& local_A)
{
    /* allgather by row, then change the row with a pointer */

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned nrows = local_A.rows();
    unsigned ncols = local_A.columns();

    dense_matrix global_result(nrows, ncols*size);
    double* p = global_result.data();

    dense_matrix R(1, ncols);

    for (unsigned i=0; i<nrows; ++i)
    {
        for(unsigned j=0; j<ncols; j++)
        {
            R(0,j)=local_A(i,j);
        }

        MPI_Allgather(R.data(), ncols, MPI_DOUBLE, 
            p, ncols, MPI_DOUBLE, MPI_COMM_WORLD); 

        p+=ncols*size;
    }

    return global_result;
}

dense_matrix assemble_cols2(const dense_matrix& local_A)
{
    /* allgather with the transposed */

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned nrows = local_A.rows();
    unsigned ncols = local_A.columns();

    dense_matrix global_result(ncols*size, nrows);

    dense_matrix local_A_tr(ncols, nrows);

    local_A_tr = local_A.transposed();

    MPI_Allgather(local_A_tr.data(), ncols*nrows, MPI_DOUBLE, 
        global_result.data(), ncols*nrows, MPI_DOUBLE, MPI_COMM_WORLD); 

    return global_result.transposed();
}

};