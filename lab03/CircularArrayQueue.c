// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 8 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	//if the array has reached capacity 
	if (q->size == q->capacity) { 
		// store the front elements in a temporary array
		int *temp_array = malloc(q->frontIndex * sizeof(Item));
		for (int i = 0; i < q->frontIndex; i++) { 
			temp_array[i] = q->items[i];
		}
		// create new malloc to double the capacity
		q->items = realloc(q->items, q->capacity * 2 * sizeof(Item));
		if (q->items == NULL) {
			fprintf(stderr, "couldn't resize Queue\n");
			exit(EXIT_FAILURE);
		}  
		// copy over the items to the 'end' of the old queue
		for (int i = 0, j = q->capacity; i < q->frontIndex; i++, j++) { 
			q->items[j]=temp_array[i];
		}
		free(temp_array);
		// update the struct after
		q->capacity = q->capacity * 2;
		
	}
	q->items[(q->size + q->frontIndex) % q->capacity] = it;
	q->size = q->size + 1;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	int temp_item = q->items[q->frontIndex];
	q->frontIndex = (q->frontIndex + 1) % q->capacity;
	q->size--;
	return temp_item;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is ns
 * ot empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		printf("%d ", q->items[i]);
	}
	printf("\n");
}

