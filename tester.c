/*
 * tester.c: A program that simply loops forever, holding a piece of memory that
 * can be changed and easily accessed by memory address. The purpose of this
 * program is to provide a simple testing ground for debugger.c, i.e. a program
 * with an easily identifiable memory segement that can be quickly identified as
 * correct or not, and a way to show if the process has been stopped or not.
 * Author: Collin Tod
 *
 * TODO: Add automatic addr dumping once memory is allocated
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	//These two lines are the memoryplant that will be searched for. The address
	//of this memory is in the file memoryplantaddr.txt
	int *memoryplant = malloc(sizeof(int));
	*memoryplant = argc;

	while(1){
		printf("Running\n");
	}

	free(memoryplant);
	return 0;
}
