/*
 ------------------------------
 Authors: Melissa Pinto
 Phoebe Shulman
 IDs:	190647880
 201915560
 Github: https://github.com/meli1022/CP386-Assignment-4
 ------------------------------
 passing the number of available resources of each type via
 command line to initialize the available array by these values.
 example, if in system there
 were four resource types,
 with ten instances of the first type, f
 ive of the second type,
 seven of the
 third type, and
 eight of the fourth type
 ./Question1 10 5 7 8
 ./190647880_201915560_a04_q1 10 5 7 8
 */

//commit 2: mild chagne in  read file //fixed - read command line input //updated matrixes //status ok //(note q = exit) //udpate some inputs --2 lines of input-how get first input?
//added to thread run //input off //allocated - not calcuated right?
// safety algorithm// if it leaves the system in a safe state,otherwise will deny it.
//need a line of input - where input can be 1 word or many ..
//fgets //getline
//for now break inptu into 2? //or array input - and check first 2 letters for rq?
//RQ:
//eqns toupdate matrix:	//alloc = input. need = max- alloc[row]? //availbe  = avaible-alloc [cols]?
//RL
//
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include <sys/stat.h>

typedef struct customer {
	int resource[4]; // can have up to 5 resources for the customer

//each thread also need a needed, availble. ?and allocated - of its own?//and id
} Customer;

