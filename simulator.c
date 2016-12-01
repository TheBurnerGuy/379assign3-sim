typedef struct node_{
	int num;
	struct node_* next;
	struct node_* prev;
}node;

void init(int psize, int winsize){
	int* mem = (int*)malloc((2^25)/sizeof(int));
	int wsModelsHead; //need to implement 2 way linked list
	int wsModelsTail;
	int counter = 0;
	int pagesize = psize;
	int windowsize = winsize;
}

void put(unsigned int address, int value){
	mem[address] = value;
	int pageNum = (i*32)/psize;
	
}

int get(unsigned int address){
	int pageNum = (i*32)/psize;
	return mem[address];
}

void done(){
	//print all working sets - unfinished
	int i;
	for(i = 0; i<len(workingsetmodels); ++i){
		print(workingsetmodels[i]);//should print linked lists so change this later
	}
}
