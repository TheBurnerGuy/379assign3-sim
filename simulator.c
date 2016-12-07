#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"

//Linked list implementation
typedef struct node_{
	int num;
	unsigned int key;
	struct node_* next;
}node;

//Global variables
node** table;
int* set;
node* ws_head; //Head node of Linked list for all working sets contained so far
node* ws_tail;
int counter;
int pagesize;
int windowsize;

//Adds a node to tail node, and returns new tail node
node* addTailNode(node* tailNode, int number){
	if (ws_tail==NULL){
		//Base case: No tail yet
		ws_tail = ws_head;
		ws_tail->num = number;
		return ws_tail;
	}
	tailNode->next = (node*)malloc(sizeof(node));
	if(tailNode->next == NULL){
		perror("not enough memory to allocate more space for llist"); 
		exit(1);
	}
	tailNode->next->num = number;
	return tailNode->next;
}

//Adds a node given the address if theres no node already there.
//If there are nodes (linked list) there, check if a key exists there. 
//If yes, replace the number there. 
//If not, make one.
void addNode(int number, unsigned int key){
	//printf("I'm here %d!\n", key);
	node* currentNode = table[key%windowsize];
	if(currentNode==NULL){
		//Base case: no llist made yet
		//~ printf("made llist %d",key);
		node* currentNode = (node*)malloc(sizeof(node));
		table[key%windowsize] = currentNode;
		currentNode->num = number;
		currentNode->key = key;
		currentNode->next;
		return;
	}
	node* savedNode;
	while(currentNode != NULL){
		savedNode = currentNode;
		if(currentNode->key == key){
			//Base case: key already exists inside
			currentNode->num = number;
			return;
		}
		currentNode = currentNode->next;
	}
	//~ printf("making key%d",key);
	//Key does not exist, so make a node for that key
	savedNode->next = (node*)malloc(sizeof(node));
	savedNode->next->num = number;
	savedNode->next->key = key;
}

//Searches a node for a key given the address (returns if NULL)
//returns the stored number inside node
int searchNodes(unsigned int key){
	node* currentNode = table[key%windowsize];
	while (currentNode != NULL){
		if(currentNode->key == key) return currentNode->num;
		currentNode = currentNode->next;
	}
	printf("no num: error\n");
	return 0;
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

void init(int psize, int winsize){
	//mem = (int*)malloc((2^25)*sizeof(int));
	table = (node**)calloc(winsize,sizeof(node*)); //Assumes (*winsize) buckets is enough... may change in the future
	set = (int*)calloc(winsize,sizeof(int));
	ws_head = (node*)malloc(sizeof(node)); //Head node of Linked list for all working sets contained so far
	ws_tail = NULL;	
	counter = 0;
	pagesize = psize;
	windowsize = winsize;
}

//setCheck - fundamental piece of put() and get()
//Checks if page is inside of set (current working set interval) and also checks if counter has reached the window size interval
//If counter has reached ws interval, put current set into a linked list and clear the set for new interval
void setCheck(unsigned int pageNum){
	//check if pageNum is in current working set
	int temp = 0; //Right now, used to check if a pageNum is inside current working setsearchNodes
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
		//~ printf("entered tail node hell\n");
		//copy & store working set size
		int temp = 0; //Now temp is used to store the size of of set[i]
		counter = 0;
		for(i = 0; i < windowsize && set[i] != 0; ++i){
			++temp;
			//also clear the set
			set[i] = 0;
		}
		
		ws_tail = addTailNode(ws_tail, temp);
		//~ printf("survived through tail node hell\n");	
	}
}

void put(unsigned int address, int value){
	//mem[address] = value;
	addNode(value, address);
	setCheck(1+((address*8*sizeof(int))/pagesize));
}

int get(unsigned int address){
	setCheck(1+((address*8*sizeof(int))/pagesize));
	return searchNodes(address);
	//return mem[address];
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
    //Consider calling deleteNodes here
}

int main(int argc, char* argv[]){
	if(argc!=3){
		printf("%d is invalid amount of arguments!\n",argc);
		exit(1);
	}
	init(atoi(argv[1]),atoi(argv[2]));
	process();

}
