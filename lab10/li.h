#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct node {
	int data;
	struct node* next;
};

typedef struct node node;

struct li {
	node* head;
};

typedef struct li li;


struct tuple {
	li* t1;
	li* t2;
	li* t3;
};

typedef struct tuple tuple;

/*
	Print the content of a list of ints
*/
void li_print(li* L);


/*
	Allocate 3 lists of ints [1,...,n]. Return a struct with 3 pointers to the new lists or NULL if memory allocations fails.
*/
tuple* li_alloc(int n);


/* 
	Release a list of ints and all of its nodes.
*/
void li_free(li* L);


/*
	Evaluate mtf method cost for accesses described in num array. Return the integer cost or 0 in case of error.
*/
int li_mtf(li* L, int* num, int r);


/*
	Evaluate transpose method cost for accesses described in num array. Return the integer cost or 0 in case of error.
*/
int li_transp(li* L, int* num, int r);


/*
	Evaluate count method cost for accesses described in num array. Return the integer cost or 0 in case of error.
*/
int li_count(li* L, int* num, int r, int n);



