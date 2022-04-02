/*
 ------------------------------
 Authors: Melissa Pinto
 Phoebe Shulman
 IDs:	190647880
 201915560
 Github: https://github.com/meli1022/CP386-Assignment-4
 ------------------------------

 */

//why is invalid command?--algo not getting input?
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

//best fit algo
/*
 *
 * start off as 1 giant whole?
 * as process come in - fill it up
 *
 * eg
 * 0 to 200
 * 200 to 500
 * 500 to 700
 *
 * but realase process ->eg
 *  * 0 to 200
 * h1 = start - size?
 * 500 to 700
 *
 *----
 *----Allocated memory = sum of sizes
 *Address [start:start+size] Process P1
 * //how to rember each?- start matrxi and size matrix?

 Holes = max - allocated
 Address [0:199999] len = 200000 //holde start: hold start + hole size-1. lne = hole size
 //how detect hole- if not between process starta nd edn?
 *
 */

// track of which region of memory has been allocated to which process
//. If a partition being released is adjacent to an existing hole, be sure to combine the two holes into a single hole
int main(int argc, char *argv[]) {
	int MAX;
//	MAX = 1000000;
	MAX = atoi(argv[1]);

	char commands[20];
	char p1[20];

	int totalHoles = MAX;
	int totalAllocated = 0;
	//maybe 1 big matrxi? each elem. 0 or 1 if hole ornot?-prob not

	char processNames[100][100];
	int processStarts[100];
	int processSize[100];
	int holeStarts[100];
	int holeSize[100];
	int processCounter = 0, holeCounter = 1;

	holeStarts[0] = 0; //starts from 0 . upt to max
	holeSize[0] = MAX; //start with block s of memeroy ?

	int min, start;
	printf("Allocated %d bytes of memory\n", MAX);

	while (1) { //program loop

		//input
		printf("command>");
		scanf("%s", commands);

		if (strcmp(commands, "RQ") == 0) { //command =RQ
			/* RQ <process number> <size> <B>:
			 * RQ command is the new process that requires the
			 memory,
			 followed by the amount of memory being requested,
			 and finally the algorithm.  (B refers to best fit.)
			 //RQ P0 20000 B //request for 20,000 bytes
			 *
			 */

			//get other inputs
			char processNumber[20];
			scanf("%s", processNumber);
//
//			char processNumber[20];
//						scanf("%s", &processNames[processCounter]);
//
			scanf("%s", p1);
			int size = atoi(p1);

//			char algorithm; //[20]; //... //maybe ingore for now?
//			scanf("%c", &algorithm); //c //not getting input?/

			//scanf("%s", &algorithm); //c
			//printf("%c", algorithm);
			//printf("%s", algorithm);

//best fit algo:
			int isFit = 1;

			if (isFit == 1) {
				//added to processess
				//processNames[processCounter] = processNumber;
				//travesr - find smallest hole size

				min = MAX + 1; //for holesizes:put in it
				start = 0;

				for (int i = 0; i < holeCounter; i++) {
					if (holeSize[i] < min) {
						min = holeSize[i];
						start = i; //holestarts[i]?
					}

				}
				processStarts[processCounter] = start; //i; //0; //have to traverse to find wher can start and fully fit
				processSize[processCounter] = size;
				processCounter += 1;

				//check holes
				//update hole-split if need

				totalAllocated += size;
				totalHoles -= size;
				printf("Successfully allocated %d to process %s\n", size,
						processNumber); //200000 -var,P0 -var
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
			char processNumber[20];
			scanf("%s", processNumber);

			printf("releasing memory for process %s\n", processNumber); //"P0");
			//realse
//update process areaay and hole arrays //eg remove form lists?

			printf("Successfully released memory for process %s\n",
					processNumber);

		} else if (strcmp(commands, "Status") == 0) {
			;
			/*

			 Status: The Status command used for reporting the status of memory is entered.
			 */

			printf("Partitions [Allocated memory = %d]:\n", totalAllocated); //650000);

			//loop?-num processes
			for (int i = 0; i < processCounter; i++) {
				printf("Address [%d:%d] Process %s\n", processStarts[i],
						processStarts[i] + processSize[i] - 1, processNames[i]); //200000, 549999, "P1");
			}

			printf("\n");

			printf("Holes [Free memory = %d]:\n", totalHoles); //350000);
			//looops?//num holes..//combine holes if they next to each other?
			for (int i = 0; i < holeCounter; i++) {
				printf("Address [%d:%d] len = %d\n", holeStarts[i],
						holeStarts[i] + holeSize[i] - 1, holeSize[i]);
				//0, 199999, 200000);
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
