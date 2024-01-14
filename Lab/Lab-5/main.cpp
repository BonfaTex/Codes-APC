#include <fstream>
#include <iostream>

#include <mpi.h>

#include "dense_matrix.hpp"
#include "power_method.hpp"

DenseMatrix read_matrix(const std::string & file_name);

int
main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  int rank (0), size (0);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  DenseMatrix local_A;

  local_A = read_matrix(argv[1]);
  std::size_t iterations = 20;
  DenseMatrix eigen_vector = power_method(local_A, iterations);

  if (rank == 0)
      print(eigen_vector);

  MPI_Finalize ();
  return 0;
}

DenseMatrix
read_matrix(const std::string & file_name)
{
  int rank (0), size (0);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  unsigned n(0); unsigned m(0);

  DenseMatrix full_A;

  // rank 0 legge la matrice iniziale A
  if (rank == 0)
   {
    std::ifstream f_stream (file_name);
    full_A.read (f_stream);
    n = full_A.get_n_rows ();
    m = full_A.get_n_cols ();
   }

  MPI_Bcast (&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  MPI_Bcast (&m, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  const unsigned local_n = n / size; // ogni core prende in carico local_n righe di A

  DenseMatrix local_A(local_n, m); // la matrice locale local_A è una (local_n)x(m)

  MPI_Scatter (
    full_A.data (), local_n * m, MPI_DOUBLE,
    local_A.data (), local_n * m, MPI_DOUBLE,
    0, MPI_COMM_WORLD);

  return local_A;
}
