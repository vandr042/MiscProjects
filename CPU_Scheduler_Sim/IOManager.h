#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <list>
#include <node.h>
using namespace std;

class IOManager {
	public:
		IOManager(const char* filename);
		~IOManager();
		void readFile(std::list<node*>* list);
	private:
		ifstream inputFile;
};

#endif
