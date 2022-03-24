#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
//best fit algo
int main(int argc, char *argv[]) {
	int MAX;
	MAX = 1000000; //&argv[1]; //*argv[1]; //1000000

	char command[20];
	printf("Allocated %d bytes of memory\n", MAX); //printf("Allocated 1000000 bytes of memory"); //max?

	while (1) {
		//input
		printf("command>");
		scanf("%s", command);

		//how to acccount for more than Rq or Rl inputed?

		if (strcmp(command, "RQ") == 0) { //compare
			/* RQ <process number> <size> <B>:
			 * RQ command is the new process that requires the
			 memory, followed by the amount of memory being requested, and finally the algorithm.
			 (B refers to best fit.)
			 */
			//RQ P0 20000 B //request for 20,000 bytes
			;

			//if()
			printf("No hole of sufficient size\n");
			//else
			printf("Successfully allocated %d to process %s\n", 200000, "P0"); //200000 -var,P0 -var

		} else if (strcmp(command, "RL") == 0) {
			/*
			 * RL <process number/name>:
			 * RL command will release the memory that has been
			 allocated to a process (e.g., P0).
			 *
			 */
			//RL P0 //eg
			printf("releasing memory for process %s\n", "P0");
			printf("Successfully released memory for process %s\n", "P0");

		} else if (strcmp(command, "Status") == 0) {
			;
			/*

			 Status: The Status command used for reporting the status of memory is entered.
			 */

			printf("Partitions [Allocated memory = %d]:\n", 650000);

			//loop?
			printf("Address [%d:%d] Process %s\n", 200000, 549999, "P1");

			printf("\n");
			printf("Holes [Free memory = %d]:\n", 350000);
			//looops?
			printf("Address [%d:%d] len = %d\n", 0, 199999, 200000);

		} else if (strcmp(command, "Exit") == 0) {
			/*
			 Exit: The Exit command is used to exit the loop and the program.

			 */
			break;
		} else {			// If user enters a wrong command
			printf("Invalid input, use one of RQ, RL, Status, Exit\n");
		}
	}

	return 0;
}

//int main1() { //q1.attempt 1
//
//	int n = 0; //5//maybe num lines in file? //requests from n customers for m resource types.
//	int m = 0; //4?--maybe how many in 1 line of file?
//
//	/*
//	 * aviallbe is array - 1*n
//	 * rest matrix :
//	 * n*m
//
//	 *
//	 */
//	//all arrays...
//	int available = 0; //array
//	//available amount of each resource
//	int maximum = 0; // maximum demand of each customer //array? array size?
//
//	int allocated = 0; //amount currently allocated to each customer
//	int need = 0; //remaining need of each customer
//	return 0;
//
//	char command[];
//	command = "Exit";
//	char temp[] = "RQ";
//
//	//char *command = "Exit";
//	//command = "Exit";
//	//char *temp = "RQ";
//
//	// safety algorithm
//	//, if it leaves the system in a safe state,otherwise will deny it.
//
//	/*
//	 *  user to interactively enter a request for resources, to release resources, or
//	 to output the values of the different data structures (available, maximum, allocation,
//	 and need) u
//	 */
//
//	//read the sample input file, sample4_in.txt
//	//l initialize the maximum array to these values.
//	//refert o a3 read file?
//	FILE *in = fopen("sample4_in.txt", "r");
//	fclose(in);
//	/*
//	 * 	FILE *in = fopen(fileName, "r");
//	 if (!in) {
//	 printf(
//	 "Child A: Error in opening input file...exiting with error code -1\n");
//	 return -1;
//	 }
//
//	 struct stat st;
//	 fstat(fileno(in), &st);
//	 char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
//	 fileContent[0] = '\0';
//	 while (!feof(in)) {
//	 char line[100];
//	 if (fgets(line, 100, in) != NULL) {
//	 strncat(fileContent, line, strlen(line));
//	 }
//	 }
//	 fclose(in);
//	 */
//
//	printf("Number of Customers: %d", n);
//	printf("Currently Available resources: 10 5 7 8"); //10 5 7 8 from file
//	printf("Maximum resources from file:"); //contents of file-print line by line
//
//	/*
//	 *  run a loop (user enters Exit to stop its execution)
//	 *   and would take user enter
//	 commands for responding to request of resources, release of resources, the current values of the
//	 different data structures, or find the safe sequence and run each thread. The program should take
//	 the following commands:
//	 *
//	 */
//
//	/*
//	 * <RQ [int customer_number] [int Resource 1] [int Resource 2] ... [int
//	 Resource 4]>:
//
//	 RQ command is used for requesting resources
//	 (remember threads cannot
//	 request more than maximum number of resources for that thread).
//
//	 If the request leaves the
//	 system unsafe it will be denied. If the system state is safe, the resources would be allocated
//	 and a message "State is safe, and request is satisfied" would be printed.
//	 */
//
//	//eg RQ 0 1 0 0 1 //customer/thread 0 were to request the resources (1, 0, 0, 1),
//	while (1) { //(!"Exit"){	}
//		printf("Enter Command:");
//
//		if (strncmp(command, temp) == 0) {
//			//if (strncmp(command, "RQ") == 0) { //(command == "RQ") {
//			//if "RQ" {request.
//			//if customer_number>maximum: invalid} {else
//			printf("State is safe, and request is satisfied");
//
//			/*
//			 * <RL [int customer_number] [int Resource 1] [int Resource 2] ... [int
//			 Resource 4]>:
//			 RL command would release the resources and data structures would be
//			 updated accordingly. It would print
//			 The resources have been released
//			 successfully
//			 */
//
//			//eg RL 4 1 0 0 0 // customer 4 wishes to release the resources (1, 0, 0, 0),
////if command == "RL"{release}
//		} else if (command == "RL") {
//			printf("The resources have been released successfully");
//
//			/*
//			 * <Status>:
//			 * Status command would print all arrays and matrices used
//			 (available, maximum, allocation, and need).
//			 *
//			 */
//			//if (command == "Status"){print}
//		} else if (command == "Status") {
//			printf("%d", available); //array ? traverse?
//			printf("%d", maximum);
//			printf("%d", allocation);
//			printf("%d", need);
//
//			/*
//			 <Run>:
//			 Run command executes customers as threads in a safe sequence. Each thread
//			 requests the resources it needs, releases them, and lets the next thread in the sequence run.
//			 */
//		} else if (command == "Run") {
//			;
//
////if (command == "Run"){executes}
//			/*
//			 * <Exit>: The Exit command is used to exit the loop and the program
//			 */
//
//		} else if (command == "Exit") {
//			break;
////if (command == "Exit"){break;}
//			/*
//			 * If user enters a wrong command, then a message, Invalid input, use one of RQ, RL,
//			 Status, Run, Exit, must be displayed and the correct command must be asked.
//			 *
//			 */
//		} else {
//			printf("Invalid input, use one of RQ, RL, Status, Run, Exit");
//		}
//	} //end while
//}
//
//void* threadRun(void *t) {
//	printf("Thread has started/n");
//	printf("Thread has finished/n");
//	printf("Thread is releasing resources/n");
//
////New Available status.
//	pthread_exit(0);
//}
