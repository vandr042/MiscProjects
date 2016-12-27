#include <Scheduler.h>
Scheduler::Scheduler(list<node*>* procList, int timeQuantum){
	plist = procList;
	quantum = timeQuantum;
	clockTime = 0;	
	activeProcess = NULL;
	NP = 0;
	ATT = 0;
	AWT = 0;
};

Scheduler::~Scheduler(){}

void Scheduler::run(){

	while (!plist->empty() || !readyQueue.isEmpty() || !waitQueue.isEmpty() || activeProcess != NULL){
		/* if processes have arrived move them to the ready queue */
		if (!plist->empty()){
			checkArrivals();
		}
		if (!waitQueue.isEmpty()){
			#ifdef DEBUG
				cout << "Doing io work." << endl;
			#endif
			ioDeviceDoWork();
		}
		if (!readyQueue.isEmpty()){			
			cpuDoWork();
			ageAndPromote();	
		}else if (activeProcess != NULL){
			cpuDoWork();
		}	
		tick();
	}	
}
void Scheduler::ageAndPromote(){
	ageIONode* min = ageQueue.getFront();
	while (min != NULL && min->value == clockTime){
		readyQueue.del(min->proc);
		ageQueue.remove(min);
		min->value = clockTime+100;
		if (min->proc->key < 50){	
			min->proc->key += 10;
			if (min->proc->key >= 50)
				min->proc->key = 49;
		}
		else{
			min->proc->key += 10;
			if (min->proc->key >= 100)
				min->proc->key = 99;
		}
		#ifdef DEBUG
			cout << "Inserting from age and promote." << endl;
		#endif
		readyQueue.insert(min->proc);
		ageQueue.addBack(min);
		min = ageQueue.getFront();
	}
}

void Scheduler::printStats(){
	cout << "AWT: " << AWT/NP << " ATT: " << ATT/NP << " NP: " << NP << endl;
}

void Scheduler::tick(){
	clockTime++;
}

void Scheduler::cpuDoWork(){
	if (activeProcess == NULL){
		activeProcess = readyQueue.maxNode;
		tempQuantum = 0;
		#ifdef DEBUG
			cout << "set new process printing tree " << activeProcess->key << endl;
			readyQueue.printTree(readyQueue.root);
		#endif
		if (activeProcess->lastBurst != -1){
			AWT += clockTime - activeProcess->lastBurst;
		}
		readyQueue.del(activeProcess);
		ageQueue.remove(activeProcess->ageNode);
		#ifdef DEBUG
			readyQueue.printTree(readyQueue.root);
		#endif
		
	}
	activeProcess->bst--;
	tempQuantum++;
	
	if (activeProcess->bst == 0){
		#ifdef DEBUG
			cout << "Deleting active process." << endl;
		#endif 
		NP++;
		ATT += clockTime+1 - activeProcess->arr;
		delete activeProcess->ageNode;
		delete activeProcess;
		activeProcess = NULL;
	} else if (tempQuantum == quantum-1 && activeProcess->io > 0){
		node* ioNode = new node;
		ioNode->key = clockTime + 1 + activeProcess->io;
		ioNode->proc = activeProcess;
		waitQueue.insert(ioNode);
		activeProcess = NULL;
	} else if (tempQuantum == quantum){
		activeProcess->ageNode->value = clockTime+101;
		activeProcess->lastBurst = clockTime+1;
		int newPriority = activeProcess->key - quantum;
		#ifdef DEBUG
			cout << "cpu changing priority: " << activeProcess->pid << " " << activeProcess->key << " quantum " << quantum << " newPri " << newPriority << endl;
		#endif
		if (newPriority < activeProcess->pri)
			activeProcess->key = activeProcess->pri;
		else
			activeProcess->key = newPriority;	
		#ifdef DEBUG
			cout << "Key changed to " << activeProcess -> key << endl;
			cout << "Calling insert from cpuDoWork " << clockTime << endl;
		#endif
		readyQueue.insert(activeProcess);
		ageQueue.addBack(activeProcess->ageNode);
		activeProcess = NULL;
		#ifdef DEBUG 
			cout << "___Print from cpu___" << endl;
			readyQueue.printTree(readyQueue.root);
		#endif
	}
}

void Scheduler::ioDeviceDoWork(){
	node* p = waitQueue.minNode;
	while (p != waitQueue.nil && p->key == clockTime){
		if (p->proc->key < 50){	
			p->proc->key += p->proc->io;
			if (p->proc->key >=50)
				p->proc->key = 49;	
		}
		else{
			p->proc->key += p->proc->io;
			if (p->proc->key >= 100)
				p->proc->key = 99;
		}
		readyQueue.insert(p->proc);
		p->proc->lastBurst = clockTime+1;
		p->proc->ageNode->value = clockTime+1+100;
		ageQueue.addBack(p->proc->ageNode);
		waitQueue.del(p);
		delete p;	
		p = waitQueue.minNode;	
	}
}

void Scheduler::checkArrivals(){
	node* arrivalNode;
	arrivalNode = plist->back();
	while (arrivalNode->arr == clockTime){
		ageIONode* ageN = new ageIONode;
		ageN->value = clockTime + 100;
		ageN->proc = arrivalNode;
		arrivalNode->ageNode = ageN;
		#ifdef DEBUG	
			cout << "Inserting from arrivals." << endl;
		#endif
		readyQueue.insert(arrivalNode);
		ageQueue.addBack(ageN);
		#ifdef DEBUG
			cout << "size " << readyQueue.size << endl;
			cout << "tree__ ";
			readyQueue.printTree(readyQueue.root);
		#endif
		plist->pop_back();
		if (plist->empty()){
			break;
		}else{
			arrivalNode = plist->back();	
		}
		
	}
}

