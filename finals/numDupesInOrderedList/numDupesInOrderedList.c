
#include "list.h"

int numDupesInOrderedList(List l) {
	// TODO
	Node curr = l->head;
	int duplicateCount = 0;
	while (curr != NULL && curr->next != NULL) { 
		if (curr->value == curr->next->value) { 
			duplicateCount++;
		}
		curr = curr->next;
	}
	return duplicateCount;
}

