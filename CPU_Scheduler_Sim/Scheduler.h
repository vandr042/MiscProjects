#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <RedBlackTrees.h>
#include <iostream>
#include <list>
#include <LinkedList.h>
#include <deque>
class Scheduler { 
	public:
		node* activeProcess;
		list<node*>* plist;
		RBTree readyQueue;
		LinkedList ageQueue;
		RBTree waitQueue;
		int clockTime, quantum, tempQuantum;	
		float NP, ATT, AWT;

		Scheduler(list<node*>* procList, int timeQuantum);
		~Scheduler();
		void run();
		void printStats();
	private:
		void ageAndPromote();
		void tick();
		void cpuDoWork();
		void ioDeviceDoWork();
		void checkArrivals();
};


#endif
