#ifndef REDBLACKTREES_H
#define REDBLACKTREES_H

#include <iostream>
#include <node.h>
using namespace std;



class RBTree {


	public: 
		node* root;
		node* nil;
		node* maxNode;
		node* minNode;
		int size;

		RBTree();
		~RBTree();
		void insert(node *);
		void transplant(node*, node*);
		void del(node *);
		void insertFixup(node*);
		void delFixup(node*);
		void leftRotate(node*);
		void rightRotate(node*);
		node* treeMin(node*);
		node* treeMax(node*);
		bool isEmpty();
		void printTree(node* z);
};

#endif
