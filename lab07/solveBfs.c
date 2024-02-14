// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"

//check if it is a wall
void MazeEnqueue (Maze m, Queue q, Cell c, Cell **predecessor, Cell prev, bool **visited) { 
    if (MazeIsWall(m, c)  == false && visited[c.row][c.col] == false) { 
        QueueEnqueue(q,c); 
        predecessor[c.row][c.col] = prev; 
    }
}

bool solve(Maze m) {

    bool **visited = createBoolMatrix(MazeHeight(m), MazeWidth(m)); 
    Cell **predecessor = createCellMatrix(MazeHeight(m), MazeWidth(m));
    Queue q = QueueNew();
    QueueEnqueue(q, MazeGetStart(m)); 
    Cell maze_start = MazeGetStart(m);

    // pseudocode:; while the queue is not empty:
	// 	dequeue v
    while (QueueIsEmpty(q) == false) { 
        Cell c = QueueDequeue(q); 

        // 	pseudocode: if v has already been visited:
	    // 	continue (i.e., go back to beginning of loop)
        if (visited[c.row][c.col]) { 
            continue; 
        }
	    
        visited[c.row][c.col] = true; 

        if (MazeVisit(m, c)) { 
            Cell curr = c; 
            
            // found the exit 
            while (!(curr.row == maze_start.row && curr.col == maze_start.col)) { 
                MazeMarkPath(m, curr);
                curr = predecessor[curr.row][curr.col]; 
            }
            MazeMarkPath(m, curr);
            QueueFree(q);
            freeBoolMatrix(visited);
            freeCellMatrix(predecessor);
            return true;
        }

        // traverse
        Cell lower = c; 
        lower.row++;
        if (lower.row <= MazeWidth(m)) { 
            MazeEnqueue(m, q, lower, predecessor,c,visited); 
        }
        Cell higher = c; 
        higher.row--;
        if (higher.row >= 0) { 
            MazeEnqueue(m, q, higher, predecessor, c, visited); 
        }

        Cell right = c; 
        right.col++;
        if (right.row < MazeHeight(m)) { 
            MazeEnqueue(m, q, right, predecessor, c, visited); 
        }
        Cell left = c; 
        left.col--;
        if (left.row > 0) { 
            MazeEnqueue(m, q, left, predecessor, c, visited); 
        }
    }

    QueueFree(q);
    freeBoolMatrix(visited);
    freeCellMatrix(predecessor);
    return false;
}

