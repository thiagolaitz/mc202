/*
	Hash table
*/
struct hashItem {
	unsigned char* pdata;
	int timestamp;
	int state;
};
typedef struct hashItem hashItem;

/*
Uses the djb2 algorithm to map an unsigned char array to an encoded value.
*/
unsigned long djb2(unsigned char* str);

/*
Insert a value into a hash table. Receives the text to be inserted, a djb2 encoded value, the timestamp, the hashTable, and the maximum length m.
*/
void insert(unsigned char* text, unsigned long djb2, int timestamp, hashItem* hashTable, int m);

/*
Searches for a text in a hash table. If the text exists in the hash table it returns the timestamp of the text. Otherwise, -1 is returned
*/
int search(unsigned char* text, unsigned long djb2, hashItem* hashTable, int m);

/*
Removes a text from a hash table. Must only be called if the data exists in the hash table.
*/
void remove_item(unsigned char* text, unsigned long djb2, int timestamp, hashItem* hashTable, int m);
