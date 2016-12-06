# Makefile Usage:
# make process : compile programs
# make clean : clean programs




simulator: ${PROCESS}.c simulator.c simulator.h
	gcc simulator.c ${PROCESS}.c -o ${PROCESS}

clean:
	rm -rf *~ *.o  heapsort quicksort quicksortv2

