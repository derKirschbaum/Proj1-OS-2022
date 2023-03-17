#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>


#define MAX_WRITER 10
#define MAX_READER 10
#define MAX_INTEGER 100000

pthread_mutex_t mutex;


int main(int argc, char* argv[]){

    // Check input arguments
    // argc = # number of argument
    // argv = array of argument
    // !! default value of argc is 1, therefore we need to check for 7 args
    // !! default value of argv[0] is the name of program, custom args starts from argv[1]
    // !! argv = [ programName, # writer, # reader, input, output, seed, N]; # of args = 7
    if (argc != 7 )
    {
        //Print to stderr (Standard Error)
        fprintf(stderr,
        "Invalid arguments\n\nUsage: ./multithread <# of writers> <# of readers> <input> <output> <seed> <N>");
        exit(-1);
    }
    if(atoi(argv[1]) < 1 || MAX_WRITER < atoi(argv[1])){
        fprintf(stderr,
        "Invalid arguments\n# of writers must be from 1 - %d",MAX_WRITER);
        exit(-1);
    }
    if(atoi(argv[2]) < 1 || MAX_READER < atoi(argv[2])){
        fprintf(stderr,
        "Invalid arguments\n# of readers must be from 1 - %d",MAX_READER);
        exit(-1);
    }
    if(fopen(argv[3],"r")==NULL){
        fprintf(stderr,
        "Unable to open file");
        exit(-1);
    }
    //-----------------------------------------------
    if(atoi(argv[6]) < 1 || MAX_INTEGER < atoi(argv[6])){
        fprintf(stderr,
        "Invalid arguments\nAmount of integers must be from 1 - %d",MAX_INTEGER);
        exit(-1);
    }

    int num_writers =atoi(argv[1]);
    int num_readers =atoi(argv[2]);
    FILE *fp = fopen(argv[3],"r");
    int seed =atoi(argv[5]);
    int N =atoi(argv[6]);
    
    
    

    return 0;
}
