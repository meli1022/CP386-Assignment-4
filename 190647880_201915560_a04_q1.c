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
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include <sys/stat.h>

typedef struct customer
{
	int resource[4]; // can have up to 5 resources for the customer

} Customer;

int readFile(char* fileName,Customer** customer ){

	FILE *in = fopen(fileName, "r");
		if (!in) {
			printf("Error in opening input file...exiting with error code -1\n");
			return -1;
		}

	struct stat st;
	fstat(fileno(in), &st);
	char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';

	while(!feof(in))
	{
		char line[100];
		if(fgets(line,100,in)!=NULL)
		{
			strncat(fileContent,line,strlen(line));
		}
	}
	fclose(in);

	char *command = NULL;
	int customerCount = 0;
	char *fileCopy = (char*) malloc((strlen(fileContent) + 1) * sizeof(char));
	strcpy(fileCopy, fileContent);
	command = strtok(fileCopy, "\r\n");

	while(command!=NULL){
		customerCount++; // counting of customers and increment by 1
		command = strtok(NULL,"\r\n");
	}
	*customer = (Customer*)malloc(sizeof(customer) * customerCount);

	char *lines[customerCount];
		command = NULL;
		int i = 0;
		command = strtok(fileContent, "\r\n");

	while (command!=NULL){
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

				if (j == 0)
					(*customer)[k].resource[0] = atoi(token); //set resource number for resource 1 in index 0
				else if (j == 1)
					(*customer)[k].resource[1] = atoi(token); //set resource number for resource 2 in index 1
				else if(j == 2)
					(*customer)[k].resource[2] = atoi(token); // set resource number for resource 3 in index 2
				else if(j == 3)
					(*customer)[k].resource[3] = atoi(token); // set resource number for resource 4 in index 3
				else if(j == 4)
					(*customer)[k].resource[4] = atoi(token); // set resource number for resource 5 in index 4
				token = strtok(NULL, ",");
				j++;
			}
	}


	return customerCount;
}




void* threadRun(void *t); //the thread function, the code executed by each thread

//banker's algorithm.



int main(int argc, char *argv[]) {

	Customer *customer = NULL;

	int numofCustomers = readFile("sample4_in.txt",&customer);


	//all arrays/matrix...
	int available = 0; //array
	//available amount of each resource
	int maximum = 0; // maximum demand of each customer //array? array size?

	int allocated = 0; //amount currently allocated to each customer
	int need = 0; //remaining need of each customer

	printf("%d %d %d %d", available, maximum, allocated, need);

	char commands[20];


	printf("Number of Customers: %d\n", numofCustomers);
	printf("Currently Available resources: 10 5 7 8 \n"); //10 5 7 8 from file
	printf("Maximum resources from file:\n" ); //contents of file-print line by line
	for (int i=0; i <5; i++){

		printf("%d,",customer[i].resource[0]);
		printf("%d,",customer[i].resource[1]);
		printf("%d,",customer[i].resource[2]);
		printf("%d",customer[i].resource[3]);

		printf("\n");


	}
	//// safety algorithm
	//, if it leaves the system in a safe state,otherwise will deny it.

	while (1) {
		//input
		printf("Enter Command: ");
		scanf("%s", commands);

		if (strcmp(commands, "RQ") == 0) { //compare
			//	eg RQ 0 1 0 0 1 //customer/thread 0 were to request the resources (1, 0, 0, 1),

			////if customer_number>maximum: invalid} {else
			printf("State is safe, and request is satisfied\n");

		} else if (strcmp(commands, "RL") == 0) {
			//eg RL 4 1 0 0 0 // customer 4 wishes to release the resources (1, 0, 0, 0),

			printf("The resources have been released successfully\n");

		} else if (strcmp(commands, "Status") == 0) {
			;
			/*

			 * Status command would print all arrays and matrices used
			 (available, maximum, allocation, and need).
			 *
			 */
		} else if (strcmp(commands, "Run") == 0) {
			;
			/*

			 Run command executes customers as threads in a safe sequence. Each thread
			 requests the resources it needs, releases them, and lets the next thread in the sequence run.
			 */
		} else if (strcmp(commands, "Exit") == 0) {
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
