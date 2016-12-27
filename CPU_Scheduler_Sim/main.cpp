#include <iostream>
#include <Scheduler.h>
#include <IOManager.h>
#include <list>
#include <node.h>
using namespace std;
int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "Please provide an input file argument." << endl;
	}else{
		const char* filename = argv[1];
		int timeQuantum;
		list<node*> plist;
		IOManager iom(filename);
		iom.readFile(&plist);
		cout <<	"Enter a time quantum to give each process: "	<< endl;
		cin >> timeQuantum;
		if (timeQuantum <= 0){
			cout << "Time quantum cannot be less than 0.  Terminating." << endl;
		}else{
			Scheduler sch(&plist, timeQuantum);
			sch.run();
			sch.printStats();
		}
	}
}
