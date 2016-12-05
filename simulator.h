//init() initializes variables in the simulator
//Variables include the memory for all the pages, the working set, linked list for all recorded working sets, etc.
void init(int psize, int winsize);

//setCheck() is a helper function for put() and get()
//Given a page number, checks if the page number is already in the current working set
//If this memory reference is equal to the window size, send current working set to the linked list of all recorded working sets
void setCheck(unsigned int pageNum);

//put()
//Given an address to an integer that is between 0 and 2^25-1, places the given value in that address
void put(unsigned int address, int value);

//get()
//Given an address to an integer that is already stored in the simulator by put(), return that integer.
int get(unsigned int address);

//done()
//called by process(), parameter is head node of the linked list of ws sizes
//print to stdout: list of working set sizes quantized to interval
//				   average of working set size
void done();
