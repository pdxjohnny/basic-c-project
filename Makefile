# The name of the output binary
SRC=plinko
# This sets the compiler to use. Most people use gcc clang is also another
# common compiler. It becomes the variable which can be accessed with $(CC)
CC=gcc
# These are the flags that get passed to $(CC)
CFLAGS=-g -O0 -ansi -pedantic -Wall
# These are linker flags only needed if using external libraries but we are not
# in this
LDFLAGS=
# This says to grab all the files with the c extension in this directory and
# make them the array called SRC_SOURCES
SRC_SOURCES=$(wildcard *.c)
# This makes an array of all the c files but replaces .c with .o
SRC_OBJECTS=$(SRC_SOURCES:.c=.o)

# This says run all when someone types `make hw1`
hw1: all

# When you run make then all is the default command to run. So running `make` is
# the same as running `make all`
all: $(SRC)

# This says to build $(SRC) then all the o files need to be present / up to
# date first. The way they get up to date is by compiling the c files in to
# their respective o files
$(SRC): $(SRC_OBJECTS)
	# The $@ variable gets replaced with $(SRC)
	$(CC) $(SRC_OBJECTS) $(LDFLAGS) -o $@

# This is the action that is run to create all the .o files, object files.
# Every c file in the array SRC_SOURCES is compiled to its object file for
# before being linked together
%.o:%.c
	$(CC) $(CFLAGS) $< -c

# Clean deletes everything that gets created when you run the build. This means
# all the .o files and the binary named $(SRC)
clean:
	@rm -f $(SRC) *.o *.tar

# This creates the tar file for submission
tar:
	tar cvf outputfile.tar $(SRC_SOURCES) Makefile
