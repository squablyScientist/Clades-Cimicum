#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>


int main(int argc, char **argv){

	pid_t pid = (pid_t)strtol(argv[1], NULL, 10);
	long offset = strtol(argv[2], NULL, 16);

	kill(pid, SIGSTOP);

	char memfilename[32];

	sprintf(memfilename, "/proc/%d/mem", pid);
	FILE *memfile = fopen(memfilename, "r");

	// Make sure that the file was properly opened
	if(errno){
		perror("fopen");
		return 1;
	}

	char buf[33];

	// Seek to the correct offset in the file
	fseek(memfile, offset, SEEK_SET);

	fgets(buf, 32, memfile);

	if(errno){
		perror("fgets");
		return 1;
	}

	for(int i = 0; i < 4; i++){
		printf("%d", buf[i]);
	}
	kill(pid, SIGCONT);
	return 0;

}
