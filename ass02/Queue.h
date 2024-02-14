// Interface to the Queue ADT


#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include "Wall.h"

typedef struct queue *Queue;

/**
 * Creates a new empty queue of size length
 */
Queue QueueNew(int length);

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q);

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q);


/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q);

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, struct rock it);

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
struct rock QueueDequeue(Queue q);

/**
 * priority queue dequeue for task 2
 * dequeues rock of smallest distance
 */
struct rock PriorityQueueDequeue(Queue q, int **distance);



#endif

