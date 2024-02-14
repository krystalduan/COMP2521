// Implementation of the Queue ADT using a struct

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//#include "climber.h"
//#include "Wall.h"
#include "Queue.h"

//typedef struct queue *Queue;
struct queue {
	struct rock *rocks;
	int  size;
};


/**
 * Creates a new empty queue of size length
 */
Queue QueueNew(int length) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->rocks = malloc(length * sizeof(struct rock));
	if (q->rocks == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->rocks);
	free(q);
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
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, struct rock it) {
	q->rocks[q->size++] = it;
	//q->size++;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
struct rock QueueDequeue(Queue q) {
	assert(q->size > 0);

	struct rock item = q->rocks[0];
	for (int i = 1; i < q->size; i++) {
		q->rocks[i - 1] = q->rocks[i];
	}
	q->size--;
	return item;
}


// priority queue dequeue for task 2
struct rock PriorityQueueDequeue(Queue q,int **distance) {
	assert(q->size > 0);

	// Find earliest element with smallest value (highest priority)
	int chosenIndex = 0;
	for (int i = 1; i < q->size; i++) {
		if (distance[q->rocks[i].row][q->rocks[i].col] 
            < distance[q->rocks[chosenIndex].row][q->rocks[chosenIndex].col]) {
			chosenIndex = i;
		}
	}

	struct rock item = q->rocks[chosenIndex];
	// Shuffle down everything after that element
	for (int i = chosenIndex + 1; i < q->size; i++) {
		q->rocks[i - 1] = q->rocks[i];
	}
	// change size of the queue
    	q->size--;
	return item;
}

