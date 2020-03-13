#include "mpi.h"
#include "stdio.h"

#define MAX_MESSAGE_BUFFER_SIZE 21

int main(int argc, char* argv[]) {
	const int TAG = 1;
	MPI_Init(&argc, &argv);
	int process_count;
	int process_rank;
	//MPI_COMM_WORLD - за этим именем пр€четс€ коммуникатор ктр объедин€ет все процессы запущенные в рамках данной программы
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	
	char messageRecv[MAX_MESSAGE_BUFFER_SIZE] = "";
	if (process_rank > 0) {
		MPI_Status status;

		MPI_Recv(messageRecv, MAX_MESSAGE_BUFFER_SIZE, MPI_CHAR, process_rank - 1, TAG, MPI_COMM_WORLD, &status);
		printf("Message in process %d from process %d: %s\n", process_rank, status.MPI_SOURCE, messageRecv);

		MPI_Send(messageRecv, strlen(messageRecv), MPI_CHAR, (process_rank == (process_count - 1)) ? 0 : process_rank + 1,TAG, MPI_COMM_WORLD);
	}
	else {
		MPI_Status status;
		char message[MAX_MESSAGE_BUFFER_SIZE] = "hello from process 0";
		MPI_Send(message, strlen(message), MPI_CHAR, process_rank + 1, TAG, MPI_COMM_WORLD);
		
		MPI_Recv(messageRecv, MAX_MESSAGE_BUFFER_SIZE, MPI_CHAR, process_count - 1, TAG, MPI_COMM_WORLD, &status);

		printf("Message in process %d from process %d: %s\n", process_rank, status.MPI_SOURCE, messageRecv);
	}
	MPI_Finalize();
}


