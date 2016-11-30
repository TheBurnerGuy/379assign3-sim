#include <stdio.h>
#include <stdlib.h>

int select(int* L, int begin, int end, int k){
    if (L<=10){
        //sort L
        
        return L[k]; //return the element in the kth position
    }

    partition L into subsets S[i] of five elements each
        (there will be n/5 subsets total).

    for (i = 1 to n/5) do
        x[i] = select(S[i],3)

    M = select({x[i]}, n/10)

    partition L into L1<M, L2=M, L3>M
    if (k <= length(L1))
        return select(L1,k)
    else if (k > length(L1)+length(L2))
        return select(L3,k-length(L1)-length(L2))
    else return M
}

//haven't tested swap()
void swap(int* A, int* B){
	int temp = *A;
	*A = *B;
	*B = temp;
}

int partition(int* A, int begin, int end, int pivot){
	
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
	int pivot, temp, i, j, indexPos = 0, begin = 0, end = len(A)-1;
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
		pivot = select(A, begin, end, begin + ((end-begin)/2));
		//For now, assume select partitions everything nicely, that is all the values that coresspond to the pivot are grouped together
		//Find an index with pivot
		for(i = begin; i <= end; i++){
			if(A[i] == pivot) break;
		}
		//Swap pivot to end
		temp = A[i];
		A[i] = A[end];
		A[end] = A[i];
		//In-place Partition
		i = begin;
		j = end-1;
		while(i<j){
			while(A[i]<=pivot){
				i++
			}
			while(A[j]>=pivot){
				j--
			}
			if(i<j){
				//swap
				temp = A[i];
				A[i] = A[j];
				A[j] = A[i];
				i++;
				j--;
			}
		}
		//Find index to place pivot, and assign partitions to partitionIndex
		temp = 1; //In case this partition's piviot is mostly the same number
		for(i = begin; i <= end; i++){
			if(A[i]>pivot){
				temp = A[i];
				A[i] = A[end];
				A[end] = A[i];
				partitionIndex[posIndex] = begin;
				partitionIndex[posIndex+1] = i-1;
				partitionIndex[posIndex+2] = i+1;
				partitionIndex[posIndex+3] = end;
				posIndex+=2;
				temp = 0;
				break;
			}
		}
		if(temp) posIndex -= 2;
	}
}
