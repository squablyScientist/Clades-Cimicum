# Opens the binary file for the captcha program
file captcha

# Sets a breakpoint at a location in the program that will yield easy access to 
# an array that holds the entire answer in integers via the stack pointer
break receive_CAPTCHA

# Runs the program
run 4 4 -b -d

# Prepares the program for logging
set logging file gdb.txt
set logging on
set logging overwrite on

# Retrieve information from the current frame. The previous frame's stack
# pointer is currently pointing exactly at the answer, so we need to be able
# to know it's address. That's what the logging was for, this command prints
# all of that information to the log file.
info frame

# Logging is no longer needed
set logging off
continue
continue
