

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

#ifndef CELL_CPP
#define CELL_CPP

#include "Cell.CPP"

#endif


using namespace std;

class Life {

	public:

		// CONSTRUCTORS //
		Life();
		Life(int newX, int newY);
		Life(int newX, int newY, int newMode);
		Life(string filename, int newMode);
		//Life(Life other);
		~Life();
		
		// MUTATORS //
		void setMode(int newMode);
		//void setX(int newX);
		//void setY(int newY);
		
		// ACCESSORS //
		int getGen();
		int getMode();
		//string getModeName();
		int getX();
		int getY();


		// GAME FUNCTIONALITY //
		void createGrid();
		
		void randomGrid(double density);
		
		void scanNeighbors();
		
		void nextGeneration();
		
		void printGrid();
		
		string getGridString(bool withGen, bool spaces);
		
		bool isEmpty();
		
		bool isStable();
		
		int countAlive();



	private:
	
		void init(int newX, int newY, int newMode);

		int x;	// Grid width.
		int y;	// Grid height.
		int mode;	// Game mode: 0 = classic; -1 = doughnut; 1 = mirror
		
		Cell ***grid;	// Grid of cells.
		//Cell ***previous;	// Previous grid; used to check for stable population.

		int prevAlive;
		
		int genNum;	// Generation number.

		

};
