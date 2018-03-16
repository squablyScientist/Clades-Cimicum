//TODO: implement an output format choice
//TODO: add autocompletion for the names of processes
//TODO: allow for '0x' at the beginning of memory address
//TODO: add getopt options for various output formatting

/*
 * Clades Cīmicum : Bane of Bugs
 *
 * A small, rudimentary interprocess debugger that can stop anoter process given
 * a PID, read, and output a piece of memory from that process. 
 *
 * Author: Collin Tod
 */
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

void usage(void){
	fprintf(stderr, "Usage: debugger <PID> <mem_offset> <length>\n");
}

int readmemory(char *buf, pid_t pid, long offset, size_t length){

	char memfilename[32];

	// Generates the filename of the process's mem file.
	sprintf(memfilename, "/proc/%d/mem", pid);

	// Opens the mem file 
	FILE *memfile = fopen(memfilename, "r");

	// Make sure that the file was properly opened.
	if(errno){
		perror("fopen");
		return 1;
	}

	// Stops the process temporarily to avoid race conditions.
	kill(pid, SIGSTOP);

	/*
	 * Seek to the correct offset in the file
	 * It is very important that the memory at offset is actually mapped. If
	 * it is not mapped in the other process, then reading from the
	 * /proc/PID/mem file will result in an EIO (i.e. an Input output error).
	 */
	fseek(memfile, offset , SEEK_SET);

	// Reads a certain number bytes from the mem file
	fgets(buf, length+1, memfile);

	// Makes sure that the read from the mem file was successful
	if(errno){
		perror("fgets");
		return 1;
	}

	// Close the memory file; it is no longer needed
	fclose(memfile);

	//TODO: Find a way to do this that doesn't mess with SIGINT later
	// Continues the process since it no longer needs to be stopped
	kill(pid, SIGCONT);

	return 0;
}

int main(int argc, char **argv){

	// Makes sure that the correct number of clargs was entered
	if(argc != 4){
		usage();
		return EXIT_FAILURE;
	}

	pid_t pid = (pid_t)strtol(argv[1], NULL, 10);
	long offset = strtol(argv[2], NULL, 16);
	int length = (int)strtol(argv[3], NULL, 10);

	char buf[length+1]; //The buffer that will hold the memory read in 

	// Reads the memory and makes sure that it was successful. If it wasn't exit
	if(readmemory(buf, pid, offset, length) != 0){
		return EXIT_FAILURE;
	}

	//TODO: make this able to handle different formats than just integers.
	// Prints out the memory read from the file
	
	printf("Memory at %p: ", offset);
	for(int i = 0; i < length; i++){
		printf("%d", buf[i]);
	}
	printf("\n");

	return 0;

}
