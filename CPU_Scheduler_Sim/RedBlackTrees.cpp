#include <RedBlackTrees.h>

RBTree::RBTree(){
	nil = new node;
	nil->key = -1;
	nil->p = nil;
	nil->color='b';
	nil->left = nil;
	nil->right = nil;

	root = nil; 
	maxNode = root;
	minNode = root;
	size = 0;
}

void RBTree::insert(node *z){
	size++;
	node* y = nil;
	node* x = root;
	while (x != nil){
		y = x;
		if (z->key < x->key){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	z->p = y;
	if (y == nil){
		root = z;
		maxNode = z;
		minNode = z;
	}else if (z->key < y->key){
		y->left = z;
		if (minNode == y)
			minNode = z;
	}else{
		y->right = z;
		if (maxNode == y)
			maxNode = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = 'r';
	insertFixup(z);
}

void RBTree::transplant(node* u, node* v){
	if (u->p == nil){
		root = v;
	}else if (u == u->p->left){
		u->p->left = v;
	}else{
		u->p->right = v;
	}
	v->p = u->p;
}

void RBTree::del(node *z){
	size--;
	node* y = z;
	node* x = nil;
	char yOrigColor = y-> color;
	if (z->left == nil){
		x = z->right;
		transplant(z, z->right);
	}else if (z->right == nil){
		x = z->left;
		transplant(z, z->left);
	}else{
		y = treeMin(z->right);
		yOrigColor = y->color;
		x = y->right;
		if (y->p == z){
			x->p = y;
		}else{
			transplant(y, y->right);
			y->right = z->right;
			y->right->p =  y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (yOrigColor == 'b')
		delFixup(x);
	else if (maxNode == z || minNode == z){
		if (maxNode == z)
			maxNode = treeMax(root);
		if (minNode == z)
			minNode = treeMin(root);
	}
	
}

void RBTree::insertFixup(node *z){
	node* y = nil;
	bool findMinMax = false;
	if (z->p->color == 'r')
		findMinMax = true;
	while (z->p->color == 'r'){
		if (z->p == z->p->p->left){
			y = z->p->p->right;
			if (y->color == 'r'){
				z->p->color = 'b';
				y->color = 'b';
				z->p->p->color = 'r';
				z = z->p->p;
			}else{
				if (z == z->p->right){
					z = z->p;
					leftRotate(z);
				}
				z->p->color = 'b';
				z->p->p->color = 'r';
				rightRotate(z->p->p);
			}
		}else{
			y = z->p->p->left;
			if (y->color == 'r'){
				z->p->color = 'b';
				y->color = 'b';
				z->p->p->color = 'r';
				z = z->p->p;
			}else{ 
				if (z == z->p->left){
					z = z->p;
					rightRotate(z);
				}
				z->p->color = 'b';
				z->p->p->color = 'r';
				leftRotate(z->p->p);
			}

		}
	}
	root->color = 'b';
	if (findMinMax == true){
		maxNode = treeMax(root);
		minNode = treeMin(root);
	}
}

void RBTree::delFixup(node *x){
	while (x != root && x->color == 'b'){
		if (x == x->p->left){
			node* w = x->p->right;
			if (w->color == 'r'){
				w->color = 'b';
				x->p->color = 'r';
				leftRotate(x->p);
				w = x->p->right;
			}	
			if (w->left->color == 'b' && w->right->color == 'b'){
				w->color = 'r';
				x = x->p;
			}else{
				if (w->right->color == 'b'){
					w->left->color = 'b';
					w->color = 'r';
					rightRotate(w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = 'b';
				w->right->color = 'b';
				leftRotate(x->p);
				x = root;
			}
		}else{
			node* w = x->p->left;
			if (w->color == 'r'){
				w->color = 'b';
				x->p->color = 'r';
				rightRotate(x->p);
				w = x->p->left;
			}	
			if (w->right->color == 'b' && w->left->color == 'b'){
				w->color = 'r';
				x = x->p;
			}else{ 
				if (w->left->color == 'b'){
					w->right->color = 'b';
					w->color = 'r';
					leftRotate(w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = 'b';
				w->left->color = 'b';
				rightRotate(x->p);
				x = root;
			}

		}
	}
	x->color = 'b';
	maxNode = treeMax(root);
	minNode = treeMin(root);
}

void RBTree::leftRotate(node *x){
	node* y = x->right;
	x->right = y->left;
	if (y->left != nil){
		y->left->p = x;
	}
	y->p = x->p;

	if (x->p == nil){
		root = y;
	}else if (x->p->left == x){
		x->p->left = y;
	}else{
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void RBTree::rightRotate(node *x){
	node* y = x->left;
	x->left = y->right;
	if (y->right != nil){
		y->right->p = x;
	}
	y->p = x->p;

	if (x->p == nil){
		root = y;
	}else if (x->p->right == x){
		x->p->right = y;
	}else{
		x->p->left = y;
	}

	y->right = x;
	x->p = y;
}

node* RBTree::treeMin(node* z){
	node* y = nil;
	while (z != nil){
		y = z;
		z = z->left;
	}
	return y;
}

node* RBTree::treeMax(node* z){
	node* y = nil;
	
	while (z != nil){
		y = z;
		z = z-> right;
	}
	return y;
}

RBTree::~RBTree(){
	delete nil;
}

bool RBTree::isEmpty(){
	if (root == nil || root == NULL)
		return true;
	else
		return false;
}

void RBTree::printTree(node* p){
	if (p->left != nil)
		printTree(p->left);
	if (p->right != nil)
		printTree(p->right);
}

