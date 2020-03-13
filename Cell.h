/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 2: Game of Life
 * Life.cpp
 * Declaration of class for a single cell within a Game of Life grid.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;


class Cell {

	public:
	
		// CONSTRUCTORS
		Cell();
		Cell(bool newNow);
		Cell(bool newNow, bool newNxt);
		Cell(Cell *other);
		~Cell();

		
		// MUTATORS
		void setNow(bool newNow);
		void setNxt(bool newNxt);
		
		// ACCESSORS
		bool getNow();
		bool getNxt();
		
		
		// GAME FUNCTIONALITY
		void determineNext(int neighbors);	// Determine the cell's next state based on its current neighbors.
		void advance();	// Shift to the next state.
		
		
		// MISC
		char toChar();
		string toString(bool fancy);



	private:
	
		void init(bool newNow, bool newNxt);

		bool now;	// Cell's current state: false = empty; true = occupied.
		bool nxt;	// Cell's state next generation: false = empty; true = occupied.

};
