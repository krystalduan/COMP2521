
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) { 
		return NULL;
	}
	while (t->left != NULL) { 
		t = t->left;
	}
	return t;
}
// this has a memory leak 
// BSTree BSTreeGetSmallest(BSTree t) {
// 	// if (t == NULL) { 
// 	// 	return t; 
// 	// }

// 	// if (t->left == NULL) {
// 	// 	return t;
// 	// }
// 	if (t == NULL) { 
// 		return NULL;
// 	}
// 	BSTree curr = malloc(sizeof(struct BSTNode));
// 	curr = t;
// 	while (curr->left != NULL) { 
// 		curr = curr->left;
// 	}
	
// 	return curr;
// 	//t->right = BSTreeGetSmallest(t->right);
	
	
// }

