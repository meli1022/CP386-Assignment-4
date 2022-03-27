# CP386-Assignment-4

## Project:
This program implements the banker's algorithm and best-fit algorithm. 

## Makefile:
The purpose of the makefile file is to easily build an executable that might take many commands to create. To use the makefile, type `make runq1` or `make runq2` to execute each program in terminal.

## Features:
**The features of the banker algorithm program and best fit algorithm include:**

RQ - Request resources to fill allocation array
```
Enter Command: RQ 1 2 3 4 5
```
RL - Release Resources and update data structures
```
Enter Command: RL 1 1 1 1 1
```
Status - Display current state
```
Enter Command: Status
```
Run - Exectute threads in a safe sequence
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
Phoebe - 
'int testing()'

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
The license for this program is GNU GPLv3 which lets people to do almost anything they want with our project, except distributing closed source versions. [GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0)

## Developers
- [Melissa Pinto](https://github.com/meli1022)
- [Phoebe Shulman](https://github.com/Phoebe-S-9)



