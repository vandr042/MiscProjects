#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <node.h>

class LinkedList { 
	public:
		LinkedList();
		~LinkedList();
		void remove(ageIONode*);
		void addFront(ageIONode*);
		void addBack(ageIONode*);
		ageIONode* getFront();
		ageIONode* getBack();
		bool empty();
		unsigned int getSize();

	private:
		unsigned int size;
		ageIONode* front;
		ageIONode* back;
};


#endif
