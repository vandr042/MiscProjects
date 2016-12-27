#include <LinkedList.h>
#include <cstdlib>

LinkedList::LinkedList(){
	size = 0;
	front = NULL;
	back = NULL;
}

LinkedList::~LinkedList(){}

void LinkedList::remove(ageIONode* x){
	if (x->prev != NULL)
		x->prev->next = x->next;
	if (x->next != NULL)
		x->next->prev = x->prev;
	if (x == front)
		front = x->next;
	if (x == back)
		back = x->prev;
	x->prev = NULL;
	x->next = NULL;
	size--;
}

void LinkedList::addFront(ageIONode* x){
	if (front != NULL){
		front->prev = x;
		x->next = front;
		front = x;
	}else{  // list is empty
		front = x;
		back = x;
	}
	size++;
}

void LinkedList::addBack(ageIONode* x){
	if (back != NULL){
		back->next = x;
		x->prev = back;
		back = x;
	}else{
		front = x;
		back = x;
	}
	size++;

}

ageIONode* LinkedList::getFront(){
	return front;
}

ageIONode* LinkedList::getBack(){
	return back;
}

bool LinkedList::empty(){
	if (size == 0)
		return true;
	else
		return false;
}

unsigned int LinkedList::getSize(){
	return size;
}	
