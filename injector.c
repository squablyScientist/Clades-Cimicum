#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int inject(pid_t pid, char *data){
	
	char fd_name[33];

	sprintf(fd_name, "/proc/%d/fd/0", pid);

	int target_stdin_fd = open(fd_name, O_WRONLY | O_APPEND);

	if(errno){
		perror("open");
		return -1;
	}

	write(target_stdin_fd, data, strlen(data));
	
	if(errno){
		perror("write");
		return -1;
	}

	close(target_stdin_fd);
	return 0;
}	


