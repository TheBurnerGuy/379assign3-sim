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
	return newNode;
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
	static int* mem = (int*)malloc((2^25)/sizeof(int));
	static int* set = (int*)calloc(winsize,sizeof(int));
	static node* ws_head = (node*)malloc(sizeof(node)); //Head node of Linked list for all working sets contained so far
	static node* ws_tail = ws_Head;	
	static int counter = 0;
	static int pagesize = psize;
	static int windowsize = winsize;
}

//Checks if page is inside of set and also checks if counter has reached the window size interval
//Function created for convenience instead of writing to both put and get
void setCheck(int pageNum){
	//check if pageNum is in current working set
	isInSet = 0;
	int i;
	for(i = 0; i < winsize && set[i] != 0; ++i){ //change winsize later to actual size of set
		if(set[i]==pageNum){
			//Base case: pageNum is in the set
			isInSet = 1;
			break;
		}
	}
	if(!isInSet) set[i] = pageNum;
	//check if counter has reached windowsize
	counter+=1;
	if (counter==winsize){
		//copy & store working set size
		int length = 0;
		for(i = 0; i < winsize && set[i] != 0; ++i){
			++length;
			//also clear the set
			set[i] = 0;
		}
		ws_tail = addNode(ws_tail, length);	
	}
}

void put(unsigned int address, int value){
	mem[address] = value;
	setCheck(1+(address*32)/pagesize);
}

void get(unsigned int address){
	setCheck(1+(address*32)/pagesize);
	return mem[address];
}

void done(){
	//print all working sets - unfinished
	int i;
	for(i = 0; i<len(workingsetmodels); ++i){
		print(workingsetmodels[i]);
	}
}
