# Paging Simulation

This program creates 1000 random numbers between 0 and 9 which serve as a list of page references.

To compile my program for Lab 2 you must execute this command:

`gcc lab2.c queue.h  -o paging`

The file lab2.c drives the program and simulates the paging, queue.h contains the data structure for the paging and the functions for interacting with the structure.

To run the program execute:

`./paging`

You will then be prompted to enter the number of page frames you want to simulate. Enter the number of frames you desire.

Next you will be asked to choose between which eviction algorithm you want to use in your simulation: FIFO (0), LRU (1), Second Chance (2). To choose first in first out enter 0, to choose least recently used enter 1, to choose second chance enter 2.

Finally the paging will be simulated and the total number of hits, misses, and evictions will be printed. The total number of references for each page number will also be printed.
