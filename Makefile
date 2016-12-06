# Makefile Usage:
# make process : compile programs
# make clean

quicksortv2:
	gcc -c quicksortv2.c



#$(process): simulator.c  simulator.h 
#	gcc simulator.c $(process).c  -o $(process)

clean:
	rm -rf *~ *.o $(process) heapsort quicksort

