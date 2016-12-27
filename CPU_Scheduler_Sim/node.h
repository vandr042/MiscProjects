#ifndef NODE_H
#define NODE_H

typedef struct ageIONode ageIONode;
struct node
{
	int key; //priority 
	node* p;
	char color;
	node* left;
	node* right;
	int bst; //burst
	int lastBurst;
	int arr; //arrival time
	int pid;
	int pri;
	int dline; //deadline
	int io; //does process do i/o

	ageIONode* ageNode;
	node* proc;
};

struct ageIONode {
	int value;
	
	node* proc;
	ageIONode* next;
	ageIONode* prev;
};

bool compareNodeArrival(node* p1, node* p2);

#endif
