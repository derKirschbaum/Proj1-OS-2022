#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WRITER 10
#define MAX_READER 10
#define MAX_NUMBER 100000
#define MAX_INTEGER 1000
sem_t mutex;
sem_t write_mutex;
char line[MAX_INTEGER];
int sleep_time = 1;
struct thread {
  int tid;             // thread ID
  int amount_Rand; // Amount of random number in each thread
  FILE *fp;            // file pointer
};

typedef struct {
  int *list;  // pointer
  size_t used; // storage of current used list
  size_t size; // storage of limited size of list
} Buffer;

Buffer buff; //buffer shared list

void start_bufferList(Buffer *fec){
  fec->list = malloc(sizeof(int));
  fec->used =0;
  fec->size =1;
}

void insert_item(Buffer *fec, int item) {
  if (fec->used == fec->size) {
    fec->size *= 2;
    fec->list = realloc(fec->list, fec->size * sizeof(int));
  }
  fec->list[fec->used++] =item;
}

/*---------------------------------------------------*/

void *writer(void *args) {
  struct thread *arg =
      (struct thread *)args; // change type of args -> struct thread
  int id =arg->tid;            // assign to argument of thread id
  FILE *f =arg->fp;            // point to argument of file fp
  int fileRead;

  while (EOF != fscanf(f, " %d", &fileRead)) {
    sem_wait(&write_mutex);
    insert_item(&buff, fileRead);
    sem_post(&write_mutex);

    sleep(sleep_time);
  }
  printf("WRITER %d DONE\n", id);
}

void *reader(void *args) { 
  struct thread *arg = (struct thread *)args;     // changing from args to thread
  int id =arg->tid;                
  FILE *f =arg->fp;                
  int size =arg->amount_Rand; 
  int num_ready =1;
  int counter =0; // for counting loop until reaching the amount of random numbers

  while (counter < size) {
    /*
    */
    if (buff.list[counter] != NULL) {
      sem_wait(&mutex);
      num_ready--;
      if (num_ready == 0) { sem_wait(&write_mutex); }// thread is not ready
      sem_post(&mutex);
      
      /*---------------------*/
      char str[30];
      sprintf(str, "%d\n",
              buff.list[counter]);  
                                          
      fputs(str, f);                      // put value in str into *f
     
      sem_wait(&mutex);
      num_ready++; //
      if (num_ready == 1) { sem_post(&write_mutex); }// thread is ready
      sem_post(&mutex);
      counter++; 
      
      sleep(sleep_time);
    }
  }
  printf("READER %d DONE\n", id);
}
/*-----------------------------------*/

int main(int argc, char *argv[]) {

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
        "Invalid arguments\nUsage: ./multithread <# of writers> <# of readers> <input> <output> <seed> <N>");
        exit(-1);
    }
    if(atoi(argv[1]) < 1 || MAX_WRITER < atoi(argv[1])){
        fprintf(stderr,
        "Invalid arguments\n# of writers must be from 1 - %d\n",MAX_WRITER);
        exit(-1);
    }
    if(atoi(argv[2]) < 1 || MAX_READER < atoi(argv[2])){
        fprintf(stderr,
        "Invalid arguments\n# of readers must be from 1 - %d\n",MAX_READER);
        exit(-1);
    }
    FILE *in  =fopen(argv[3],"r");
    
    if(! in ){ /* (! file) = (file ==NULL) */ 
        fprintf(stderr,
        "Unable to open file\n");
        exit(-1);
    }
    while(fgets(line, sizeof(line), in)!=NULL){
    	int dec = atoi(line);
	if(dec < 1 || MAX_INTEGER < dec){
	   fprintf(stderr,
       	   "Invalid arguments\nEach integer must be from 1 - 1000\n");
       	   exit(-1);
	}
    }
    //-----------------------------------------------
    if(atoi(argv[6]) < 1 || MAX_NUMBER < atoi(argv[6])){
        fprintf(stderr,
        "Invalid arguments\nAmount of integers must be from 1 - %d\n",MAX_NUMBER);
        exit(-1);
    }

  //---------------Assigned argument-------------------
  int numWrit = atoi(argv[1]); 
  int numRead = atoi(argv[2]); 
                            
  char inputName[100];
  strcpy(inputName, argv[3]); // name of input file that want to import
  char outputName[100];
  strcpy(outputName, argv[4]); // name of output file that expected
  
  int seed = atoi(argv[5]);  
  int N = atoi(argv[6]);     
  //--------------------------------------------------

  srand(seed); // set seed
  start_bufferList(&buff); 
    	
  exit(0);
}
