/*
Min cost heap 
*/

struct node{
	int key;
	int cost;
};
typedef struct node node;

struct heap{
	node* pdata;
	int size;
};
typedef struct heap heap;

/*
Insert a new value in the heap. If it already exists nothing occurs.
*/
int insert(heap* hp, int* i, int key, int cost);

/*
Remove the first element from a min heap and print it.
*/
int min_heap(heap* hp, int* i);

/*
Reduce a key cost and heapify the heap.
*/
int reduce(heap* hp, int* i, int key, int cost); 

/*
Print the heap data.
*/
void print_heap(heap* hp);

/*
Swap two values from a heap.
*/
void swap(heap* hp, int* i, int root, int smallest);

/*
Print the I array.
*/
void print_i(int* i, int n);
