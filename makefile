#############################################
# Operation Systems, Lab 1, January 26th 2024
# Jason Manarroo | 100825106
#############################################

# Default target
all: myshell

# Link the target with object files
myshell: myshell.o utility.o
	gcc -Wall -g -o myshell myshell.o utility.o

# Compile source files into object files
myshell.o: myshell.c 
	gcc -Wall -g -c myshell.c

utility.o: utility.c utility.h
	gcc -Wall -g -c utility.c

# Clean up
clean:
	rm -f myshell *.o

