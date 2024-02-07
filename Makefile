#############################################
# Operation Systems, Lab 1, January 26th 2024
# Jason Manarroo | 100825106
# Ahmed Darwish  | 100754743
# Juliano Falotico | 100658311 
#############################################

# Default target
all: myshell

# Link the target with object files
myshell: myshell.o utility.o

# Compile source files into object files
myshell.o: myshell.c 

utility.o: utility.c utility.h

# Clean up
clean:
	rm -f myshell *.o

.PHONY: all clean
