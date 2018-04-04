#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int inject(pid_t pid, char *data){
	
	// A buffer for the file descriptor path 
	char fd_name[33];

	// Create the file descriptor path based on PID
	sprintf(fd_name, "/proc/%d/fd/0", pid);


	// Opens the file descriptor
	int target_stdin_fd = open(fd_name, O_WRONLY | O_APPEND);

	// Makes sure that open was successful
	if(errno){
		perror("open");
		return -1;
	}

	// Writes the requested data to stdin of target process
	write(target_stdin_fd, data, strlen(data));
	
	// Makes sure that write was successful
	if(errno){
		perror("write");
		return -1;
	}

	// Closes this processes hold on the file descriptor
	close(target_stdin_fd);

	return 0;
}	


