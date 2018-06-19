#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const size_t NUM_WORKERS = 99;
size_t NUM_ATTEMPTS;
size_t SHARED = 0;

int client(void);
int server(void);

int main(int argc, char ** argv) {
    char *ptr = NULL;
    if(argc != 2) NUM_ATTEMPTS = 10000;
    else NUM_ATTEMPTS = strtoul(argv[1], &ptr, 10);

    printf("The expected result of SHARED is: %d\n", NUM_WORKERS * NUM_ATTEMPTS);

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) server();
    else client();

    return 0;
}

/*
    The server holds an int, and listens for read/write
    requests from clients. 
*/
int server(void) {
     for(int i = 0; i < NUM_WORKERS * NUM_ATTEMPTS * 2; i++) {
        // Wait for a client to send a request, then switch on the tag
        size_t result;
        MPI_Status status;
        MPI_Recv(&result, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    
        switch(status.MPI_TAG) {
            case 0: 
                // Read - so asynchronously send SHARED to the client
                MPI_Request request;
                MPI_Isend(&SHARED, 1, MPI_UNSIGNED, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &request); 
            case 1:
                // Write - so write result to SHARED 
                SHARED = result;
        }
    }
  
    printf("The final count was %d\n", SHARED);
    return 0;
}

/*
   The client asynchronously reads and writes to the int
   stored in the server. 
*/ 
int client(void) {
    for(int i = 0; i < NUM_ATTEMPTS; i++) {
        size_t CLIENT_NUM = 0;

        // Send a read request to the server
        MPI_Ssend(&CLIENT_NUM, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
       
        // Now read the response 
        MPI_Status status; 
        MPI_Recv(&CLIENT_NUM, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, &status);

        // Increment CLIENT_NUM and write the value to the server
        CLIENT_NUM++;
        MPI_Ssend(&CLIENT_NUM, 1, MPI_UNSIGNED, 0, 1, MPI_COMM_WORLD); 
    }

    return 0;
}
