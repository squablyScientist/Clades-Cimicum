/**
 * This function injects the bytes in data into the stdin of the process that
 * currently hold the process id pid.
 *
 * pid: The id of the process to write to
 * data: The data to write to stdin. Should be null terminated
 * returns: 0 is successful, -1 otherwise.
 */
int inject(pid_t pid, char *data);
