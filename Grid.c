#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> 
#include "Ship.h"

char** createArray(int gridSize) {
    char** grid; 
    grid = calloc(gridSize, sizeof(char*)); 
    if(grid == NULL) {
       printf("FATAL ERROR: out of memory: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < gridSize; i++) {
        grid[i] = calloc(gridSize, sizeof(char));
        if(grid[i] == NULL) {
           printf("FATAL ERROR: out of memory: %s\n", strerror(errno));
           exit(EXIT_FAILURE);
        }
    }
    return grid; 
}

void fill_grid(char ** grid, int gridSize) {
    for(int i = 0; i < gridSize; i++) {
       for(int j = 0; j < gridSize; j++) {
          grid[i][j] = '-';
       }
    }
    return; 

}

void printArray(char** grid, int gridSize) {
    printf("  "); 
    for(int i = 0; i < gridSize; i++) {
       printf("%c ", i + 65);
    }
    printf("\n");
    printf(" +");
    for(int i = 0; i < gridSize * 2; i++) {
       printf("-");
    }
    printf("\n");
    for(int i = 0; i < gridSize; i++) {
       printf("%d |", i + 1);
       for(int j = 0; j < gridSize; j++) {
          printf("%c ", grid[i][j]); 
       }
       printf("\n");
    }
    return;
}

void deleteArray(char** grid, int gridSize) {
     for(int i = 0; i < gridSize; i++) {
        free(grid[i]);
     }
     free(grid);
}
    
