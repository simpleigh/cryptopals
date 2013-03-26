# Variable definitions
CFLAGS := $(CFLAGS) -Wall -Wextra -std=c89 -pedantic

.PHONY : all clean

# Default target
all: crypto1 crypto2 crypto3

# Targets to build binaries
crypto1: crypto1.o conversions.o
	$(CC) $(CFLAGS) -o crypto1 $^

crypto2: crypto2.o conversions.o
	$(CC) $(CFLAGS) -o crypto2 $^

crypto3: crypto3.o conversions.o
	$(CC) $(CFLAGS) -o crypto3 $^

# Binary object files
crypto1.o: crypto1.c conversions.h
crypto2.o: crypto2.c conversions.h
crypto3.o: crypto3.c conversions.h

# Library object files
conversions.o: conversions.c conversions.h

clean:
	-rm *.o
	-rm crypto?
