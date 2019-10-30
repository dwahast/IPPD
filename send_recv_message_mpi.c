#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void main(){
	int my_rank;
	int world_size;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	char s[4] = "Ola!";
	int len_msg = strlen(s);
	printf("tamanho da msg: %d\n",len_msg);		
		
	if(my_rank == 0){
		printf("World_size:%d\n",world_size);
		printf("\n ------------------------------- \n");
		
		printf("Eu (%d) Enviei: '%s'\n",my_rank, s);
		
		MPI_Send(&s, len_msg, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
	
	}else{
		
		MPI_Recv(&s, len_msg, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Eu (%d) recebi: %s\n",my_rank, s);
	}
	MPI_Finalize();	
}