#include <stdio.h>
#include <stdlib.h>

//Linked list implementation
typedef struct node_{
	int num;
	struct node_* next;
}node;

//Adds a node to tail node, and returns new tail node
node* addNode(node* tailNode, int number){
	tailNode->next = (node*)malloc(sizeof(node));
	if(tailNode->next == NULL){
		perror("not enough memory to allocate more space for llist"); 
		exit(1);
	}
	tailNode->next->num = number;
	return tailNode->next;
}

//Deletes all nodes
//Postcondition: nodeHead points to an unknown address
void deleteNodes(node* nodeHead){
	node* currentNode = nodeHead;
	while(nodeHead!=NULL){
		currentNode = nodeHead;
		nodeHead = nodeHead->next;
		free(currentNode);
	}
}

//Simulator implementation

//Global variables
int* mem;
int* set;
node* ws_head; //Head node of Linked list for all working sets contained so far
node* ws_tail;
int counter;
int pagesize;
int windowsize;

void init(int psize, int winsize){
	mem = (int*)malloc((2^25)*sizeof(int));
	set = (int*)calloc(winsize,sizeof(int));
	ws_head = (node*)malloc(sizeof(node)); //Head node of Linked list for all working sets contained so far
	ws_tail = ws_head;	
	counter = 0;
	pagesize = psize;
	windowsize = winsize;
}

//setCheck - fundamental piece of put() and get()
//Checks if page is inside of set (current working set interval) and also checks if counter has reached the window size interval
//If counter has reached ws interval, put current set into a linked list and clear the set for new interval
void setCheck(int pageNum){
	//check if pageNum is in current working set
	int temp = 0; //Right now, used to check if a pageNum is inside current working set
	int i;
	for(i = 0; i < windowsize && set[i] != 0; ++i){
		if(set[i]==pageNum){
			//Base case: pageNum is in the set
			temp = 1;
			break;
		}
	}
	if(!temp) set[i] = pageNum;
	//check if counter has reached windowsize
	counter+=1;
	if (counter==windowsize){
		//copy & store working set size
		int temp = 0; //Now temp is used to store the size of of set[i]
		counter = 0;
		for(i = 0; i < windowsize && set[i] != 0; ++i){
			++temp;
			//also clear the set
			set[i] = 0;
		}
		ws_tail = addNode(ws_tail, temp);	
	}
}

void put(unsigned int address, int value){
	mem[address] = value;
	setCheck(1+((address*8*sizeof(int))/pagesize));
}

int get(unsigned int address){
	setCheck(1+((address*8*sizeof(int))/pagesize));
	return mem[address];
}

//called by process(), parameter is head node of the linked list of ws sizes
//print to stdout: list of working set sizes quantized to interval
//				   average of working set size
void done() {
    node* current = ws_head;
    int totalPages = 0;
    int sum = 0;
    while (current!= NULL) {
    	++totalPages;
    	printf("T%d: %d\n", totalPages, current->num);
    	sum += current->num;
    	current = current->next;
    }
    printf("Average Working Set Size: %d\n\n", sum/totalPages);	
}

//~ int main(){
	//~ /* This process function generates a number of integer */
	//~ /* keys and sorts them using bubblesort. */
	//~ int N, i, j, k, t, min, f;
	//~ N = 1000;
	//~ init (128, 1000);
	//~ /* Generate the sorting problem (just random numbers) */
	//~ for (i = 0; i < N; i++) put (i, lrand48 ());
	//~ /* Sort the numbers */
	//~ for (i = 0; i < N-1; i++) {
		//~ for (j = i+1, f = min = get (i), k = i; j < N; j++)
			//~ if ((t = get (j)) < min) {
				//~ k = j;
				//~ min = t;
			//~ }
		//~ put (i, min);
		//~ put (k, f);
	//~ }
	//~ done ();
//~ }