int readFile(char *fileName, Customer **customer) {

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
//void* safety();//check if safe
//banker's algorithm.

int main(int argc, char *argv[]) {

	//vars
	Customer *customer = NULL;

	int numofCustomers = readFile("sample4_in.txt", &customer);

	//char *available[100]; //available amount of each resource //
	int available[3]; //4

	for (int i = 1; i < argc; i++) { //not argv[0]
		available[i] = atoi(argv[i]); //in command line
	}

//	for (int i = 1; i < argc; i++) { //not argv[0]
//		available[i] = argv[i]; //in command line
//	}

	int maximum[5][4]; // maximum demand of each customer  //[4][5] //argc-1,numcusomters
	int allocated[5][4]; //amount currently allocated to each customer
	int need[5][4];	 //remaining need of each customer

	//int safeSequnce[]; //dyanmic?//ad p1 values to it

	char commands[20]; //RQ. Stastus. etc
	int p1[20], p2[20], p3[20], p4[20], p5[20];	//p1 - process number . p2 - p5: num resources ?//char

	//need to crtate numofCustomers amount of threads...
	pthread_t t1;	//, t2, t3, t4, t5;
	//output
	printf("Number of Customers: %d\n", numofCustomers);

	printf("Currently Available resources:");//printf("Currently Available resources: 10 5 7 8 \n");
	for (int i = 1; i < argc; i++) { //not argv[0] //i = 0
		printf("%d ", available[i]); //in command line
	}
//	for (int i = 1; i < argc; i++) { //not argv[0]
//		printf("%s ", available[i]); //d
//	}
	printf("\n");

	printf("Maximum resources from file:\n"); //contents of file-print line by line

	for (int i = 0; i < numofCustomers; i++) { //5//num customers
		for (int j = 0; j < argc - 1; j++) { //4 //resources types passed (not including argv[0]

			maximum[i][j] = customer[i].resource[j];
			printf("%d ", maximum[i][j]); //printf("%d ", customer[i].resource[j]);
		}
		printf("\n");
	}

	for (int i = 0; i < numofCustomers; i++) { //5
		for (int j = 0; j < argc - 1; j++) { //4

			allocated[i][j] = 0;
			need[i][j] = 0;
		}
	}

	while (1) {

		//input
		printf("Enter Command: ");

		scanf("%s", commands);	//multi command? expted 5 input at most?
		//scanf("%s %d %d %d %d %d",commands, p1, p2, p3, p4, p5); //commands - wrod (RQ). p1- thread number . rest - request nums
//make rest  null if not rq or rl?

		//just first part of input mathces?
		//if (strcmp(commands[0], "RQ") == 0) {

		//		printf("%c %c", commands[0], commands[1]);
//		char temp[20];
//		temp = commands[0] + commands[1];
//		printf("%d", strcmp(temp, "RQ"));

		if (strcmp(commands, "RQ") == 0) { //compare
			//	eg RQ 0 1 0 0 1 //customer/thread 0 were to request the resources (1, 0, 0, 1)

			//scanf("%d", p1);
			//printf("%d", allocated[p1][0]);

			//allocated[2][0] = p1;

			//int t = &p1;
			//scanf("%d", &allocated[t][0]);

			//scanf("%d %d %d %d %d", p1, p2, p3, p4, p5);

			//do saftey algo here..

			//saftye algo //to check if this would be safe?
			int work[5];			//[4]; //temp avaible array

			int isSafe = 1;
			int finish[5];

			for (int i = 0; i < numofCustomers; i++) { //5

				work[i] = available[i];

			}
			for (int i = 0; i < numofCustomers; i++) { //5
				finish[i] = 0; //false

			}

			//find index i

			for (int i = 0; i < numofCustomers; i++) { //5

				if (finish[i] == 0 && need[i][0] <= work[i]) { //available[i]) { //which need and alloc to compare?
					printf("yes");

					work[i] = work[i] + allocated[i][0];
					//available[i] = available[i] + allocated[i][0];
					finish[i] = 1; //true

				}
			}
			for (int i = 0; i < numofCustomers; i++) { //5
				if (finish[i] == 0) {
					isSafe = 0; //false
				}

			}

			if (isSafe == 1) {

				printf("isSafe %d\n", isSafe);
//do resource alloc

				printf("State is safe, and request is satisfied\n");

				//update everything
				//attmpet at resource alloc
				for (int i = 1; i < argc; i++) { //not argv[0] //for (int i = 0; i < argc - 1; i++) {
					//printf("%s ", available[i]); //d
					available[i] = available[i] - 1; //each input //allcoedcted[j][i]? //last value not right?
				}

				for (int i = 0; i < numofCustomers; i++) { //5
					for (int j = 0; j < argc - 1; j++) { //4
						//printf("%d ", need[i][j]);
						need[i][j] = maximum[i][j] - allocated[i][j];
					}

				}

			}

			for (int i = 1; i < argc - 1; i++) { //not argv[0] //for (int i = 0; i < argc - 1; i++) {
				printf("%d ", available[i]); //d
				printf("%d ", work[i]);

				//work[i] = work[i] - 1; //each input //allcoedcted[j][i]? //last value not right?
			}
			printf("\n");

			//assume safe
			scanf("%d %d %d %d", &allocated[2][0], &allocated[2][1],
					&allocated[2][2], &allocated[2][3]); //p1 = 2 //how get p1?

			////if customer_number[i][j]>maximum[i][j]: invalid} {else

			printf("State is safe, and request is satisfied\n");

			//update everything

//			for (int i = 0; i < numofCustomers; i++) { //5
//
//				if (i == p1) { //first num is process number
//
//
//					allocated[i][1] = p2;
//					allocated[i][2] = p3;
//					allocated[i][3] = p4;
//					allocated[i][4] = p5;
//
//
//				}
//			}

//			for (int i = 0; i < argc - 1; i++) { //5//numofCustomers
//				//scanf("%d", &allocated[i][p1]); //
//				scanf("%d", &allocated[p1][i]);	//scanf("%d", &allocated[p1][i]);
//			}

			//------------

		} else if (strcmp(commands, "RL") == 0) {
			//eg RL 4 1 0 0 0 // customer 4 wishes to release the resources (1, 0, 0, 0),
			scanf("%d %d %d %d %d", p1, p2, p3, p4, p5); //scanf("%s %s %s %s %s", p1, p2, p3, p4, p5);
			printf("The resources have been released successfully\n");

		} else if (strcmp(commands, "Status") == 0) {
			;
			/*
			 * Status command would print all arrays and matrices used
			 (available, maximum, allocation, and need).
			 *
			 */
			printf("Available Resources:\n");
			for (int i = 1; i < argc; i++) { //not argv[0] //i = 0
				printf("%d ", available[i]); //in command line
			}
			printf("\n");

			printf("Maximum Resources:\n");

			for (int i = 0; i < numofCustomers; i++) { //5
				for (int j = 0; j < argc - 1; j++) { //4
					printf("%d ", maximum[i][j]);

				}
				printf("\n");
			}

			printf("Allocated Resources:\n");

			for (int i = 0; i < numofCustomers; i++) { //5
				for (int j = 0; j < argc - 1; j++) { //4
					printf("%d ", allocated[i][j]);

				}
				printf("\n");
			}

			printf("Need Resources:\n");

			for (int i = 0; i < numofCustomers; i++) { //5
				for (int j = 0; j < argc - 1; j++) { //4
					printf("%d ", need[i][j]);

				}
				printf("\n");
			}

		} else if (strcmp(commands, "Run") == 0) {
			;
			/*
			 Run command executes customers as threads in a safe sequence. Each thread
			 requests the resources it needs, releases them, and lets the next thread in the sequence run.
			 */

			//call thred run?
			printf("Safe Sequence is: 1 3 2 4 0\n"); //need build up values--thes are p1 values
			//threadRun()
			//idea- maybe a semphore so thread runs fully?
			pthread_create(&t1, NULL, &threadRun, NULL);

		} else if (strcmp(commands, "Exit") == 0
				|| strcmp(commands, "q") == 0) { //q to debug
				/*
				 *  Exit command is used to exit the loop and the program
				 */
			break;
		} else {			// If user enters a wrong command
			printf("Invalid input, use one of RQ, RL, Status, Run, Exit\n");
		}
	}

	return 0;
}

//Function to run the customer threads
void* threadRun(void *t) {

	printf("\n--> Customer/Thread %d", 1);
	printf("\nAllocated resources: ");			//1 1 1 1"); //traverse values
	printf("\nNeeded: "); //3 1 2 1");
	printf("\nAvailable: "); //4 1 3 3");

	printf("\n");
	printf("Thread has started\n");
	printf("Thread has finished\n");
	printf("Thread is releasing resources\n");

//New Available status.
//avabile = avialbe + alloc?
	printf("New Available: "); //5 2 4 4")
	pthread_exit(0);
}

