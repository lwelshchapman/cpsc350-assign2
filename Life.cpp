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
	
	// Check if opening the input file worked
	if (!inFile.is_open()) {
		cout << "oops" << endl;
	}
	
	string temp = "";
	
	// Get first line, 
	inFile >> temp;
	int newX = stoi(temp);
	
	inFile >> temp;
	int newY = stoi(temp);
	
	init(newX, newY, newMode);
	
	int i = -1;
	
	while(!inFile.eof()) {
	
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

/*
Life::Life(Life other) {
	
	init(other->getX(), other->getY());
}
*/

void Life::init(int newX, int newY, int newMode) {
	srand(time(0));
	
	x = (newX > 0) ? newX : 10;
	y = (newY > 0) ? newY : 10;
	
	mode = newMode;
	
	prevAlive = 0;
	
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

/*
void Life::setX(int newX) {

	x = (newX > 0) ? newX : x;
}
*/

/*
void Life::setY(int newY) {
	
	y = (newY > 0) ? newY : y;
}
*/



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
void Life::createGrid() {

	grid = new Cell**[x];
	
	for(int i = 0; i < x; ++i) {
		grid[i] = new Cell*[y];

		for(int j = 0; j < y; ++j) {
			grid[i][j] = new Cell();
		}
	}
}


void Life::randomGrid(double density) {
	
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


void Life::scanNeighbors() {
	
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


void Life::nextGeneration() {
	
	prevAlive = countAlive();
	
	++genNum;
	
	//previous = grid;
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {
			
			grid[i][j]->advance();	// Advance each cell to its next state.
		}
	}
	
	
}


void Life::printGrid() {
	/*
	cout << "Gen: " << genNum << "\tDen: " << countAlive() / static_cast<double>(x * y) << endl;
	cout << getGridString(false);
	*/
	cout << getGridString(true, false);
}


string Life::getGridString(bool withGen = true, bool spaces = false) {
	
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


bool Life::isEmpty() {
	
	for(int i = 0; i < x; ++i) {
		for(int j = 0; j < y; ++j) {

			if( grid[i][j]->getNow() ) {
				return false;
			}
		}
	}
	
	return true;
}


bool Life::isStable() {
	
	return prevAlive == countAlive();

}


int Life::countAlive() {
	
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



