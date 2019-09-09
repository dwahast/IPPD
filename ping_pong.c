// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Ping pong example with MPI_Send and MPI_Recv. Two processes ping pong a
// number back and forth, incrementing it until it reaches a given value.
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  const int PING_PONG_LIMIT = 5;

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We are assuming at least 2 processes for this task
  if (world_size != 2) {
    fprintf(stderr, "World size must be two for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int ping_pong_count = 0;
  int partner_rank = (world_rank + 1) % 2;
  clock_t send_start, send_end, rec_start, rec_end, total;

  while (ping_pong_count < PING_PONG_LIMIT) {

    if (world_rank == ping_pong_count % 2) {

      double tbeg = MPI_Wtime();
      // Increment the ping pong count before you send it
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_SHORT, partner_rank, 0, MPI_COMM_WORLD);
      printf("%d sent and incremented ping_pong_count %d to %d\n",
             world_rank, ping_pong_count, partner_rank);
      /////
      double elapsedTime = MPI_Wtime() - tbeg;
      printf("%d Time for send %.2fus\n",world_rank ,elapsedTime*1000000);
    } else {

      double tbeg = MPI_Wtime();
      /////
      MPI_Recv(&ping_pong_count, 1, MPI_SHORT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("%d received ping_pong_count %d from %d\n",
             world_rank, ping_pong_count, partner_rank);
      /////
      double elapsedTime = MPI_Wtime() - tbeg;

      printf("%d Time for rec %.2fus\n",world_rank,elapsedTime*1000000);
    }
  }
  MPI_Finalize();
}
