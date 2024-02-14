
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	// TODO
	if (t == NULL) { 
		BSTree newNode = malloc(sizeof(struct BSTNode));
		newNode->value = val;
		newNode->right = NULL;
		newNode->left = NULL;
		return newNode;
	}
	if (t->value < val) { 
		t->right = BSTreeInsert(t->right, val);
	}
	else if (t->value > val) { 
		t->left = BSTreeInsert(t->left, val);
	}
	else if (t->value == val) { 
		return t;
	} 
	return t;
}

