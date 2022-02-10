#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "Ship.h"
#include "Grid.h"

int random2(int range) {
    int num;
    num = 1 + rand() % range - 1;
    return num;
}

struct Ship initializeShip(char type) {
    struct Ship ship; 
    switch(type) {
       case 'c':
            ship.length = 5;
            ship.maxHits = 4;
            ship.type = 'c';
            break;
       case 'b':
            ship.length = 4;
            ship.maxHits = 3;
            ship.type = 'b';
            break;
       case 'f':
            ship.length = 2;
            ship.maxHits = 2;
            ship.type = 'f'; 
            break; 
    }
    return ship;
}


void addShip(struct Ship* ship, int gridSize, char** grid, char** winGrid, struct locations** location) {

// This iterates all ships and coordinates checking if not in bounds. If not, then it randomizes the ships and checks coordinates again. 

     for(int j = 0; j < 4; j++) {
        spaces(ship[j], location[j]);
        for(int i = 0; i < ship[j].length; i++) {
            if(location[j][i].row < 0 || location[j][i].row >= gridSize || location[j][i].col < 0 || location[j][i].col >= gridSize || grid[location[j][i].row][location[j][i].col] != '-') {
                i = -1;
		ship[j].row = random2(gridSize);
		ship[j].col = random2(gridSize);
		ship[j].vert = random2(2);
		spaces(ship[j], location[j]);
	     }
	}
	
	for(int i = 0; i < ship[j].length; i++) {
	    grid[location[j][i].row][location[j][i].col] = ship[j].type;
	    winGrid[location[j][i].row][location[j][i].col] = ship[j].type;
	}
    }
}

void spaces(struct Ship ship, struct locations* location) { 
     //Inputs the ships coordinates into the location
     for( int i = 0; i < ship.length; i++) {
	 if(ship.vert == 1) {
	    location[i].row = ship.row + i;
	    location[i].col = ship.col;
	 }
	 else if(ship.vert == 0) {
	     location[i].row = ship.row;
	     location[i].col = ship.col + i;
	}
     }
}
	   
