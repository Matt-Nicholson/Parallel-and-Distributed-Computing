#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main( int argc, char argv[])
{
    int n, myid, numprocs, i;
    double start = 0.0, end, newpi, pi, a, b, total;


    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Init(&argc,&argv);


    n = 0;
    if (myid == 0)

    {
        if (n==0) n=1024*numprocs; else n=0;
        start = MPI_Wtime();
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n == 0)

   {

    }
    else

    {
        a   = 1.0 / (double) n;
        total = 0.0;
        b =  a* 0.5;
        for (i = myid + 1; i <= n; i += numprocs){
            b += a;
            total += (double)(4.0 / (1.0 + b*b));
        }
        newpi = a * total;
        MPI_Reduce(&newpi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        if (myid == 0)

       {
            printf("Pi is approximately %.20f\n",pi);
            end = MPI_Wtime();
            printf("Time = %f\n", end - start);
        }
    }
    MPI_Finalize();
    return 0;
}