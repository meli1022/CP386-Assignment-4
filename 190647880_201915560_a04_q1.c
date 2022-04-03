/*
 ------------------------------
 Authors: Melissa Pinto
 Phoebe Shulman
 IDs:	190647880
 201915560
 Github: https://github.com/meli1022/CP386-Assignment-4
 ------------------------------

 */

/*
 ./190647880_201915560_a04_q1 10 5 7 8

 args: number of available resources of each type

 eg:
 4 resource types:
 10 instances of the first type, 5 of the second type,
 7 of the third type, and 8 of the fourth type
 */

/*
 * commits:
 * skeleton/frame work
 * semaphores
 * input
 * status,exit,invalid input
 *
 * //maybe RQ and RL? added to thread run...-main issue...
 *

 */

//eqns toupdate matrix:	//alloc = input. need = max- alloc[row]? //availbe  = avaible-alloc [cols]?
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include <sys/stat.h>

#include<semaphore.h>
sem_t sem;

typedef struct customer { //thread
	int resource[4]; // can have up to 5 resources for the customer

} Customer;

//typedef struct thread //represents a single thread, you can add more members if required
//{
//	int tid; //char tid[4]; //id of the thread as read from file
////pthread_t handle;
////int state;
//	//each thread also need a needed, availble. ?and allocated - of its own?//and id//or just print off from main matrix?
//	//need thread id?
//} ThreadOLD;

