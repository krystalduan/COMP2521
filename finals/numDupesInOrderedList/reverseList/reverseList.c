
#include "list.h"

// void listReverse(List l) {
// 	// TODO
// 	Node curr = l->head;
// 	Node temp = NULL;
// 	while (curr != NULL) { 
// 		temp = l->head;
// 		l->head = curr->next;
// 		if (curr->next != NULL && curr->next->next != NULL) { 
// 			curr->next = curr->next->next;
// 		} else if (curr->next)
// 		else {
// 			curr->next = NULL;
// 		}
// 		l->head->next = temp;
// 		curr = curr->next;
// 	}
	
// }

void listReverse(List l) {
	Node prev = NULL;
	Node curr = l->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		temp->next = prev;
		prev = temp;
	}
	l->head = prev;
}

