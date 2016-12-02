#include <stdio.h>
#include <stdlib.h>
struct node* BuildOneTwoThree(); //small example linked list for testing 
typedef struct node
{
    int num;
    struct node * next;
}node;

//called by process(), parameter is head node of the linked list of ws sizes
//print to stdout: list of working set sizes quantized to interval
//				   average of working set size
void done(struct node* workingsetmodels) {
    struct node* current = workingsetmodels;

    int i = 0;
    int sum = 0;
    while (current!= NULL) {
    	i++;
    	printf("T%d: %d\n", i, current->num);
    	sum += current ->num;

    	current = current-> next;
    }



    printf("Average Working Set Size: %d\n\n", sum/i);	
}




int main(int argc, char* argv[]) {

    struct node* workingsetmodels = BuildOneTwoThree(); // initialize a small example list to test done
    done(workingsetmodels);

}


/*
 Build the list {1, 2, 3} in the heap and store
 its head pointer in a local stack variable.
 Returns the head pointer to the caller.
*/
struct node* BuildOneTwoThree() {
    struct node* head = NULL;
    struct node* second = NULL;
    struct node* third = NULL;
    head = malloc(sizeof(struct node));
    // allocate 3 nodes in the heap
    second = malloc(sizeof(struct node));
    third = malloc(sizeof(struct node));
    head->num = 5;
    head->next = second;
    second->num = 10;
    second->next = third;
    third->num = 20;
    third->next = NULL;
    return head;
}

