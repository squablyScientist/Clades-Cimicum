# Clades Cīmicum (i.e. 'Bane of Bugs')
This program is a simple, extremely rudimentary debugger that I've written to better understand interprocess memory management on Unix systems.
At the moment, the program can take in a PID, and a memory address, and provided that the memory at that address is allocated, spits out the memory at that address, in the virtual memory of the process whose ID was specified. It avoids race conditions by signalling utilizing signal.h to SIGSTOP and SIGCONT the target process. These features will be expanded upon in the near future.

## Compilation
To compile the program simply run:
```sh
make
```
## Usage
Using this program is relatively simple, the usage statement is as follows:
```sh
sudo clades-cimicum PID memory_offset length 
```
Where PID is the PID of the target process, memory_offset is the memory address that you wish to be read(in hexadecimal, at the moment sans '0x'), and length is the number of bytes that you wish to be read and subsequently printed. 

The necessity to run as a super user is (hopefully) temporary.

## Demoing 
The demo of the program is slightly finicky due to GDB, but it works. The steps
to take to demo the program are as follows:

1. Compile the relevant code. This is done with the following command: 
```sh
make && make captcha
```
1. Launch GDB in the same directory and wait until it reaches a point where you
appear to be prompted by `>>` to input the answer.
1. In a separate terminal, but still in the same directory, run the following
command to both print out the correct answer and inject that answer into the
captcha process:
```sh
sudo debugger PID `./getAddress.sh gdb.txt` num_of_bytes
```
Note: There is a bug in the captcha code where the number of digits displayed
is not always consistant, so make sure the num_of_bytes is 4 * the number of
digits. It should be 4 digits the majority of the time.
Other Note: To find the PID, it is suggested that `pgrep captcha` is used to
streamline the process
1. And you're done! The correct answer should be displayed in integers and also
   be injected into the sdtin of the captcha process!

## Credit
This branch of the repo contains code written by other people for the purpose of
demonstration. That code is in the file `captcha.c`. The original is hosted on
Github as `src/main.c` in the repo
[MNIST_ASCII_challenge](https://github.com/scvalencia/MNIST_ASCII_challenge).

