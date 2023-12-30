#include "power_method.hpp"

DenseMatrix power_method(const DenseMatrix & local_A, std::size_t iterations)
{
    const std::size_t n_rows = local_A.get_n_rows();
    const std::size_t n_cols = local_A.get_n_cols();

    DenseMatrix x0(n_cols, 1, 1.0); // vettore colonna di uni

    for (std::size_t i=0; i<iterations; ++i)
    {
        DenseMatrix x1 = local_A * x0; // (n_rows,n_cols) x (n_cols,1) = (n_rows,1)

        // mettendo insieme tutti i vettori colonna x1, formo il vettore colonna x0 per la prossima iterazione
        MPI_Allgather(x1.data(), n_rows, MPI_DOUBLE, x0.data(), n_rows, MPI_DOUBLE, MPI_COMM_WORLD);
    }

    return x0;
}

DenseMatrix power_method2(const DenseMatrix & local_A, std::size_t iterations)
{
  const unsigned n = local_A.get_n_cols ();

  const unsigned stripe = local_A.get_n_rows ();

  DenseMatrix full_eigen_vector(n, 1, 1.0);

  for (std::size_t it_n = 0; it_n < iterations; ++it_n)
  {

    DenseMatrix local_X = local_A * full_eigen_vector;

    MPI_Allgather (local_X.data (), stripe , MPI_DOUBLE,
              full_eigen_vector.data (), stripe , MPI_DOUBLE,
              MPI_COMM_WORLD);
  }

  return full_eigen_vector;
}