#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define ROOT 0
#define MSG_TAG 100

int main(int argc, char **argv)
{
	int tid,size;
	MPI_Status status;
	int provided;
	int i;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided); //Musi być w każdym programie na początku

//	printf("Checking!\n");
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &tid );
//	printf("My id is %d from %d\n",tid, size);

	int msg[2];

	if ( tid == ROOT)
	{
		i=0;
		MPI_Send( &i, 1, MPI_INT, tid+1, MSG_TAG, MPI_COMM_WORLD );
		printf("#%d Wyslalem %d do %d od %d\n", tid, i, (tid+1)%size, status.MPI_SOURCE);
		MPI_Recv(&i, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("#%d Otrzymalem %d od %d\n", tid, i, status.MPI_SOURCE);
	}
	else
	{
		MPI_Recv(&i, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("#%d Otrzymalem %d od %d\n", tid, i, status.MPI_SOURCE);
		i=i+1;
		MPI_Send( &i, 1, MPI_INT, (tid+1)%size, MSG_TAG, MPI_COMM_WORLD );
                printf("#%d Wyslalem %d do %d od %d\n", tid, i, (tid+1)%size, status.MPI_SOURCE);
		//msg[0] = tid;
		//msg[1] = size;
		//MPI_Send( msg, 2, MPI_INT, ROOT, MSG_TAG, MPI_COMM_WORLD );
		//printf(" Wyslalem %d %d do %d\n", msg[0], msg[1], ROOT );
	}

	MPI_Finalize(); // Musi być w każdym programie na końcu
}
