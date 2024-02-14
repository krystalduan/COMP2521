
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();
	// test large input to compare time
	int input_size = 100000;
	for (int i = 1; i <= input_size; i++) { 
		QueueEnqueue(q,i);
	}
	// use input_size - 1 because <=
	for (int i = 0; i <= input_size - 1; i++) { 
		QueueDequeue(q);
	}

	QueueFree(q);
}

/*
$ time ./benchmarkArrayQueue

real    1m37.321s
user    1m37.304s
sys     0m0.000s

$ time ./benchmarkCircularArrayQueue

real    0m0.024s
user    0m0.016s
sys     0m0.008s


*/

