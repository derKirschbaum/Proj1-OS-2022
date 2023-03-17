#include "stdio.h"
#include "stdlib.h"

int main(int argc, char* argv[]){

    // Check input arguments
    // argc = # number of argument
    // argv = array of argument
    // !! default value of argc is 1, therefore we need to check for 7 args
    // !! default value of argv[0] is the name of program, custom args starts from argv[1]
    // !! argv = [ programName, # writer, # reader, input, output, seed, N]; # of args = 7
    if (argc != 7 || argv[1] > 10 || argv[2] > 10 || argv[1] <= 0 || argv[2] <= 0 || argv[5] <= 0 || argv[5] > 100000)
    {
        //Print to stderr (Standard Error)
        fprintf(stderr,
        "\nInvalid arguments\n\nUsage: ./multithread <# of writers> <# of readers> <input> <output> <seed> <N>\n\nConstraints: 0 < #writer/reader <= 10\n             0 < N <= 100,000");
        return 1;
    }

    return 0;
}