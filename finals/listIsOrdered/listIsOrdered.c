
#include "list.h"

bool listIsOrdered(List l) {
	// TODO
	Node curr = l->head;
	if (curr == NULL || curr->next == NULL) { 
		return true;
	}

	if (curr->value <= curr->next->value) { 
		while (curr->next != NULL) { 
			if (curr->value > curr->next->value) { 
				return false;
			}
			curr = curr->next;
		}
	}
	else if (curr->value >= curr->next->value) { 
		while (curr->next != NULL) { 
			if (curr->value < curr->next->value) { 
				return false;
			}
			curr = curr->next;
		}
	}
	return true;;
}