typedef struct thread //represents a single thread
{
	//char tid[4]; //id of the thread as read from file
	int tid; //or change process id and safe sequn type? //no atoi?

//add more members here as per requirement
	//float start_time; //int start_time;
	//float lifetime; //int lifetime;
	//int is_executed; //state of thread

	pthread_t pt_id; //posix thread id

	int alloc[100]; //1 row [100];
	int need[100];
	int available[100];
} Thread;
int readFile(char *fileName, Customer **customer) { //read Maximum resources from file

	FILE *in = fopen(fileName, "r");
	if (!in) {
		printf("Error in opening input file...exiting with error code -1\n");
		return -1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';

	while (!feof(in)) {
		char line[100];
		if (fgets(line, 100, in) != NULL) {
			strncat(fileContent, line, strlen(line));
		}
	}
	fclose(in);

	char *command = NULL;
	int customerCount = 0;
	char *fileCopy = (char*) malloc((strlen(fileContent) + 1) * sizeof(char));
	strcpy(fileCopy, fileContent);
	command = strtok(fileCopy, "\r\n");

	while (command != NULL) {
		customerCount++; // counting of customers and increment by 1
		command = strtok(NULL, "\r\n");
	}
	*customer = (Customer*) malloc(sizeof(customer) * customerCount);

	char *lines[customerCount];
	command = NULL;
	int i = 0;
	command = strtok(fileContent, "\r\n");

	while (command != NULL) {
		lines[i] = malloc(sizeof(command) * sizeof(char));
		strcpy(lines[i], command);
		i++;
		command = strtok(NULL, "\r\n");
	}

	for (int k = 0; k < customerCount; k++) {
		char *token = NULL;
		int j = 0;
		token = strtok(lines[k], ",");
		while (token != NULL) {
			(*customer)[k].resource[j] = atoi(token); //set resource number for resource 1 in index j

			token = strtok(NULL, ",");

			//token = strtok(NULL, " ");
			j++;
		}
	}

	return customerCount;
}

void* threadRun(void *t); //the thread function, the code executed by each thread
//void* threadRun(void *t, int threadNum, int numResourceTypes, int allocated);

int main(int argc, char *argv[]) { //banker's algorithm.

	//vars
	sem_init(&sem, 0, 1);	//unnamed

	//n customers for m resource types. //eg 5 customers *4 types
	Customer *customer = NULL;
	int numofCustomers = readFile("sample4_in.txt", &customer); //n = 5
	int numResourceTypes = argc - 1; //m = 4//resources types passed (not including argv[0])

	int available[numResourceTypes];	//available amount of each resource

	int maximum[numofCustomers][numResourceTypes]; // maximum demand of each customer //5,4

	int allocated[numofCustomers][numResourceTypes]; //amount currently allocated to each customer
	int need[numofCustomers][numResourceTypes];	//remaining need of each customer

	int safeSequnce[100]; //dyanmic?//ad p1 values to it
	int safeCounter = 0; //num elemes in safe sequnce

	char commands[20]; //RQ. Stastus. etc

	char p1[20]; //p1 - process number . and  num resources inputed
	int temp[numResourceTypes];		//array of inputs

	//need to crtate numofCustomers amount of threads...
	//pthread_t t1, t2, t3, t4, t5;

	//output

	printf("Number of Customers: %d\n", numofCustomers);

	//available
	for (int i = 0; i < numResourceTypes; i++) {
		available[i] = atoi(argv[i + 1]); //in command line  //not argv[0]
	}

	printf("Currently Available resources:");
	for (int i = 0; i < numResourceTypes; i++) {
		printf("%d ", available[i]);
	}
	printf("\n");

	//max
	for (int i = 0; i < numofCustomers; i++) { //5
		for (int j = 0; j < numResourceTypes; j++) { //4
			maximum[i][j] = customer[i].resource[j];
		}
	}

	printf("Maximum resources from file:\n"); //contents of file-print line by line

	for (int i = 0; i < numofCustomers; i++) {
		for (int j = 0; j < numResourceTypes; j++) {

			printf("%d ", maximum[i][j]);
		}
		printf("\n");
	}

	//allocated and need
	for (int i = 0; i < numofCustomers; i++) {
		for (int j = 0; j < numResourceTypes; j++) {

			allocated[i][j] = 0;
			need[i][j] = 0;
		}
	}

	while (1) { //program loop

		//input
		printf("Enter Command: ");
		scanf("%s", commands);

		if (strcmp(commands, "RQ") == 0) { //command =RQ
			//	eg RQ 0 1 0 0 1
			//customer/thread 0 were to request the resources (1, 0, 0, 1)

			/*
			 * RQ:
			 * input = process id, requests
			 * resouces request algo
			 * if safty algo: allocate. need = max - alloc
			 * else wati?
			 */

			//get other inputs
			scanf("%s", p1);			//process id
			int processID = atoi(p1);
			//printf("process id: %d\n", processID);

			for (int i = 0; i < numResourceTypes; i++) { //requested

				scanf("%s", p1);
				temp[i] = atoi(p1);
				//printf("%d ", temp[i]);
			}

			// safety algorithm
			// if it leaves the system in a safe state,otherwise will deny it.
			//allocate resources if safe

			int isSafe = 1;

			//firs check is requiesti>max i //eg rq 1 1000 1 1 1 1
			for (int i = 0; i < numResourceTypes; i++) { //requested

				if (temp[i] > maximum[processID][i]) {
					isSafe = 0;
				}

			}

			//step 1
			int work[numResourceTypes];	//temp avaible array //m
			int finish[numofCustomers];	//n

			for (int i = 0; i < numResourceTypes; i++) {
				work[i] = available[i];
			}

			for (int i = 0; i < numofCustomers - 1; i++) {
				finish[i] = 0; //false
			}

			//step 2

			for (int i = 0; i < numofCustomers; i++) {

				if (finish[i] == 0 && need[processID][i] <= work[i]) { //use row of  processID

				//step 3
					work[i] = work[i] + allocated[processID][i];
					finish[i] = 1; //true

				}
			}

			//step 4
			for (int i = 0; i < numofCustomers; i++) {
				if (finish[i] == 0) { //not all true -> not safe
					isSafe = 0; //false
				}
			}

			//printf("isSafe %d\n", isSafe);
			if (isSafe == 1) { //resource alloc

				printf("State is safe, and request is satisfied\n");

				//update everything
				safeSequnce[safeCounter] = processID; //add to sequence
				safeCounter += 1;

				for (int j = 0; j < numResourceTypes; j++) //avail = avail - request
					available[j] -= temp[j];

				for (int j = 0; j < numResourceTypes; j++) //alloc  = alloc +request?
					allocated[processID][j] += temp[j];

				for (int j = 0; j < numResourceTypes; j++) //need = max - request
					need[processID][j] = maximum[processID][j] - temp[j];
				///or need = max - alloc ?

			} else {
				printf("not safe\n");
			}

		} else if (strcmp(commands, "RL") == 0) {			//command =RL
			//eg RL 4 1 0 0 0
			// customer 4 wishes to release the resources (1, 0, 0, 0)

			//get other inputs
			scanf("%s", p1);			//process id
			int processID = atoi(p1);
			//printf("process id: %d\n", processID);

			for (int i = 0; i < numResourceTypes; i++) { //requested

				scanf("%s", p1);
				temp[i] = atoi(p1);
				//printf("%d ", temp[i]);
			}

			//release//opposite of request? //but assume safe?

			//update everything

			for (int j = 0; j < numResourceTypes; j++) //avail
				available[j] += temp[j]; //-= temp[j];

			for (int j = 0; j < numResourceTypes; j++) //alloc
				allocated[processID][j] -= temp[j]; // += temp[j];

			for (int j = 0; j < numResourceTypes; j++) //need
				need[processID][j] = maximum[processID][j] + temp[j]; //maximum[processID][j] - temp[j];

			printf("The resources have been released successfully\n");

		} else if (strcmp(commands, "Status") == 0) { //command =Status

			/*
			 *print all arrays and matrices:  (available, maximum, allocation, and need).
			 */

			printf("Available Resources:\n");
			for (int i = 0; i < numResourceTypes; i++) {
				printf("%d ", available[i]);
			}
			printf("\n");

			printf("Maximum Resources:\n");
			for (int i = 0; i < numofCustomers; i++) { //5
				for (int j = 0; j < numResourceTypes; j++) { //4

					printf("%d ", maximum[i][j]);
				}
				printf("\n");
			}

			printf("Allocated Resources:\n");
			for (int i = 0; i < numofCustomers; i++) {
				for (int j = 0; j < numResourceTypes; j++) {

					printf("%d ", allocated[i][j]);
				}
				printf("\n");
			}

			printf("Need Resources:\n");
			for (int i = 0; i < numofCustomers; i++) {
				for (int j = 0; j < numResourceTypes; j++) {

					printf("%d ", need[i][j]);
				}
				printf("\n");
			}

		} else if (strcmp(commands, "Exit") == 0
				|| strcmp(commands, "q") == 0) {

			//Exit command is used to exit the loop and the program ////q to debug
			break;

		} else if (strcmp(commands, "Run") == 0) {

			/*
			 Run command executes customers as threads in a safe sequence. Each thread
			 requests the resources it needs, releases them, and lets the next thread in the sequence run.
			 */

			/*
			 * print sequnce
			 * tid = sequnces[i]
			 * arrays = arrayu[tid]
			 * run threads
			 *
			 */
//safe seeuqnce not right?
			printf("Safe Sequence is: "); //1 3 2 4 0\n"); //need build up values--these are process id values
			for (int i = 0; i < safeCounter; i++) {
				printf("%d ", safeSequnce[i]);
				//threads[i].tid = safeseuqnce[i]?
				//	printf("%c ", safeSequnce[i] + '0');//int into char
			}
			printf("\n");

			Thread *threads; // array
			//*threads = (Thread*) malloc(sizeof(Thread) * safeCounter); //threadCount);
			threads = (Thread*) malloc(sizeof(Thread) * safeCounter);

			for (int k = 0; k < safeCounter; k++) { //assing tid
				int i = safeSequnce[k];
				;
				(threads)[k].tid = safeSequnce[k];

				for (int j = 0; j < numResourceTypes; j++) {
					(threads)[k].alloc[j] = allocated[i][j]; //allocated[safeSequnce[k]];
					(threads)[k].need[j] = need[i][j];
					(threads)[k].available[j] = available[j]; //available[i][j];
				}
			}

//			char toke[20];
//
//			for (int k = 0; k < safeCounter; k++) {
//				strcpy(toke, safeSequnce[k] + '0');
//				//int a = safeSequnce[k];
//				//toke = a + '0';			//safeSequnce[k] + '0';
//				(threads)[k].tid = toke;
//			}

			//return 0;
//
//			char *token = NULL;
//			//int *token = NULL;
//
////			*token = safeSequnce[0] + '0';
////						//printf("%c,", token); //printf("%c," * token);
////						printf("token %s,", token); //*token, &token
////
//
////			char t[5];
////			itoa(safeSequnce[0], t, 10); //int to str
////			printf("%s ", t);
//
//			for (int k = 0; k < safeCounter; k++) { //copy id
//				//token = safeSequnce[k] + '0'; //int to char?
//				//strcpy(token, safeSequnce[k] + '0');
//				//(threads)[k].tid = token;
//				token = "1"; //needs to be safe sequence... how conver it //strtok(lines[k], ";");
//
//				strcpy((threads)[k].tid, token); //strcpy((*threads)[k].tid, token);
//			}

			//run them
			//have to reutnr a value... for  new allcoedted? so alloc = thread alloc?-yes...
			for (int i = 0; i < safeCounter; i++) { //until no more threads left

				pthread_create(&(threads[i].pt_id), NULL, threadRun,
						&(threads[i])); //create thread

//				//updaete avalible = avail - alloc //something like this..but in threads? then update from threads?
				for (int j = 0; j < numResourceTypes; j++) {
					int k = safeSequnce[i];
					available[j] = available[j] + allocated[k][j];
					//(threads)[k].alloc[j] = allocated[i][j]; //allocated[safeSequnce[k]];

					//(threads)[k].available[j] = available[j]; //available[i][j];
				}
			}

			for (int i = 0; i < safeCounter; i++) {
				pthread_join(threads[i].pt_id, NULL);
			}

			// just resete matraxies  at the end after running //since theyll be relasesd?
			for (int i = 0; i < numResourceTypes; i++) {
				available[i] = atoi(argv[i + 1]); //in command line  //not argv[0]
			}

			//allocated and need
			for (int i = 0; i < numofCustomers; i++) {
				for (int j = 0; j < numResourceTypes; j++) {

					allocated[i][j] = 0;
					need[i][j] = 0;
				}
			}

			//=============
//			Thread *threads = NULL;
//			*threads = (Thread*) malloc(sizeof(Thread) * safeCounter);
//			for (int i = 0; i < safeCounter; i++) {
//				threads[i].tid = safeSequnce[i];
//				pthread_create(&(threads[i].tid), NULL, threadRun, &threads[i]);
//				//(*threads)[i].tid = safeSequnce[i];
//				//threads[i].tid = safeseuqnce[i]?
//			}
			//call threads in safe sequence order... not sequential...
			//how to assign thread tid? and other vars? //eg assign thread3 .alloc = row3 of alloc matrix?

			/*
			 ///for all threads. if tid == safesequence[i] then run//if safe squence[[i] == 1; runt1?
			 pthread_t t1, t2, t3, t4, t5;
			 for (int i = 0; i < safeCounter; i++) {
			 if (safeSequnce[i] == 1) {
			 pthread_create(&t1, NULL, &threadRun, NULL);
			 //printf("%d ", safeSequnce[i]);
			 }			//else if 2...
			 }

			 //pthread_create(&t1, NULL, &threadRun, NULL);
			 pthread_create(&t2, NULL, &threadRun, NULL);
			 pthread_create(&t3, NULL, &threadRun, NULL);
			 pthread_create(&t4, NULL, &threadRun, NULL);
			 pthread_create(&t5, NULL, &threadRun, NULL);

			 pthread_join(t1, NULL);
			 pthread_join(t2, NULL);
			 pthread_join(t3, NULL);
			 pthread_join(t4, NULL);
			 pthread_join(t5, NULL);
			 */
			//&t1.tid = 1;
//			Thread *threads = NULL;
//			*threads = (Thread*) malloc(sizeof(Thread) * numofCustomers);
//			for (int k = 0; k < numofCustomers; k++) {
//
//				(*threads)[k].tid = k;
//
//			}
//			for (int i = 0; i < numofCustomers; i++) { //5
//				//&threads[i].tid = i;
//				pthread_create(&(threads[i].tid), NULL, &threadRun,
//						&(threads[i])); //create thread
//
//				//	pthread_create(&threads[i], NULL, &threadRun, NULL);
//				//pthread_create(&(threads[i].handle), NULL, threadRun, &threads[i]);
//			}
		} else { // If user enters a wrong command
			printf("Invalid input, use one of RQ, RL, Status, Run, Exit\n");
		}
	}
	return 0;

}

//Function to run the customer threads
//void* threadRun(void *t, int threadNum, int numResourceTypes, int allocated) {
void* threadRun(void *t) {

	//printf("%s ", ((Thread*) t)->tid); //d //c

	sem_wait(&sem); //semphore so thread runs fully

	int numResourceTypes = 4; //how get?
	int temp[numResourceTypes];

	//int threadNum = ((Thread*) t)->tid)); //1;
	int tid = ((Thread*) t)->tid;
	//int *tid = ((Thread*) t)->tid;
	//char *tid = ((Thread*) t)->tid;
	//threadNum = ((Thread*) t)->tid;
	//thread have indiv arrays?//or copy paste to acutally allocate and rlease?

	printf("--> Customer/Thread %d\n", tid);	   //threadNum); //%d //%s

	printf("Allocated resources: ");		//1 1 1 1"); //traverse values
	for (int j = 0; j < numResourceTypes; j++) { //4
		printf("%d ", ((Thread*) t)->alloc[j]); //1); //allocated[threadNum][j]);
	}
	printf("\n");

	printf("Needed: "); //3 1 2 1");
	for (int j = 0; j < numResourceTypes; j++) {
		printf("%d ", ((Thread*) t)->need[j]); //1); //need[threadNum][j]);
	}
	printf("\n");

	printf("Available: "); //4 1 3 3");
	for (int j = 0; j < numResourceTypes; j++) {
		printf("%d ", ((Thread*) t)->available[j]); //1); //available[i]);
	}
	printf("\n");

	printf("Thread has started\n");
	//just the realse code agains?

	//get other inputs
	//scanf("%s", p1);			//process id
	//int processID = tid;				//atoi(p1);
	//printf("process id: %d\n", processID);

	for (int i = 0; i < numResourceTypes; i++) { //requested //to release(alloc?)

		//scanf("%s", p1);
		temp[i] = (((Thread*) t)->alloc[i]); //allocated[processID][i]; //atoi(p1);
											 //printf("%d ", temp[i]);
	}

//release//opposite of request? //but assume safe?

//update everything

	for (int j = 0; j < numResourceTypes; j++) //avail
		((Thread*) t)->available[j] += temp[j]; //available[j] += temp[j]; //-= temp[j];

	for (int j = 0; j < numResourceTypes; j++) //alloc=alloc - alloc //or just alloc = 0
		((Thread*) t)->alloc[j] = 0; //allocated[processID][j] -= temp[j]; // += temp[j];

	for (int j = 0; j < numResourceTypes; j++) //need //need = 0?
		((Thread*) t)->need[j] = 0; //need[processID][j] = maximum[processID][j] + temp[j]; //maximum[processID][j] - temp[j];

	printf("The resources have been released successfully\n");

//update matrix?
//availbe = availbe + alloc?
	for (int i = 0; i < numResourceTypes; i++) {
		;	//available[i] = available[i] + allocated[threadNum][i];
	}

//and alloc = 0? //realase all?

	for (int j = 0; j < numResourceTypes; j++) {
		;	//allocated[threadNum][j] = 0;
	}

	printf("Thread has finished\n");
	printf("Thread is releasing resources\n");

//New Available status.

	printf("New Available: "); //5 2 4 4")
	for (int j = 0; j < numResourceTypes; j++) {
		printf("%d ", ((Thread*) t)->available[j]); //1); //available[i]);
	}
	printf("\n");

	sem_post(&sem);
	pthread_exit(0);
}
