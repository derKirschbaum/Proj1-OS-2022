#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <assert.h>

#define MAX_WRITER 10
#define MAX_READER 10
#define MAX_INTEGER 100000
#define BUFFER_SIZE 1000
#define TRUE 1
struct  buffer {
  int n;
  struct buffer *next;
}buff;
pthread_mutex_t mutex;
sem_t full,empty;
char  line[MAX_INTEGER];


int b_counter; //buffer counter
pthread_t tid; //Thread ID
pthread_attr_t attr;//Set of attributes of thread

//void *writer(void *wno); /* the producer thread */
void *reader(void *rno); /* the consumer thread */

void initializeData() {
    /* Create the mutex lock */
    pthread_mutex_init(&mutex, NULL);
    /* Create the full semaphore and initialize to 0 */
    sem_init(&full, 0, 0);
    /* Create the empty semaphore and initialize to BUFFER_SIZE */
    sem_init(&empty, 0, MAX_INTEGER);
    /* Get the default attributes */
    pthread_attr_init(&attr);
    /* init buffer */
    b_counter = 0;
}
/* Add an item to the buffer */
void insert_item(struct buffer **item,int fec) {
        struct buffer *newItem = (struct buffer *) malloc (sizeof (struct buffer));
	newItem->n =fec;
	newItem->next = *item;
	*item =newItem;
}
/* Remove an item from the buffer */
void remove_item(struct buffer **item, int kek) {
  // 
	struct buffer *temp = *item;
	if(*item ==NULL){
	  return;
	}
  /* When the buffer is not empty remove the item
  and decrement the counter */
	*item =(*item)->next;
	free(temp);
}

/* Writer Thread (drafted)*/
void *writer(void *wno, FILE *fir) {
  long tid;
  tid=(long) wno;

  while(TRUE) {
  // ge
    
  /* acquire the empty lock */
  sem_wait(&empty);
  /* acquire the mutex lock */
  pthread_mutex_lock(&mutex);
    while(fgets(line, sizeof(line), fir)!=NULL){

    	int im  =  atoi(line);
	insert_item(&buff,im);
     }
 

   /* release the mutex lock */
   pthread_mutex_unlock(&mutex);
   /* signal full */
   sem_post(&full);
   printf("Writer %ld done",tid);
 }
}

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
    FILE *out =fopen(argv[4],"r");
    if(! in  || ! out){ /* (! file) = (file ==NULL) */ 
        fprintf(stderr,
        "Unable to open file\n");
        exit(-1);
    }
    while(fgets(line, sizeof(line), in)!=NULL){
    	int dec = atoi(line);
	if(dec < 1 || 1000 < dec){
	   fprintf(stderr,
       	   "Invalid arguments\nEach integer must be from 1 - 1000\n");
       	   exit(-1);
	}
    }
    //-----------------------------------------------
    if(atoi(argv[6]) < 1 || MAX_INTEGER < atoi(argv[6])){
        fprintf(stderr,
        "Invalid arguments\nAmount of integers must be from 1 - %d\n",MAX_INTEGER);
        exit(-1);
    }

    int num_writers =atoi(argv[1]);
    int num_readers =atoi(argv[2]);
  //FILE *in  =fopen(argv[3],"r"); just reminding
    int seed =atoi(argv[5]);
    int N =atoi(argv[6]);
    	
    exit(0);
}
