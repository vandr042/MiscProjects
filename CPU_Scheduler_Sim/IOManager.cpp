#include "IOManager.h"
IOManager::IOManager(const char* filename){
	inputFile.open(filename);
	if (!inputFile.is_open()){
		cout << "Could not open file.  Exiting." << endl;
		exit(0);
	}
}

IOManager::~IOManager(){}

void IOManager::readFile(std::list<node*>* list){
	char line[600];
	char delimeter = '\t';
	int buf[6];
	if (inputFile.is_open()){
		int i = 0;
		bool invalid = false;
		inputFile.getline(line, 600);
		while (inputFile.getline(line, 600, delimeter)){
			buf[i] = atoi((const char*) line);	
			if (buf[i] < 0)
				invalid = true;
			i++;
			if (i == 6){
				delimeter = '\t';
				i = 0;
				if (invalid == false){
					node* z = new node();
					z->pid = buf[0];
					z->bst = buf[1];
					z->arr = buf[2];
					z->key = buf[3];
					z->pri = buf[3];
					z->dline = buf[4];
					z->io = buf[5];
					z->lastBurst = -1;
					list->push_back((node* const&)z);
				}else{
					invalid = false;
				}
			}else if(i == 5)
				delimeter = '\n';
		}
		list->sort(compareNodeArrival);
	}else{
		cout << "Could not read file.  File is not open." << endl;
	}
}
