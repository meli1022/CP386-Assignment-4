# CP386-Assignment-4

## Project:
This program implements the banker's algorithm and best-fit algorithm. 

## Makefile:
The purpose of the makefile file is to easily build an executable that might take many commands to create. To use the makefile, type `make runq1` or `make runq2` to execute each program in terminal.

## Features:
**The features of the banker algorithm and best-fit algorithm programs include:**

RQ - Request resources to fill allocation array **(Q1)**
```
Enter Command: RQ 1 2 3 4 5
```
RQ - Request memory block allocation ("process number" + "size" + "B") **(Q2)**
```
command>RQ P0 20000 B
```
RL - Release resources and update data structures **(Q1)**
```
Enter Command: RL 1 1 1 1 1
```
RL - Release the memory that has been allocated to a process ("process number/name") **(Q2)**
```
command>RL P0
```
Status - Display current state
```
Enter Command: Status
```
Run - Exectute threads in a safe sequence **(Q1)**
```
Enter Command: Run
```
Exit - Exit out of program
```
Enter Command: Exit
```

## Contribution:
Melissa - 
`int readFile(char* fileName,Customer** customer)`
`README.md`
Phoebe - 
`void* threadRun(void *t); `
`int main(int argc, char *argv[]) `

## Test Case Q1:
`RQ 0 1 0 0 1`
`RQ 1 1 1 1 1`
`RQ 2 2 2 2 2`
`RQ 3 1 1 1 1`
`RQ 4 1 0 0 0`

## Test Case Q2:
`RQ P0 200000 B`
`RQ P1 350000 B`
`RQ P2 300000 B`
`RL P0`
`RQ P4 150000 B`
`RQ P5 80000 B`

## License:
The license for this program is [GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0) which lets people to do almost anything they want with our project, except distributing closed source versions.

## Developers
- [Melissa Pinto](https://github.com/meli1022)
- [Phoebe Shulman](https://github.com/Phoebe-S-9)



