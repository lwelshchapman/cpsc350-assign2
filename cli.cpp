#include <iostream>
#include <unistd.h>

#include "Life.cpp"


using namespace std;	


int main(int argc, char** argv) {
	
	// VARIABLES //
	
	// Option variables:
	unsigned int autoTime = 50000;	// Number of nanoseconds to wait when automatically advancing.
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
	
	while(true) {
		
		// Output the current generation.
		if(outputType == 0) {	// Automatic console
			cout << life->getGridString();
			usleep(autoTime);
		}
		else if(outputType < 0) {	// Manual console
			cout << life->getGridString();
			getchar();
		}
		else {	// File output
			outFile << life->getGridString();
		}
	
	
	
	
		// Check if the simulation is finished.
		if(life->isEmpty()) {
			cout << "[Gen " << life->getGen() << ": Grid is empty; 0 living cells! ]" << endl;
			break;
		}
		
		if(life->isStable()) {
			stableCount++;
			if(stableCount == stableMax) {
				cout << "[Gen " << life->getGen() << ": Grid is stable; " << stableMax << " consecutive gens with same amount of living cells!]" << endl;
				break;
			}
		}
		else {
			stableCount = 0;
		}
		
		
		
		
		// Advance to the next generation.
		life->scanNeighbors();
		life->nextGeneration();
	
	}
	
	cout << "SIMULATION COMPLETE." << endl;
	
	
	
	
	// CLEANUP //
	
	outFile.close();
	delete life;
	
	return 0;
}