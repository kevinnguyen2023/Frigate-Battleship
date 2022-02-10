#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Grid.h"
#include "Ship.h"

int main(void) {
    printf("Welcome to Frigate!\n"); 
    struct locations** coordinates;
    coordinates = (struct locations**)malloc(sizeof(struct locations*) * 4);
    struct Ship carrier;
    struct Ship battleShip;
    struct Ship frigate1;
    struct Ship frigate2;
    //Creating a seed for randomization later on
    srand(time(NULL));

    char** grid;
    char** grid1;
    char** winGrid;
    int gridSize;

    //Partly initializing the four ships
    carrier = initializeShip('c');
    battleShip = initializeShip('b');
    frigate1 = initializeShip('f');
    frigate2 = initializeShip('f');
	
    //Initializing array of ships to easily access the four ships;
    struct Ship* ships = (struct Ship*)malloc(sizeof(struct Ship) * 4);
	
   //Opening a the input.txt file and scanning the file and inputting the variables into the ships
    char string[75];
    printf("Enter the file name(If no file, enter a string): ");
    scanf("%s", string);
    FILE* file;
    file = fopen(string, "r");
    if(file) {
	printf("The file was loaded successfully loaded! \n");
	int c;
	int comment;
	int count = 0;
	printf("How large should I make the grid?");
	scanf("%d", &gridSize);
	if(gridSize > 4 && gridSize < 21) {
	   printf("Grid Size is %d\n", gridSize);
	}
	else if(gridSize < 5) {
	    printf("Grid Size is incorrect, the minimum grid size is 5... I'll make one of size 5\n");
	    gridSize = 5;
	}
	else {
	    printf("Grid Size is incorrect, the maximum grid size is 20... I'll make one of size 20\n");
	    gridSize = 20;
	    }
	    
	while((c = fgetc(file)) != EOF) {
	     if(c == '#') {
		comment = 1;
	     }
	     else if(c == '\n') {
		comment = 0;
	     }
	     else if(comment == 0) {
		switch(c) {
		    case 'c':
			c = fgetc(file);
			c = fgetc(file);
						
		       if(c == 'r') {
		         carrier.vert = 1;
		       }
	              else if( c == 'c') {
		         carrier.vert = 0;
		      }
		      c = fgetc(file);
		      c = fgetc(file);
		      int carrierCol = (int)(c) - 97;
		      carrier.col = carrierCol;
						
		       c = fgetc(file);
		       int carrierRow = (int)(c) - 49;
		       carrier.row = carrierRow;
		       break;
		   case 'b':	
			//printf("Creating battleShip\n");
		        
		        c = fgetc(file);
			c = fgetc(file);
			if(c == 'r') {
			   battleShip.vert = 1;
			}
			else if(c == 'c') {
			    battleShip.vert = 0;
			}
			
			c = fgetc(file);
			c = fgetc(file);
			int battleShipCol = (int)(c) - 97;
			//printf("Battle Col: %i \n", battleShipCol);
			battleShip.col = battleShipCol;
						
			c = fgetc(file);
			int battleShipRow = (int)(c) - 49;
			//printf(" Batlle Row is %i \n", battleShipRow);
			battleShip.row = battleShipRow;
			break;
		    case 'f':
		    	if(count == 0) {				
			   c = fgetc(file);
			   c = fgetc(file);
							
			   if(c == 'r') {
			     frigate1.vert = 1;
			   }
			   else if(c == 'c') {
			     frigate1.vert = 0;
			   }
			   c = fgetc(file);
			   c = fgetc(file);
			   int frigate1Col = (int)(c) - 97;
			   frigate1.col = frigate1Col;
							
			   c = fgetc(file);
			   int frigate1Row = (int)(c) - 49;
			   frigate1.row = frigate1Row;
							
			}
			else if(count == 1) {
			     c = fgetc(file);
			     c = fgetc(file);
							
			     if(c == 'r') {
				frigate2.vert = 1;
			     }
			     else if(c == 'c') {
				frigate2.vert = 0;
			     }
			     c = fgetc(file);
			     c = fgetc(file);
			     int frigate2Col = (int)(c) - 97;
			     frigate2.col = frigate2Col;
							
			     c = fgetc(file);
			     int frigate2Row = (int)(c) - 49;
			     frigate2.row = frigate2Row;
			     printf("\n");
			 }
			 count++;
			 break;
		  default:
		    break;
		}	
	     }
	}
    }
    else if(!file) { //input for the grid
	printf("How large should I make the grid?");
	scanf("%d", &gridSize);
	if(gridSize > 4 && gridSize < 21) {
	   printf("Grid Size is %d\n", gridSize);
	}
	else if(gridSize < 5) {
	    printf("Grid Size is incorrect, min is 5... I'll make one of size 5\n");
	    gridSize = 5;
	}
	else {
	   printf("Grid Size is incorrect, max is 20... I'll make one of size 20\n");
	   gridSize = 20;
	}	
	
	for(int i = 0; i < 4; i++) {
	    ships[i].row = gridSize + 1;
	    ships[i].col = gridSize + 1;
	    ships[i].vert = random2(2);
	}
		
     }
	
     //Inputting the ships into one array to save time
     ships[0] = carrier;
     ships[1] = battleShip;
     ships[2] = frigate1;
     ships[3] = frigate2;
     //Initializing the coordinates to an array
     for(int i = 0; i < 4; i++) {
	coordinates[i] = (struct locations*)malloc(sizeof(struct locations) * ships[i].length);
	}
	//ALlocating space for the grids
	grid = createArray(gridSize);
	grid1 = createArray(gridSize);
	winGrid = createArray(gridSize);
	//Filling the grids with a '-'
	fill_grid(grid, gridSize);
	fill_grid(grid1, gridSize);
	fill_grid(winGrid, gridSize);

	//Putting the coordinates of the ships inside the double array coordinates
	for(int i = 0; i < 4; i++) {
	   spaces(ships[i], coordinates[i]);
	}
	
	//If the coordinates of ships are invalid, addShip will randomize the coordinates and reset the ship starting point
	addShip(ships, gridSize, grid1, winGrid, coordinates);

//These declarations are for the game inside the while loop
	char letter;
	char letter1;
	int row;
	int col;
	int numSunk = 0;
	char waste;
	int shots = .5 * (gridSize * gridSize);
	int check1;
	printArray(grid, gridSize);
	
	while(shots > 0 && numSunk < 4) {
		printf("You have %i shots remaining!\n", shots);
		printf("Enter the coordinate for your shot:");
		scanf("%c %c %i",&waste, &letter1, &row);
		shots--;
		letter = tolower(letter1);
		col = (int)(letter) - 97;
		row = row - 1;
		if(col >= gridSize || row >= gridSize || col < 0 || row < 0) {
			printf("That shot is out of bounds!!\n");
		}
		else {
			if('x' == grid1[row][col] || 'm' == grid[row][col]){
				printf("You already hit this space!");
			}
			else if(ships[0].type == grid1[row][col]) {
				printf("You hit a ship!\n");
				grid[row][col] = 'h';
				grid1[row][col] = 'x';
				printArray(grid, gridSize);
				ships[0].maxHits--;
				if(ships[0].maxHits == 0) {
					printf("You destroyed the carrier!\n");
					for(int i = 0; i < ships[0].length; i++) {
				           grid[coordinates[0][i].row] [coordinates[0][i].col] = ships[0].type;

					}
					numSunk += 1;		
					printf("You destroyed %i ship(s)\n", numSunk);
				}
				printArray(grid, gridSize);				
			}
				
			else if(ships[1].type == grid1[row][col]){
				printf("You hit a ship!\n");
				grid[row][col] = 'h';
				grid1[row][col] = 'x';
				ships[1].maxHits--;
				if(ships[1].maxHits == 0){
				   printf("You destroyed the battle ship!\n");
				   numSunk += 1;
				   printf("You destroyed %i ship(s)\n", numSunk);
					for(int i = 0; i < ships[1].length; i++) {
						grid[coordinates[1][i].row][coordinates[1][i].col] = ships[1].type;
					}
				}
				printArray(grid, gridSize);	
			}
				
			else if(ships[2].type == grid1[row][col]){ // Checks the grid for health and location
			     check1 = 1;
			     for(int i = 0; i < ships[2].length; i++) {
				if(coordinates[2][i].row == row && coordinates[2][i].col == col) {
				    check1 = 0;
					}
			      }
			     if(check1 == 0) {
				printf("You hit a ship!\n");
				grid[row][col] = 'h';
				grid1[row][col] = 'x';
				ships[2].maxHits--;
				if(ships[2].maxHits == 0) {
				   printf("You destroyed the frigate!\n");
				   numSunk += 1;
				   printf("You destroyed %i ship(s)\n", numSunk);
				for(int i = 0; i < ships[2].length; i++) {
							grid[coordinates[2][i].row][coordinates[2][i].col] = ships[2].type;
						}
				}
				printArray(grid, gridSize);
					
					
			} 
			if(check1 == 1){
			  printf("You hit a ship!\n");
			  grid[row][col] = 'h';
			  grid1[row][col] = 'x';
		          ships[3].maxHits--;
			  if(ships[3].maxHits == 0) {
			     printf("You destroyed the frigate ship!\n");
			     numSunk += 1;
			     printf("You destroyed %i ship(s)\n", numSunk);
			     for(int i = 0; i < ships[3].length; i++) {
				grid[coordinates[3][i].row][coordinates[3][i].col] = ships[3].type;
			     }
			   }
			   printArray(grid, gridSize);
			}
		   }
		   else {
		      printf("You missed!! \n");
		      grid[row][col] = 'm';
		      grid1[row][col] = 'x';
		      printArray(grid, gridSize);
		   }

		}	
		
		if(numSunk == 4) {
		   printf("You WIN!!\n");
		   printf("Here is the original ship locations.\n");
		   printArray(winGrid, gridSize);
		}
		
		else if(numSunk < 4 && shots == 0) {
		   printf("You lose! Ran out of shots!\n");
		   printf("Here is the original ship locations.\n");
		   printArray(winGrid, gridSize);
		}
	   
	}
	deleteArray(grid, gridSize);
	deleteArray(grid1, gridSize);
	deleteArray(winGrid, gridSize);
	free(ships);
	 
	for(int i = 0; i < 4; i++){
		free(coordinates[i]);
	}
	free(coordinates);
	if(file) {
	   fclose(file);
	}
	
}
