// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"


void MazeEnqueue (Maze m, Stack stack, Cell c, Cell **predecessor, Cell prev, bool **visited) { 
    if (!MazeIsWall(m, c) && !visited[c.row][c.col]) { 
        StackPush(stack,c); 
        predecessor[c.row][c.col] = prev; 
    }
}


bool solve(Maze m) {
    bool **visited = createBoolMatrix(MazeHeight(m), MazeWidth(m)); 
    Cell **predecessor = createCellMatrix(MazeHeight(m), MazeWidth(m));
    Stack stack = StackNew();
    StackPush(stack, MazeGetStart(m)); 
    Cell maze_start = MazeGetStart(m); 

    while (StackIsEmpty(stack) == false) { 
        Cell c = StackPop(stack); 
        if (visited[c.row][c.col]) { 
            continue; 
        }
        visited[c.row][c.col] = true; 

        // found
        if (MazeVisit(m,c)) { 
            Cell curr = c; 
            // Cell maze_start = MazeGetStart(m); 
            while (!(curr.row == maze_start.row && curr.col == maze_start.col)) { 
                MazeMarkPath(m, curr);
                curr = predecessor[curr.row][curr.col]; 
            }
            MazeMarkPath(m, curr);
            StackFree(stack);
            freeBoolMatrix(visited);
            freeCellMatrix(predecessor);
            return true;
        }
        // traverse 
        // question: how do we decide this? why does it only matter for dfs and not much for bfs
        Cell higher = c; 
        higher.row--;
        if (higher.row >= 0) { 
            MazeEnqueue(m, stack, higher, predecessor, c, visited); 
        }


        Cell lower = c; 
        lower.row++;
        if (lower.row <= MazeWidth(m)) { 
            MazeEnqueue(m, stack, lower, predecessor,c,visited); 
        }
        
        Cell right = c; 
        right.col++;
        if (right.row <= MazeHeight(m)) { 
            MazeEnqueue(m, stack, right, predecessor, c, visited); 
        }
        Cell left = c; 
        left.col--;
        if (left.row >= 0) { 
            MazeEnqueue(m, stack, left, predecessor, c, visited); 
        }
    }

    StackFree(stack);
    freeBoolMatrix(visited);
    freeCellMatrix(predecessor);
    return false;
}

