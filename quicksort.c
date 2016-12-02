#include <stdio.h>
#include <stdlib.h>

//swaps two pointer values
void swap(int* A, int* B){
	int temp = *A;
	*A = *B;
	*B = temp;
}

int partition(int* A, int begin, int end){
	int pivotIndex = begin + ((end-begin)/2);
	int pivot = A[pivotIndex];
	swap(A+pivotIndex,A+end);
	//swap pivot to end
	int i = begin;
	int j = end;
	--end;
	while(begin <= end){
		if(A[begin] >= pivot && A[end] < pivot){
			swap(A+begin, A+end);
		}
		if(A[begin] < pivot) ++begin;
		if(A[end] >= pivot) --end;
	}
	//swap pivot back in place
	for(i; i<j; ++i){
		if(A[i]>A[j]){
			swap(A+i,A+j);
			break;
		}
	}
	return i;
}

/*quicksort(): in-place implementation of quick sort
Partitioning and finding a pivot point is done with partition()
While running in an infinite while loop, use a small array of indexes to keep track of partitions.
In array, numbers are placed in this order as number ofpartitions grow:{begin1, end1, begin2, end2,...,begin(n), end(n)}
The index for this array is incremented/decremented by 2 when going up/down (simulating returning from recursion)
*/
void quicksort(int* A, int begin, int end){
	int partitionIndex[1000]; //Note: Real simulator will have pretty much infinite storage, so remember to 'replace' the 1000.
	int pivot, temp, i, indexPos = 0;
	//Initialize partitionIndex + pivot to begin loop iterations
	partitionIndex[0] = begin;
	partitionIndex[1] = end;
	while(indexPos >= 0){
		//read next partition to sort
		begin = partitionIndex[indexPos];
		end = partitionIndex[indexPos+1];
		pivot = partition(A, begin, end);
		//Base case: Partition has only one number
		if(end-begin==0){
			indexPos -= 2;
			//~ printf("\n");
			continue;
		}
		//Base case: Partition has two numbers
		if(end-begin==1){
			if(A[begin]>A[end]){
				//Swap the two
				//~ printf("Swapped %d and %d\n", A[begin], A[end]);
				swap(A+begin, A+end);
			}
			indexPos -= 2;
			continue;
		}
		//Else, find pivot and partition
		pivot = partition(A, begin, end);
		//place partitions in a stack to be sorted later; smaller one to reduce stack size
		if(pivot-begin>=end-pivot){
			partitionIndex[indexPos] = begin;
			partitionIndex[indexPos+1] = pivot-1;
			partitionIndex[indexPos+2] = pivot;
			partitionIndex[indexPos+3] = end;
		}else{
			partitionIndex[indexPos] = pivot;
			partitionIndex[indexPos+1] = end;
			partitionIndex[indexPos+2] = begin;
			partitionIndex[indexPos+3] = pivot-1;
		}
		indexPos+=2;
	}
}

int main(){
	int N = 100000;
	int numberArray[N];
	int i;
	for(i = 0; i < N; ++i){
		numberArray[i] = lrand48();
	}
	quicksort(numberArray,0,N-1);
	for(i = 1; i < N; ++i){
		if(numberArray[i-1]>numberArray[i]){
			printf("incorrect!\n");
			break;
		}		
	}
}
