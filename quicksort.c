#include <stdio.h>
#include <stdlib.h>

//haven't tested swap()
void swap(int* A, int* B){
	int temp = *A;
	*A = *B;
	*B = temp;
}

int partition(int* A, int begin, int end){
	pivotIndex = begin + ((end-begin)/2);
	pivot = A[pivotIndex];
	while(begin <= end){
		if(A[begin] >= pivot && A[end] < pivot){
			swap(A[begin], A[end]);
		}
		if(A[begin] < pivot) begin++;
		if(A[end] >= pivot) end--;
	}
	return begin;
}

/*quicksort(): in-place implementation of quick sort
Uses select() to find a pivot point such that partitioning on both sides of the pivot only needs O(logn) memory.
Partitioning is done with partition()
While running in an infinite while loop, use a small array of indexes to keep track of partitions.
In array, numbers are placed in this order as number ofpartitions grow:{begin1, end1, begin2, end2,...,begin(n), end(n)}
The index for this array is incremented/decremented by 2 when going up/down (simulating returning from recursion)
*/
void quicksort(int* A){
	int partitionIndex[1000]; //Note: Real simulator will have pretty much infinite storage, so remember to 'replace' the 1000.
	int pivot, temp, i, indexPos = 0, begin = 0, end = len(A)-1;
	//Initialize partitionIndex + pivot to begin loop iterations
	partitionIndex[0] = begin;
	partitionIndex[1] = end;
	while(indexPos >= 0){
		//read next partition to sort
		begin = partitionIndex[indexPos];
		end = partitionIndex[indexPos+1];
		//Base case: Partition has only one number
		if(end-begin==0){
			posIndex -= 2;
			continue;
		}
		//Base case: Partition has two numbers
		if(end-begin==1){
			if(A[begin]<A[end]){
				//Swap the two
				temp = A[begin];
				A[begin] = A[end];
				A[end] = temp;
			}
			posIndex -= 2;
			continue;
		}
		//Else, find pivot and partition
		pivot = partition(A, begin, end);
		//place partitions in a stack to be sorted later; smaller one to reduce stack size
		if(pivot-begin>=end-pivot){
			partitionIndex[posIndex] = begin;
			partitionIndex[posIndex+1] = i-1;
			partitionIndex[posIndex+2] = i+1;
			partitionIndex[posIndex+3] = end;
		}else{
			partitionIndex[posIndex] = i+1;
			partitionIndex[posIndex+1] = end;
			partitionIndex[posIndex+2] = begin;
			partitionIndex[posIndex+3] = i-1;
		}
		posIndex+=2;
	}
}
