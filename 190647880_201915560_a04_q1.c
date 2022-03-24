/*
 *  passing the number of available resources of each type via
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
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void* threadRun(void *t); //the thread function, the code executed by each thread

//banker's algorithm.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

int main(int argc, char *argv[]) {
	int n = 0; //5/ //requests from n customers for m resource types.
	int m = 0; //4?-

	//all arrays/matrix...
	int available = 0; //array
	//available amount of each resource
	int maximum = 0; // maximum demand of each customer //array? array size?

	int allocated = 0; //amount currently allocated to each customer
	int need = 0; //remaining need of each customer

	printf("%d %d %d %d", available, maximum, allocated, need);

	char command[20];

	FILE *in = fopen("sample4_in.txt", "r");
	//get n and m?
	n = 5; //maybe num lines in file?
	m = 4; //-maybe how many in 1 line of file?

	fclose(in);

	printf("%d %d\n", n, m); //debug

	printf("Number of Customers: %d\n", n);
	printf("Currently Available resources: 10 5 7 8 \n"); //10 5 7 8 from file
	printf("Maximum resources from file:\n"); //contents of file-print line by line

	//// safety algorithm
	//, if it leaves the system in a safe state,otherwise will deny it.

	while (1) {
		//input
		printf("Enter Command: ");
		scanf("%s", command);

		if (strcmp(command, "RQ") == 0) { //compare
			//	eg RQ 0 1 0 0 1 //customer/thread 0 were to request the resources (1, 0, 0, 1),

			////if customer_number>maximum: invalid} {else
			printf("State is safe, and request is satisfied\n");

		} else if (strcmp(command, "RL") == 0) {
			//eg RL 4 1 0 0 0 // customer 4 wishes to release the resources (1, 0, 0, 0),

			printf("The resources have been released successfully\n");

		} else if (strcmp(command, "Status") == 0) {
			;
			/*

			 * Status command would print all arrays and matrices used
			 (available, maximum, allocation, and need).
			 *
			 */
		} else if (strcmp(command, "Run") == 0) {
			;
			/*

			 Run command executes customers as threads in a safe sequence. Each thread
			 requests the resources it needs, releases them, and lets the next thread in the sequence run.
			 */
		} else if (strcmp(command, "Exit") == 0) {
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
void* threadRun(void *t) {
	printf("Thread has started/n");
	printf("Thread has finished/n");
	printf("Thread is releasing resources/n");

//New Available status.
	pthread_exit(0);
}

/*
 int mainEg(int argc, char *argv[]) {
 char command[20];
 char command1[20] = "Exit";
 int value;
 printf("Enter the first string : ");
 scanf("%s", command);

 value = strcmp(command, command1); //
 value = strcmp(command, "Exit"); //not strncmp
 if (value == 0)
 printf("strings are same");
 return 0;
 }
 */
