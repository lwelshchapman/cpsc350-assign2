#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
//#include <typeinfo>

using namespace std;


//enum State { dead, alive, unknown };


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
		void determineNext(int neighbors);
		void advance();
		
		
		// MISC
		char toChar();
		string toString(bool fancy);



	private:
	
		void init(bool newNow, bool newNxt);

		bool now;	// Cell's current state: false = empty; true = occupied.
		bool nxt;	// Cell's state next generation: false = empty; true = occupied.





};
