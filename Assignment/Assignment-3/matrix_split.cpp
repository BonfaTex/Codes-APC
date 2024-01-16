#include "matrix_split.hpp"

namespace la {

dense_matrix split_cols(const dense_matrix& A)
{
    /* send e recv */

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned nrows = A.rows();
    unsigned ncols = A.columns();

    MPI_Bcast(&nrows, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ncols, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    unsigned n_local_cols = ncols / size;

    // result is a (nrows, ncols/size) dense_matrix
    dense_matrix local_split(nrows, n_local_cols);

    if (rank == 0)
    {
        for (int r = size-1; r >= 0; --r)
        {
            // backward cycle, in this way I already have the correct local matrix also for rank 0
            for (unsigned i=0; i<nrows; ++i)
            {
                for (unsigned j = 0; j < n_local_cols; ++j)
                {
                    local_split(i, j) = A(i, j + n_local_cols * r);
                }
            }
            if (r>0) // rank 0 doesn't need to receive
            {
                MPI_Send(local_split.data(), nrows * n_local_cols, MPI_DOUBLE, 
                    r, 0, MPI_COMM_WORLD);
            }
        }
    }
    else
    {
        MPI_Recv(local_split.data(), nrows * n_local_cols, MPI_DOUBLE,
                 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    return local_split;
}

dense_matrix split_cols2(const dense_matrix& A)
{
    /* scatter with the transposed matrix */

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned nrows = A.rows();
    unsigned ncols = A.columns();

    MPI_Bcast(&nrows, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ncols, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    unsigned n_local_cols = ncols / size;

    dense_matrix local_split(n_local_cols, nrows);

    MPI_Scatter (A.transposed().data(), n_local_cols*nrows, MPI_DOUBLE, 
        local_split.data(), n_local_cols*nrows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    return local_split.transposed();
}

dense_matrix split_cols3(const dense_matrix& A)
{
    /* broadcast of full A */

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned nrows = A.rows();
    unsigned ncols = A.columns();

    MPI_Bcast(&nrows, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ncols, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    unsigned n_local_cols = ncols / size;

    dense_matrix local_A(nrows, ncols);

    if (rank == 0) {
        for (unsigned i=0; i<nrows; ++i) {
            for (unsigned j=0; j<ncols; ++j) {
                local_A(i,j)=A(i,j);
            }
        }
    }

    MPI_Bcast(local_A.data(), nrows*ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    dense_matrix local_split(nrows,n_local_cols);

    for (unsigned i=0; i<nrows; ++i)
    {
        for (unsigned j=0; j<n_local_cols; ++j)
        {
            local_split(i,j) = local_A(i,j + n_local_cols * rank);
        }
    }

    return local_split;
}

};