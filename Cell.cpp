#include "Cell.h"


// CONSTRUCTORS
Cell::Cell() {
	
	init(false, false);
}

Cell::Cell(bool newNow) {
	
	init(newNow, newNow);
}

Cell::Cell(bool newNow, bool newNxt) {
	
	init(newNow, newNxt);
}

Cell::Cell(Cell *other) {
	
	init(other->getNow(), other->getNxt());
}

void Cell::init(bool newNow, bool newNxt) {

	setNow(newNow);
	setNxt(newNxt);
	
	//Debug: cout << "Oingo" << endl;
}

Cell::~Cell() {
	
	//Debug: cout << "Boingo" << endl;
}



// MUTATORS
void Cell::setNow(bool newNow) {

	now = newNow;
}

void Cell::setNxt(bool newNxt) {

	nxt = newNxt;
}




// ACCESSORS
bool Cell::getNow() {
	
	return now;
}

bool Cell::getNxt() {
	
	return nxt;
}







// GAME FUNCTIONALITY
void Cell::determineNext(int neighbors) {
	
	
	// Impossible to have less than zero neighbors
	if(neighbors < 0) {
		//Debug: cout << "Uh oh... neighbors < 0" << endl;
	}
	
	
	// One or zero neighbors: Dies of loneliness
	else if(neighbors < 2) {
		
		nxt = false;
	}
	
	
	// Two neighbors: Remains stable
	else if(neighbors < 3) {
		
		nxt = now;
	}
	
	
	// Three neighbors: Will be occupied
	else if(neighbors < 4) {
		
		nxt = true;
	}
	
	
	// Four or more neighbors: Dies of overcrowding
	else {
		
		nxt = false;
	}

}


void Cell::advance() {
	
	now = nxt;
}






// MISC
char Cell::toChar() {
	
	return (now) ? 'X' : '-';
}

string Cell::toString(bool fancy = false) {
	
	string outStr;
	
	if(fancy) {
		outStr += "[";
		outStr += toChar();
		outStr += "]";
		
		return outStr;
	}
	else {
		return string(1, toChar());
	}
}



/*
int main() {
	
	Cell *ohBoy = new Cell();
	
	cout << ohBoy->toChar() << endl;
	
	delete ohBoy;
	
	return 0;
}
*/
