void init(int psize, int winsize){
	int* mem = (int*)malloc((2^25)/sizeof(int));
	int* set = (int*)malloc(winsize); //Note: Should make this a hash table with # of buckets = winsize/4. Makes it easy to find if number is in hash table 
	int* workingsetmodels; //need to implement 2 way linked list	
	int counter = 0;
	int pagesize = psize;
	int windowsize = winsize;
}

void put(unsigned int address, int value){
	mem[address] = value;
	int pageNum = (i*32)/psize;
	//check if pageNum is in current working set
	isInSet = 0;
	for(int i = 0; i < winsize; ++i){ //change winsize later to actual size of set
		if(set[i]==pageNum){
			//Base case: pageNum is in the set
			isInSet = 1;
			break;
		}
	}
	if(!isInSet){
		//put it in the set - nothing here yet!
	}
	//check if counter has reached windowsize
	counter+=1;
	if (counter==winsize){
		//copy & store working set into some stash somewhere
		for(i = 0; i < len(set[i]); ++i){
			workingsetmodels[amountofws][i] = set[i];
			//also clear the set
			set[i] = 0;
		}		
	}
}

int get(unsigned int address){
	int pageNum = (i*32)/psize;
	//check if pageNum is in current working set
	isInSet = 0;
	int i;
	for(i = 0; i < winsize; ++i){ //change winsize later to actual size of set
		if(set[i]==pageNum){
			//Base case: pageNum is in the set
			isInSet = 1;
			break;
		}
	}
	if(!isInSet){
		//put it in the set - nothing here yet!
	}
	//check if counter has reached windowsize
	counter+=1;
	if (counter==winsize){
		//copy & store working set into some stash somewhere
		for(i = 0; i < len(set[i]); ++i){
			workingsetmodels[amountofws][i] = set[i];
			//also clear the set
			set[i] = 0;
		}		
	}
	return mem[address];
}

void done(){
	//print all working sets - unfinished
	int i;
	for(i = 0; i<len(workingsetmodels); ++i){
		print(workingsetmodels[i]);//should print linked lists so change this later
	}
}
