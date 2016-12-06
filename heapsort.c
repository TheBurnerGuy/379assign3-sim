#include <stdio.h>
#include <stdlib.h>


void swap(int A, int B){
	int temp = get(A);
	put(A, get(B));
	put(B,temp);
}




void heapify(int n) { //create a max heap
    int i, child, parent;
    for (i = 1; i < n; i++) { 
        child = i;
        do {
        	parent = (child - 1) / 2;
            if (get(parent) < get(child))  { //if a parent node is smaller than a child, swap them
             	swap(parent, child);  				          
			} 
			child = parent;       	
		} while (child > 0);
	}
}

void sort(int n) {
	int  i, child, parent;
    for (i = n-1; i > 0; i--){
    	swap(0, i); //swap max element with rightmost leaf
        parent = 0;
        child = 1;
        while (child < i) {    
            if (get(child+1) > get(child) && child  < i - 1) {
            child++;} //if child is greater than its left sibling, move to the next child
			if (get(child) > get(parent) && child < i)  {  //if a child is bigger than its parent, switch them
				swap(parent, child);
			}
            parent = child;
            child = 2 * parent + 1;   
        } 
    } 
}


void process() {
	int N = 59000;    
	int i;

	for(i = 0; i < N; ++i){
		put(i,lrand48());
	}


	heapify(N); // turn into a max heap

    sort(N);
    done();


	for(i = 1; i < N; ++i){

		if(get(i-1)>get(i)){
			printf("incorrect!\n");
			exit(1);
		}	
	}


}