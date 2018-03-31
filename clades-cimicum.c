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
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

void usage(void){
	fprintf(stderr, "Usage: debugger <PID> <mem_offset> <length>\n");
}

int byte_to_int(char *byte){
	
	int integer = byte[0] | (byte[1] << 8) | (byte[2] << 16) | (byte[3] << 24);

	return integer;
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

		// Makes sure that the program continues if reading failed
		kill(pid, SIGCONT);
		return 1;
	}

	// Close the memory file; it is no longer needed
	fclose(memfile);

	//TODO: Find a way to do this that doesn't mess with SIGINT later
	// Continues the process since it no longer needs to be stopped
	kill(pid, SIGCONT);

	return 0;

}

/**
 * Reads the memory at a certain address of another process utilizing the ptrace
 * system call rather than normal file IO. This function will print an error and
 * return a 1 if it is unsuccessful. The result of this function will be stored
 * at buf as contiguous bytes.
 *
 * @param buf: A char pointer that points to the location in which the memory
 * read from ptrace will be stored. It is important that at least length bytes
 * of memory are reserved there.
 * @param pid: The process id of the process whose memory is to be read
 * @param offset: The memory address of the first byte to be read
 * @param length: The number of bytes to read
 *
 * @return: 0 if the operation is successful, 1 otherwise.
 */
int ptraceMem(char *buf, pid_t pid, long offset, size_t length){
	// Attach to the tracee, stopping it temporarily to avoid race condition
	ptrace(PTRACE_ATTACH, pid, 0, 0);

	// Makes sure that the attaching was successful. If not report and exit
	if(errno){
		perror("attach");
		return 1;
	}

	// Reads length bytes and stores them at buf
	for(size_t i = 0; i < length; i++){

		*(buf + i)= ptrace(PTRACE_PEEKDATA, pid, offset + (long)i, 0);
	}


	// If there is an issue, report it, detach, and return
	if(errno){
		perror("peekdata");
		ptrace(PTRACE_DETACH, pid, 0, 0);
		return 1;
	}

	// Detach from the process, allowing normal operation to resume
	ptrace(PTRACE_DETACH, pid, 0, 0);

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
	
	printf("Memory at %p: ", (void*)offset);
	for(int i = 0; i < length; i++){
		printf("%d", buf[i] | (buf[i+1] << 8) | (buf[i+2] << 16) | (buf[i+3] << 24));
		i+=3;
	}
	printf("\n");

	return 0;

}
