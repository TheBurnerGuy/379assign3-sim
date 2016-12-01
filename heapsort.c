#include <stdio.h>
void heapify(int *a, int n);
void sort(int *a, int n);

int main(int argc, char* argv[]) {
	int mem[10];	 //represents 10 words in memory for put and get 
	int a[] = {7,9,1,4,8,3,10,6,2,1000,-5,666,5}; //array to be sorted
	int i=0;
	int n=13;    //count
	
	for (i=0; i<n; i++) {
		printf("%d, ", a[i]);
	}
	printf("\n\n");

	printf("{10}{9,7},{8,6,3,5},{1,6,2}\n"); //this just illustrates the leaves in the tree
	heapify(a, n); // max heap - parents are greater than their children

	for (i=0; i<n; i++) {
		printf("%d, ", a[i]);
	}
	printf("\n\n");

	sort(a, n);

	for (i=0; i<n; i++) {
		printf("%d, ", a[i]);
	}
	printf("\n\n");
}


void heapify(int *a, int n) {
    int i, swap, child, parent;
    for (i = n-1; i > 0; i--) {  //n-1 is index of end of array
        child = i;
        while (child > 0){
            parent = child / 2;         
             if (a[parent] < a[child])  { //if a parent node is smaller than a child, swap them
				swap = a[parent];
                a[parent] = a[child];
                a[child] = swap;
		}
		child = parent;
		} ;
	}
}

void sort(int *a, int n) {
	int  i, swap, child, parent;
    for (i = n - 1; i >= 0; i--){
        swap = a[0];
        a[0] = a[i];    //swap max element with rightmost leaf
        a[i] = swap;
        parent = 0;
        child = 1;
        while (child < i) {    
            if (a[child+1] > a[child] && child + 1 < i) child++; //if child is greater than its left sibling, move to the next child
			if (a[child] > a[parent] && child < i)  {  //if a child is bigger than its parent, switch them
                swap = a[parent];
				a[parent] = a[child];
				a[child] = swap;
			}
            parent = child;
            child = 2 * parent + 1;   
        } 
    } 
}

