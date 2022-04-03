/*
 ------------------------------
 Authors: Melissa Pinto
 Phoebe Shulman
 IDs:	190647880
 201915560
 Github: https://github.com/meli1022/CP386-Assignment-4
 ------------------------------

 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

typedef struct h {

	//find
	int size;
	int start;
	int end;

} Hole;

typedef struct p {
	//inputed
	char name;
	int size;

	//find
	int start;
	int end; //end = start + size

} Process;

int main(int argc, char *argv[]) {
	int MAX = atoi(argv[1]);

	Process *processess = NULL;
	Hole *holes = NULL;

	int numProcesses = 0, numHoles = 1;
	int totalProcessesSize = 0, totalHolesSize = MAX; //add up all lens

	processess = (Process*) malloc(sizeof(Process) * 20); //* numProcesses);
	holes = (Hole*) malloc(sizeof(Hole) * 20); //* numHoles);

	//first hole in memeory- 1 big hole
	(holes)[numHoles - 1].start = 0;
	(holes)[numHoles - 1].end = MAX; //- 1;
	(holes)[numHoles - 1].size = (holes)[0].end - (holes)[0].start;

	printf("Allocated %d bytes of memory\n", MAX);

	char commands[20]; //inputs
	char name[100];
	int size;
	char algo[100];

	while (1) { //program loop

		//input

		printf("command>");
		scanf("%s", commands);

		if (strcmp(commands, "RQ") == 0) { //command =RQ
			/* RQ <process number> <size> <B>:
			 * RQ command is the new process that requires the memory,
			 followed by the amount of memory being requested,
			 and finally the algorithm.  (B refers to best fit.)
			 //RQ P0 20000 B //request for 20,000 bytes
			 *
			 */

			//get other inputs
			scanf("%s", name);
			scanf("%d", &size);
			scanf("%s", algo);

			//best fit algo:================
			int isFit = 0;
			int bestHoleIndex = 0;
			int min = MAX + 1;

			//travesr - find smallest hole size
			for (int i = 0; i < numHoles; i++) { //numHoles - 1?

				if ((holes)[i].size < min && (holes)[i].size >= size) { //is min and fits
					min = (holes)[i].size;
					bestHoleIndex = i; //find best hole

					isFit = 1; //found a hole
				}

			}

			//printf("bestHoleIndex%d\n", bestHoleIndex); //put the process in here

			if (isFit == 1) { //if can fit //add to processess

				//pname = name. psize = size. pstart = hole start. pend = p start + p size

				strcpy(&(processess)[numProcesses].name, name); //	&(processess)[numProcesses].name = name;
				(processess)[numProcesses].size = size;

				(processess)[numProcesses].start = holes[bestHoleIndex].start;

				(processess)[numProcesses].end =
						(processess)[numProcesses].start
								+ (processess)[numProcesses].size;

				printf("Successfully allocated %d to process %s\n",
						(processess)[numProcesses].size,
						&(processess)[numProcesses].name);

				//update totla sizes
				totalProcessesSize += size;
				totalHolesSize -= size;

//update best hole
				(holes)[bestHoleIndex].size -= size;
				(holes)[bestHoleIndex].start = (processess)[numProcesses].end; //hole pushed over. to start where process ends

				//(holes)[bestHoleIndex].end = next process start //this makes last output wrong..
				// find where next hole start or next process starts? proces[num +1]? //= max or to process[1].start
				if ((processess)[numProcesses + 1].start > 0) { //if theres a process after. end = start of next process

					(holes)[bestHoleIndex].end =
							(processess)[numProcesses + 1].start;
				} else { //no process after the hole
					(holes)[bestHoleIndex].end = MAX;
				}

				numProcesses += 1; //process was added

			} else {
				printf("No hole of sufficient size\n");
			}

		} else if (strcmp(commands, "RL") == 0) {

			/*
			 * RL <process number/name>:
			 * RL command will release the memory that has been
			 allocated to a process (e.g., P0).
			 *
			 * //RL P0 //eg
			 */

			//get other inputs
			scanf("%s", name);

			printf("releasing memory for process %s\n", name);

			//update process areaay and hole arrays 

			for (int i = 0; i < numProcesses; i++) {
				if (strcmp(&(processess)[i].name, name) == 0) { //if found name

					//make a new hole- the exact size of it
					numHoles += 1;

					(holes)[numHoles - 1].size = (processess)[i].size; //(processess)[numProcesses - 1].size;

					(holes)[numHoles - 1].start = (processess)[i].start;

					(holes)[numHoles - 1].end = (processess)[i].end; //- 1;

					// if another hole right after it- combine into 1 hole?hole count - 1

//					if ((holes)[numHoles].end == (holes)[numHoles - 1].start) {
//						//if ((holes)[numHoles - 1].end == (holes)[numHoles].start) { //this hole starts where next hole ends
//						numHoles -= 1;
//						//change hoes start = num hoels -1 start
//						(holes)[numHoles - 1].start = (holes)[numHoles].start;
//						//(holes)[numHoles].start = (holes)[numHoles - 1].start;
//					}

					//change totla sizes
					totalProcessesSize -= (processess)[i].size; //size;
					totalHolesSize += (processess)[i].size; //size;

					//empty process
					strcpy(&(processess)[i].name, "null"); //	&(processess)[numProcesses].name = name;
					(processess)[i].size = 0;

					(processess)[i].start = 0;
					(processess)[i].end = 0;

					//numProcesses -= 1;

					//break;///jsut need 1?

				}
			}

			printf("Successfully released memory for process %s\n", name);

		} else if (strcmp(commands, "Status") == 0) {

			/*
			 Status: The Status command used for reporting the status of memory is entered.
			 */

			printf("Partitions [Allocated memory = %d]:\n", totalProcessesSize);

			//loop num processes
			for (int i = 0; i < numProcesses; i++) {

				if (strcmp(&(processess)[i].name, "null") != 0) { //not released
					printf("Address [%d:%d] Process %s\n",
							(processess)[i].start, (processess)[i].end - 1,
							&(processess)[i].name);
				}
			}

			printf("\n");

			//loop num holes
			printf("Holes [Free memory = %d]:\n", totalHolesSize);

			for (int i = 0; i < numHoles; i++) {

				printf("Address [%d:%d] len = %d\n", (holes)[i].start,
						(holes)[i].end - 1, (holes)[i].size);

			}

		} else if (strcmp(commands, "Exit") == 0
				|| strcmp(commands, "q") == 0) {
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
