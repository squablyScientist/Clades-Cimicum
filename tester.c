#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int *memoryplant = malloc(sizeof(int));
	*memoryplant = argc;

	while(1){
		printf("Running\n");
	}

	free(memoryplant);
	return 0;
}
