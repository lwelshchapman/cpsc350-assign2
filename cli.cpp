/* 
 * Logan Welsh
 * 2325215
 * lwelsh@chapman.edu
 * CPSC-350-01
 * Assignment 2: Game of Life
 * cli.cpp
 * Command-Line Interface for running Game of Life.
 */

#include <iostream>
#include <unistd.h>

#include "Life.cpp"


using namespace std;	


int main(int argc, char** argv) {
	
	// VARIABLES //
	
	// Option variables:
	unsigned int autoTime = 100000;	// Number of nanoseconds to wait when automatically advancing.
	unsigned int stableMax = 3;	// Number of consecutive generations with the same amount of living cells needed to be considered "stable".

	// Internal variables used by the program:
	unsigned int stableCount = 0;
	bool fileInput = false;
	int outputType = 0;
	string outPath = "";
	ofstream outFile;
	
	// Life instance:
	Life *life;
	
	
	
	
	// OPTION PROMPTS //
	
	// Map file input or random generation?
	bool keepAskingFile = true;
	while(keepAskingFile) {
		string response = "";
		cout << "Do you have a map file you want to use? (y/n)\n  > ";
		cin >> response;
		
		if(tolower(response[0]) == 'y') {
			fileInput = true;
			keepAskingFile = false;
		}
		else if(tolower(response[0]) == 'n') {
			fileInput = false;
			keepAskingFile = false;
		}
		else {
			cout << "Sorry, didn't understand your response." << endl;
		}
	}
	cout << endl;
	
	
	// If using an input file, get the filename.
	if(fileInput) {
		
		string inPath = "";
		cout << "Name of file to use:\n  > ";
		cin >> inPath;

		life = new Life(inPath);
	}
	// If generating randomly, get parameters.
	else {
		
		cout << "Will randomly generate a map." << endl;
		
		string temp = "";
		
		int cols = 0;
		cout << "Number of columns:\n  > ";
		cin >> temp;
		cols = stoi(temp);
		
		int rows = 0;
		cout << "Number of rows:\n  > ";
		cin >> temp;
		rows = stoi(temp);
		
		double dens = 0.0;
		bool keepAskingDens = true;
		while(keepAskingDens) {
			cout << "Density (amount of filled cells, as a decimal between 0.0 and 1.0:\n  > ";
			cin >> temp;
			dens = stod(temp);
			if( (dens <= 0) || (dens > 1) ) {
				cout << "Sorry, that density is outside the valid range." << endl;
			}
			else {
				keepAskingDens = false;
			}
		}
		
		life = new Life(rows, cols);
		life->randomGrid(dens);
	}
	cout << endl;
	

	// Which mode?
	bool keepAskingMode = true;
	while(keepAskingMode) {
		string mode = "";
		cout << "Classic, Doughnut, or Mirror mode? (c, d, m)\n  > ";
		cin >> mode;
		
		switch(tolower(mode[0])) {
			
			case 'c':
				life->setMode(0);
				keepAskingMode = false;
				break;
			case 'd':
				life->setMode(-1);
				keepAskingMode = false;
				break;
			case 'm':
				life->setMode(1);
				keepAskingMode = false;
				break;
			default:
				cout << "Sorry, didn't understand your response." << endl;
		}
		
	}
	cout << endl;
	
	
	// What kind of output?
	bool keepAskingOutput = true;
	while(keepAskingOutput) {
		
		string temp = "";
		cout << "Automatic advance, Manual advance, or File output? (a, m, f)\n  > ";
		cin >> temp;
		
		switch(tolower(temp[0])) {
			
			case 'a':
				outputType = 0;
				keepAskingOutput = false;
				break;
			
			case 'm':
				outputType = -1;
				keepAskingOutput = false;
				break;
			
			case 'f':
				outputType = 1;
				keepAskingOutput = false;
				break;
			
			default:
				cout << "Sorry, didn't understand your response." << endl;
		}
		
	}
	cout << endl;
	
	
	// If writing to file, get the filename.
	if(outputType > 0) {
		cout << "Name for output file:\n  > ";
		cin >> outPath;
		outFile.open(outPath);
		cout << endl;
	}
	
	cin.ignore();	// Get rid of trailing newlines for manual advancing.
	
	
	
	
	
	// SIMULATION //
	
	cout << "BEGINNING SIMULATION." << endl;
	
	while( (!(life->isEmpty()) && !(life->isStable())) || (life->getGen() == 0) ) {
		
		// Output the current generation.
		if(outputType > 0) {	// File output
			outFile << life->getGridString();
		}
		else {					// Console output
			cout << life->getGridString();
		}


		// Advance to the next generation.
		life->scanNeighbors();
		if(life->isStable()) {	// Checking here helps catch oscillations.
			break;
		}
		life->nextGeneration();
		
		
		// Wait if necessary.
		if(outputType == 0) {		// Automatic console
			usleep(autoTime);
		}
		else if(outputType < 0) {	// Manual console
			getchar();
		}
		
		
	}
	
	
	
	// Tell the user why the simulation is finishing.
	string message = "";
	if(life->isEmpty()) {
		message = "Grid is empty; 0 living cells!";
	}
	else if(life->isStable()) {
		message = "Grid is stable; Generation stagnant or oscillating!";
	}
	cout << "[Gen " << life->getGen() << ": " << message << "]" << endl;
	cout << "SIMULATION COMPLETE." << endl;
	
	
	
	
	// CLEANUP //
	
	outFile.close();	// Close the file output stream.
	delete life;	// Deallocate memory used by the Life object.
	
	return 0;
}