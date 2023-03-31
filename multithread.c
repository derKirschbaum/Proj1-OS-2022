#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_WRITER 10
#define MAX_READER 10
#define MAX_NUMBER 100000
#define MAX_INTEGER 1000
#define SLEEP_TIME 1
pthread_mutex_t mutex, mutexWrit;
pthread_cond_t condWrit,cond ;
char line[MAX_INTEGER];
struct thread {
  int tid;             // thread ID
  int amount_Rand; // Amount of random number in each thread
  FILE *fp;            // file pointer
};

typedef struct {
  int *list;  // pointer
  size_t used; // used list
  size_t size; // size of list
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
    pthread_mutex_lock(&mutexWrit);
    insert_item(&buff, fileRead);
    pthread_mutex_unlock(&mutexWrit);  
  
    sleep(rand() %3);
    //sleep(SLEEP_TIME);
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
    if  (buff.list[counter] != NULL) { 
      pthread_mutex_lock(&mutex);
      //pthread_cond_wait(&condWrit,&mutexWrit); // t
      pthread_mutex_unlock(&mutex);
      
      char str[MAX_INTEGER];
      sprintf(str, "%d\n",
              buff.list[counter]);  //assign 
                                          
      fputs(str, f);  // put value in str into *f
     
      pthread_mutex_lock(&mutex);
      //pthread_cond_signal(&condWrit); // thr
      pthread_mutex_unlock(&mutex);
      counter++;
      
      sleep(rand() %3);
      //sleep(SLEEP_TIME);
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
  char* endPtr;
  strcpy(outputName, argv[4]); // name of output file that expected
  unsigned int seed = strtoul(argv[5], &endPtr,10);  
  int N = atoi(argv[6]);     
  //---------------------------------------------------

  srand(seed); // set seed
  start_bufferList(&buff); 

  /* ---Writer section--- */

  FILE *fop; //read file pointer
  fop = fopen(inputName, "r"); // reading file
  struct thread writS[numWrit];
  for (int i = 0; i < numWrit; i++) {
    writS[i].tid =  i;  //assign numero ID
    writS[i].fp  = fop; 
  }
  

  /* ---Reader section--- */
  struct thread readS[numRead];
  for (int i = 0; i < numRead; i++) {
    char fName[100]; //size of name of output file 
    sprintf(fName, "%s_%d.txt", outputName, i); //apply name from input 
    readS[i].tid = i;                 
    readS[i].fp = fopen(fName, "w+"); // create empty file for writing
    readS[i].amount_Rand = rand()%N+1; // random amount of integers on the list
  }

  /* ---Thread section--- */
  
  // starting semaphores
  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&mutexWrit, NULL);
  pthread_cond_init(&condWrit, NULL);
  
  // Initializing Threads
  pthread_t writer_threads[numWrit], reader_threads[numRead] ;
  for (int i = 0; i < numWrit; i++) {
    pthread_create(&writer_threads[i], NULL, writer, &writS[i]);
  }
  for (int i = 0; i < numRead; i++) {
    pthread_create(&reader_threads[i], NULL, reader, &readS[i]);
  }
 
  /*----------------------------------------------*/
  for (int i = 0; i < numWrit; i++) {
    pthread_join(writer_threads[i], NULL);
  }
  for (int i = 0; i < numRead; i++) {
    pthread_join(reader_threads[i], NULL);
  }
  
  // Destroy mutex
  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&mutexWrit);
  
  return 0;
}
