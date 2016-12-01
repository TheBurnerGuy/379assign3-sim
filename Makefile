# Makefile Usage:
# make : compile programs
# make client
# make server
# make clean



all:
	gcc -o h heapsort.c

clean:
	rm -rf *~ 