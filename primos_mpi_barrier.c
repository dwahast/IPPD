#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void main(){
	
	int comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int until = 100000;
	int chunk_size = until / comm_sz;
	int *v = malloc(until * sizeof(int));
	int *sub_vet_primos = malloc(chunk_size * sizeof(int));

	for(int i = 0; i < until; i++){
		v[i] = i;
	}

	if(my_rank == 0){
		printf("Numero de Pro: %d\n", comm_sz);
		printf("Verificar até: %d\n", until);
		printf("Chunk    size: %d\n",chunk_size);
	}

	MPI_Scatter(v, chunk_size, MPI_INT, sub_vet_primos, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

	//MPI_Barrier(MPI_COMM_WORLD);

	for(int i = 0; i < chunk_size; i++){
		//printf("P:%d[%d]:%d\n",my_rank,i,sub_vet_primos[i]);
	}

	for(int n = 0; n < chunk_size; n++){
		int is_primo = 0;

		for(int i = 0; i <= sub_vet_primos[n]; i++){
			if(i == 0){continue;}
			if(sub_vet_primos[n] % i == 0){
				is_primo += 1;
			}
		}

		if(is_primo <= 2){
			//printf("[%d]: %d É Primo\n",my_rank,sub_vet_primos[n]);
		}
		else{
			sub_vet_primos[n] = -1;
		}
	}

	MPI_Gather(sub_vet_primos, chunk_size, MPI_INT, v, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
	
	
	if(my_rank == 0){
		for(int i = 0; i < until; i++){
			printf("%d\n", v[i]);
		}
	}
	MPI_Finalize();
}