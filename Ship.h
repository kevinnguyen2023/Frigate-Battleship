#ifndef SHIP_H
#define SHIP_H

struct Ship {
   char type;
   int vert;
   int row;
   int col;
   int length;
   int maxHits;
};

struct locations {
   int row;
   int col;
};

struct Ship initializeShip(char type);
struct Ship makeOutOfBounds(int gridSize);
void addShip(struct Ship* ships, int gridSize, char** grid, char** winGrid, struct locations** location);
void spaces(struct Ship ships, struct locations* location);
int random2(int range);
#endif
