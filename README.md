# Clades Cīmicum (i.e. 'Bane of Bugs')
This program is a simple, extremely rudimentary debugger that I've written to better understand interprocess memory management on Unix systems.
At the moment, the program can take in a PID, and an memory address, and provided that the memory at that address is allocated, spits out the memory at that address, in the virtual memory of the process whose ID was specified. It avoids race conditions by signalling utilizing signal.h to SIGSTOP and SIGCONT the target process. These features will be expanded upon in the near future.
