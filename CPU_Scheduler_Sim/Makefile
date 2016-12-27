all: main

main: Scheduler.o RedBlackTrees.o IOManager.o node.o LinkedList.o main.cpp
	g++ RedBlackTrees.o node.o IOManager.o Scheduler.o LinkedList.o main.cpp -o sim -I .

LinkedList.o: LinkedList.cpp LinkedList.h node.o
	g++ LinkedList.cpp node.o -c -I .

mainDEBUG: SchedulerDEBUG.o RedBlackTrees.o IOManager.o node.o main.cpp
	g++ RedBlackTrees.o node.o IOManager.o SchedulerDEBUG.o main.cpp -o sim -I .
	
RBTree: RedBlackTrees.cpp RedBlackTrees.h node.o
	g++ RedBlackTrees.cpp node.o -o RBTree -I .

RedBlackTrees.o: RedBlackTrees.cpp RedBlackTrees.h node.o
	g++ RedBlackTrees.cpp node.o -c -I .

IOManager.o: IOManager.cpp IOManager.h node.o
	g++ IOManager.cpp node.o -c -I .

node.o: node.cpp node.h
	g++ node.cpp -c -I .

Scheduler.o: Scheduler.cpp Scheduler.h RedBlackTrees.o node.o
	g++ -UDEBUG Scheduler.cpp RedBlackTrees.o node.o -c -I . 

SchedulerDEBUG.o: Scheduler.cpp Scheduler.h RedBlackTrees.o node.o
	g++ -DDEBUG Scheduler.cpp RedBlackTrees.o node.o -c -o SchedulerDEBUG.o -I . 
clean:
	rm -f *.o Scheduler sim RBTree IOManager node
