/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 2: Game of Life
 * Life.h
 * Declaration of class for managing a 2D array of Cells.
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Cell.CPP"


using namespace std;

class Life {

	public:

		// CONSTRUCTORS //
		Life();
		Life(int newX, int newY);
		Life(int newX, int newY, int newMode);
		Life(string filename, int newMode);
		~Life();
		
		// MUTATORS //
		void setMode(int newMode);
		
		// ACCESSORS //
		int getGen();
		int getMode();
		int getX();
		int getY();


		// GAME FUNCTIONALITY //
		void createGrid();	// Initialize an empty grid.
		
		void randomGrid(double density);	// Randomly populate a grid based on given parameters.
		
		void scanNeighbors();	// Let each Cell determine its next state based on its current neighbors.
		
		void nextGeneration();	// Advance each cell in the grid to its next state.
		
		void printGrid();	// Prints the current grid.
		
		string getGridString(bool withGen, bool spaces);	// Returns a string representation of the current grid.
		
		bool isEmpty();	// Returns true if there are zero cells currently alive.
		
		bool isStable();	// Returns true if the next generation will be identical to the previous one.
		
		int countAlive();	// Returns the number of currently living cells.

	
	private:
	
		void init(int newX, int newY, int newMode);

		int x;	// Grid width (columns).
		int y;	// Grid height (rows).
		int mode;	// Game mode: 0 = classic; -1 = doughnut; 1 = mirror.
		
		Cell ***grid;	// Grid of cells.

		string *prevGrid;	// State of the previous grid; used to check for stable population.
		
		void saveToPrevGrid();	// Saves a record of the current grid (for checking if a grid is stable).
		
		int genNum;	// Generation number.

};
