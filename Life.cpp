/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 2: Game of Life
 * Life.cpp
 * Definition of class for managing a 2D array of Cells.
 */

#include "Life.h"

// CONSTRUCTORS //
Life::Life() {
	
	init(10, 10, 0);
}

Life::Life(int newX, int newY) {
	
	init(newX, newY, 0);
}

Life::Life(int newX, int newY, int newMode) {
	
	init(newX, newY, newMode);
}

Life::Life(string filename, int newMode = 0) {
	
	// Open input file
	ifstream inFile;
	inFile.open(filename);
	
	// If opening the input file worked:
	if (inFile.is_open()) {
		string temp = "";
		
		// Get first line (# of columns).
		inFile >> temp;
		int newX = stoi(temp);
		
		// Get second line (# of rows).
		inFile >> temp;
		int newY = stoi(temp);
		
		// Initialize the Life object.
		init(newX, newY, newMode);
		
		// Read in the grid map and set each cell accordingly.
		int i = -1;
		while(!inFile.eof() && (i < newX - 1)) {
			
			inFile >> temp;
		
			i++;
			
			for(int j = 0; j < temp.size(); ++j) {
				
				if(tolower(temp[j]) == 'x') {
					grid[i][j]->setNow(true);
				}
			}
		}
		
		inFile.close();
	}
	// If opening the input file DID NOT WORK:
	else {
		cout << "There was a problem with opening that input file. Exiting." << endl;
		exit(EXIT_FAILURE);
	}
	
}

void Life::init(int newX, int newY, int newMode) {
	srand(time(0));
	
	x = (newX > 0) ? newX : 10;
	y = (newY > 0) ? newY : 10;
	
	mode = newMode;
	
	genNum = 0;
	
	createGrid();
}

Life::~Life() {

	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
			delete grid[i][j];
		}
	}
	
	delete grid;
	
	//Debug: cout << "Grid deleted. Deleting life." << endl;
}

// MUTATORS //
void Life::setMode(int newMode) {
	mode = newMode;
}



// ACCESSORS //
int Life::getGen() {
	return genNum;
}

int Life::getMode() {
	return mode;
}

int Life::getX() {
	return x;
}

int Life::getY() {
	return y;
}





// GAME FUNCTIONALITY //
void Life::createGrid() {	// Initialize an empty grid.

	grid = new Cell**[x];
	prevGrid = new string[x];

	for(int i = 0; i < x; ++i) {
		grid[i] = new Cell*[y];
		prevGrid[i] = "";
		for(int j = 0; j < y; ++j) {
			grid[i][j] = new Cell();
			prevGrid[i] += "-";
		}
	}
	
}


void Life::randomGrid(double density) {	// Randomly populate a grid based on given parameters.
	
	if( (density > 0) && (density <= 1) ) {
	
		int total = x * y;
		
		int toFill = round(total * density);
		
		bool randGrid[x][y] = {};
		
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < y; ++j) {
				randGrid[i][j] = false;
			}
		}
		
		while(toFill > 0) {

			int randX = rand() % x;
			int randY = rand() % y;
			
			if( !(randGrid[randX][randY]) ) {
				randGrid[randX][randY] = true;
				--toFill;
			}
		}
		
		/*
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < y; ++j) {
				cout << randGrid[i][j] << " ";
			}
			cout << endl;
		}
		*/
		
		
		
		//!!FIX: Now enable/disable cells in grid based on randGrid!!
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < y; ++j) {
				grid[i][j]->setNow(randGrid[i][j]);
				//grid[i][j]->setNxt(false);
			}
		}
		
	}
	else {
		cout << "Invalid density." << endl;
	}
}


void Life::scanNeighbors() {	// Let each Cell determine its next state based on its current neighbors.
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
			
			// For each cell:
		
			int count = 0;
		
			for(int u = i - 1; u <= i + 1; ++u) {
				for(int v = j - 1; v <= j + 1; ++v) {
					
					// For each of the positions neighboring that cell:
					
					if( !((u == i) && (v == j)) ) {	// Do not count the current cell as a neighbor.
					
						bool inc = false;
					
						// Classic mode
						if(mode == 0) {
							
							if( !( (u < 0) || (u >= x) || (v < 0) || (v >= y) ) ) {	// Only consider cells found on the grid.
								inc = grid[u][v]->getNow();
							}
						}
						// Doughnut mode
						else if(mode < 0) {
							
							int du = (u < 0) ? x - 1 : u;	// If checking over left side, roll over to right side.
							du = (u >= x) ? 0 : du;	// If checking over right side, roll over to left side.
							
							int dv = (v < 0) ? y - 1 : v;	// If checking under bottom, roll over to top.
							dv = (v >= y) ? 0 : dv;	// If checking over top, roll over to bottom.
							
							inc = grid[du][dv]->getNow();	// Check cell at rolled-over coords.
							
						}
						// Mirror mode
						else {
							
							int mu = (u < 0) ? 0 : u;	// If checking over left side, mirror left side.
							mu = (u >= x) ? x - 1 : mu;	// If checking over right side, mirror right side.
							
							int mv = (v < 0) ? 0 : v;	// If checking under bottom, mirror bottom.
							mv = (v >= y) ? y - 1 : mv;	// If checking over top, mirror top.
							
							inc = grid[mu][mv]->getNow();	// Check cell at mirrored coords.
							
						}
					
					
						if(inc) {
							count++;	// Increment the number of neighbors if a valid neighbor was found.
						}
					
					
					}					
				}
			}

			grid[i][j]->determineNext(count);	// Cell determines its next state based on current neighbor amount.
			
		}
	}
	
	
}


void Life::nextGeneration() {	// Advance each cell in the grid to its next state.
	
	saveToPrevGrid();
	
	++genNum;
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
			
			grid[i][j]->advance();	// Advance each cell to its next state.
		}
	}
	
	
}


void Life::saveToPrevGrid() {	// Saves a record of the current grid (for checking if a grid is stable).
	
	for(int i = 0; i < x; ++i) {
		
		prevGrid[i] = "";
		
		for(int j = 0; j < y; ++j) {
			
			prevGrid[i] += grid[i][j]->getNow();
		
		}
	}
	
}


void Life::printGrid() {	// Prints the current grid.

	cout << getGridString(true, false);
}


string Life::getGridString(bool withGen = true, bool spaces = false) {	// Returns a string representation of the current grid.
	
	string outStr = "";
	
	if(withGen) {
		outStr += to_string(genNum) + "\n";
	}
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
		
			outStr += grid[i][j]->toChar();
			if( (j < y - 1) && (spaces) ) {
				outStr += " ";
			}
		}
		outStr += "\n";
	}
	
	return outStr;
}


bool Life::isEmpty() {	// Returns true if there are zero cells currently alive.
	
	return (countAlive() == 0);
}


bool Life::isStable() {	// Returns true if the next generation will be identical to the previous one.
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
			if(grid[i][j]->getNxt() != prevGrid[i][j]) {
				return false;
			}
		}
	}
	return true;
}


int Life::countAlive() {	// Returns the number of currently living cells.
	
	int alive = 0;
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
	
			if(grid[i][j]->getNow()) {
				++alive;
			}
		}
	}

	return alive;
}



