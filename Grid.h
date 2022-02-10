#ifndef GRID_H
#define GRID_H
#include "Ship.h"
void fill_grid(char ** grid, int gridSize);
char** createArray(int gridSize);
void printArray(char** grid, int gridSize);
void deleteArray(char** grid, int gridSize);
#endif
