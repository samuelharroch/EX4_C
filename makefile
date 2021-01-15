  
CC = gcc
FLAGS = -Wall
.PHONY: all clear

all: frequency

frequency: frequency.c
	$(CC) $(FLAGS) frequency.c -o frequency

clean:
	rm frequency