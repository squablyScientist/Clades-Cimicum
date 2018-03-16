//TODO: segment functionality
//TODO: implement an output format choice
//TODO: implement a choice for how many bytes to read
//TODO: add autocompletion for the names of processes
//TODO: allow for '0x' at the beginning of memory address
//TODO: add getopt options for various output formatting

/*
 * Clades Cīmicis : Bane of Bugs
 *
 * A small, rudimentary interprocess debugger that can stop anoter process given
 * a PID, read, and output a piece of memory from that process. 
 *
 * Author: Collin Tod
 */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

void usage(void){
	fprintf(stderr, "Usage: debugger <PID> <mem_offset>\n");
}

int main(int argc, char **argv){

	if(argc != 3){
		usage();
		return EXIT_FAILURE;
	}

	pid_t pid = (pid_t)strtol(argv[1], NULL, 10);
	long offset = strtol(argv[2], NULL, 16);

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

	char buf[33]; // Buffer for reading from the mem file

	// Stops the process temporarily to avoid race conditions.
	kill(pid, SIGSTOP);

	/*
	 * Seek to the correct offset in the file
	 * It is very important that the memory at offset is actually mapped. If
	 * it is not mapped in the other process, then reading from the
	 * /proc/PID/mem file will result in an EIO (i.e. an Input output error).
	 */
	fseek(memfile, offset, SEEK_SET);


	// Reads a certain number (right now 32) bytes from the mem file
	fgets(buf, 32, memfile);

	// Makes sure that the read from the mem file was successful
	if(errno){
		perror("fgets");
		return 1;
	}

	fclose(memfile);

	// TODO: make this more robust and able to handle different lengths of mem.
	// Prints out the memory read from the file
	for(int i = 0; i < 4; i++){
		printf("%d", buf[i]);
	}

	// Continues the process, as it no longer needs to be stopped
	kill(pid, SIGCONT);

	return 0;

}
