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
 * banker's algorithm.
 *RQ and RL: request and release resources
 *  if request satisfies the safety algorithm:grant a request
 *status: output the values of the different data structures (available, maximum, allocation,
 and need)

 Run:executes customers as threads in a safe sequence.
 --------------
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
 * user input
 * status,exit,invalid input
 *
 *  RQ and RL
 * some of run command:added to thread run and thread strucutrure (outtputs data strucutures and updates a new avaible value)
 *

 */

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

typedef struct thread //represents a single thread
{
	int tid; //thread id  number

	pthread_t pt_id; //posix thread id

	//have indiv rows  of maxtrix
	int alloc[100];
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

void* threadRun(void *t); // code executed by each thread

int main(int argc, char *argv[]) { //banker's algorithm

	//vars
	sem_init(&sem, 0, 1);	//unnamed semaphore

	//n customers for m resource types. //eg 5 customers *4 types
	Customer *customer = NULL;
	int numofCustomers = readFile("sample4_in.txt", &customer); //n = 5
	int numResourceTypes = argc - 1; //m = 4//resources types passed (not including argv[0])

	int available[numResourceTypes];	//available amount of each resource

	int maximum[numofCustomers][numResourceTypes]; // maximum demand of each customer //5,4

	int allocated[numofCustomers][numResourceTypes]; //amount currently allocated to each customer
	int need[numofCustomers][numResourceTypes];	//remaining need of each customer

	int safeSequnce[100]; //add process id  values to it
	int safeCounter = 0; //num elemes in safe sequnce

	char commands[20]; //RQ. Stastus. etc

	char p1[20]; //p1 - process number . and  num resources inputed
	int temp[numResourceTypes];		//array of inputs

	Thread *threads; // array of threads

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
			 * if safty algo: allocate resouces

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

			int isSafe = 1; //assume true

			//firs check is request i > max i //eg rq 1 1000 1 1 1 1
			for (int i = 0; i < numResourceTypes; i++) { //requested

				if (temp[i] > maximum[processID][i]) {
					isSafe = 0; //false
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
				available[j] += temp[j];

			for (int j = 0; j < numResourceTypes; j++) //alloc
				allocated[processID][j] -= temp[j];

			for (int j = 0; j < numResourceTypes; j++) //need
				need[processID][j] = maximum[processID][j] + temp[j];

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
			 Run command executes customers as threads in a safe sequence.
			 Each thread requests the resources it needs, releases them,
			 and lets the next thread in the sequence run.
			 */

			/*
			 * print sequnce
			 * tid = sequnces[i]
			 * arrays = arrayu[tid]
			 * run threads
			 *update
			 *reset matrixes

			 */

			printf("Safe Sequence is: "); //1 3 2 4 0\n"); //need build up values--these are process id values
			for (int i = 0; i < safeCounter; i++) {
				printf("%d ", safeSequnce[i]);

				//	printf("%c ", safeSequnce[i] + '0');//int into char
			}
			printf("\n");

			threads = (Thread*) malloc(sizeof(Thread) * safeCounter); //*threads = (Thread*) malloc(sizeof(Thread) * threadCount);

			for (int k = 0; k < safeCounter; k++) { //assing tid = safeSequnce[]
				int seqNum = safeSequnce[k];

				(threads)[k].tid = seqNum; // safeSequnce[k];

				for (int j = 0; j < numResourceTypes; j++) { //update each matrix too

					(threads)[k].alloc[j] = allocated[seqNum][j];
					(threads)[k].need[j] = need[seqNum][j];
					(threads)[k].available[j] = available[j];
				}
			}

			//run threads  in safe sequence order.//have to update new avalible in between
			//in main and in threads: avalible = avail + alloc

			for (int k = 0; k < safeCounter; k++) { //for all threads
				int seqNum = safeSequnce[k];

				pthread_create(&(threads[k].pt_id), NULL, threadRun,
						&(threads[k])); //create thread

				//if ((threads)[k].tid == seqNum) { //only creae in order
//				pthread_create(&(threads[seqNum].pt_id), NULL, threadRun,
//						&(threads[seqNum])); //create thread

				for (int j = 0; j < numResourceTypes; j++) {

					available[j] = available[j] + allocated[seqNum][j];

				}
			}

			for (int i = 0; i < safeCounter; i++) {
				pthread_join(threads[i].pt_id, NULL);
			}

			//after all threads done: reset everything

			//avail
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
			safeCounter = 0; //reset

		} else { // If user enters a wrong command
			printf("Invalid input, use one of RQ, RL, Status, Run, Exit\n");
		}
	}
	return 0;

}

//Function to run the customer threads
void* threadRun(void *t) {

	//printf("%s ", ((Thread*) t)->tid); //d //c

	sem_wait(&sem); //semphore so thread runs fully

	int numResourceTypes = 4; //how get?
	int temp[numResourceTypes];

	int tid = ((Thread*) t)->tid; //int *tid =//char *tid =

	//thread have indiv row of matrix

	printf("--> Customer/Thread %d\n", tid);	   //%d //%s

	printf("Allocated resources: ");	//traverse values
	for (int j = 0; j < numResourceTypes; j++) { //4
		printf("%d ", ((Thread*) t)->alloc[j]);  //allocated[threadNum][j]);
	}
	printf("\n");

	printf("Needed: ");
	for (int j = 0; j < numResourceTypes; j++) {
		printf("%d ", ((Thread*) t)->need[j]); //need[threadNum][j]);
	}
	printf("\n");

	printf("Available: ");
	for (int j = 0; j < numResourceTypes; j++) {
		printf("%d ", ((Thread*) t)->available[j]); //available[i]);
	}
	printf("\n");

	printf("Thread has started\n");

	//just the realse code

	for (int i = 0; i < numResourceTypes; i++) { //requested //to release(alloc?)

		temp[i] = (((Thread*) t)->alloc[i]); //allocated[processID][i];
	}

	for (int j = 0; j < numResourceTypes; j++)
		((Thread*) t)->available[j] += temp[j]; //available[j] += temp[j]; //availbe = availbe + alloc?

	for (int j = 0; j < numResourceTypes; j++) //alloc=alloc - alloc //or just alloc = 0//allocated[processID][j] -= temp[j];
		((Thread*) t)->alloc[j] = 0;

	for (int j = 0; j < numResourceTypes; j++) //need
		((Thread*) t)->need[j] = 0; //need = 0?//need[processID][j] = maximum[processID][j] + temp[j]; //maximum[processID][j] - temp[j];

	printf("Thread has finished\n");
	printf("Thread is releasing resources\n");

//New Available status.

	printf("New Available: "); //5 2 4 4")
	for (int j = 0; j < numResourceTypes; j++) {
		printf("%d ", ((Thread*) t)->available[j]);  //available[i]);
	}
	printf("\n");

	sem_post(&sem);
	pthread_exit(0);
}
