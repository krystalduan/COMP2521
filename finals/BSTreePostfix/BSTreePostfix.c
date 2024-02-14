
#include <stdio.h>

#include "BSTree.h"



void BSTreePostfix(BSTree t) {
	if (t == NULL) { 
		return;
	}
	if (t->right == NULL && t->left == NULL) { 
		printf("%d ", t->value);
		return;
	}
	
	if (t->left != NULL) {
		BSTreePostfix(t->left);
		
	}
	
	
	if (t->right != NULL){
		BSTreePostfix(t->right);
		
	}
	
	printf("%d ", t->value);

	

}
