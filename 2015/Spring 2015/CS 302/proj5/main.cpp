/** CS 302 Project 5 - main program for bank queue simulation
@file main.cpp
@author Patrick Austin
@date 3/21/2015 */

#include <iostream>
#include <fstream>
#include <ctime>
#include "queues.h"
#include "event.h"
#include "simA.h"
#include "simN.h"
using namespace std;

int main()
	{

	int index;

	//create simulation objects

	simA testA;
	simN testN;

	//title

	cout << "CS 302 Project 5: Event Simulation" << endl << endl;

	//part 1 runs 10 values with full console output for each simulation for array and node implementations
	//just in case you doubted it was working ;)

	cout << "Part 1: Simulation Demos With Console Output:" << endl << endl;

	bool noisy = true;

	cout << "Array based demos:" << endl << endl;

		cout << "Array based One Teller One Queue simulation: 10 values, 1 iteration:" << endl << endl;
		testA.simOne( noisy, 10 );
		testA.outputToConsole(1, 10);
		testA.resetStats();

		cout << "Array based Three Tellers Three Queues simulation: 10 values, 1 iteration:" << endl << endl;
		testA.simTwo( noisy, 10 );
		testA.outputToConsole(2, 10);
		testA.resetStats();

		cout << "Array based Three Tellers One Queue simulation: 10 values, 1 iteration:" << endl << endl;
		testA.simThree ( noisy, 10 );
		testA.outputToConsole(3, 10);
		testA.resetStats();

	cout << "Node based demos:" << endl << endl;

		cout << "Node based One Teller One Queue simulation: 10 values, 1 iteration:" << endl << endl;
		testN.simOne( noisy, 10 );
		testN.outputToConsole(1, 10);
		testN.resetStats();

		cout << "Node based Three Tellers Three Queues simulation: 10 values, 1 iteration:" << endl << endl;
		testN.simTwo( noisy, 10 );
		testN.outputToConsole(2, 10);
		testN.resetStats();

		cout << "Node based Three Tellers One Queue simulation: 10 values, 1 iteration:" << endl << endl;
		testN.simThree ( noisy, 10 );
		testN.outputToConsole(3, 10);
		testN.resetStats();

	//part 2 title

	cout << "Part 2: Big Data Simulation" << endl << endl;

	noisy = false;

	testA.initCSVOutput();

	//evaluate 100 000 values 10x for each simulation for array and node based; print stats to console and spreadsheet

	cout << "100 000 value simulations (array based):" << endl << endl;

		for ( index = 0; index < 10; index++ )
			testA.simOne(noisy, 100000);

		cout << "Array based One Teller One Queue simulation: 100 000 values, 10 iterations:" << endl;
		testA.outputToConsole(1, 100000);
		testA.outputToCSV(1, 100000);
		testA.resetStats();

		for ( index = 0; index < 10; index++ )
			testA.simTwo(noisy, 100000);

		cout << "Array based Three Tellers Three Queues simulation: 100 000 values, 10 iterations:" << endl;
		testA.outputToConsole(2, 100000);
		testA.outputToCSV(2, 100000);
		testA.resetStats();

		for ( index = 0; index < 10; index++ )
			testA.simThree(noisy, 100000);

		cout << "Array based Three Tellers One Queue simulation: 100 000 values, 10 iterations:" << endl;
		testA.outputToConsole(3, 100000);
		testA.outputToCSV(3, 100000);
		testA.resetStats();

	testA.endCSVOutput();

	cout << "100 000 value simulations (node based):" << endl << endl;

	testN.initCSVOutput();

		for ( index = 0; index < 10; index++ )
			testN.simOne(noisy, 100000);

		cout << "Node based One Teller One Queue simulation: 100 000 values, 10 iterations:" << endl;
		testN.outputToConsole(1, 100000);
		testN.outputToCSV(1, 100000);
		testN.resetStats();

		for ( index = 0; index < 10; index++ )
			testN.simTwo(noisy, 100000);

		cout << "Node based Three Tellers Three Queues simulation: 100 000 values, 10 iterations:" << endl;
		testN.outputToConsole(2, 100000);
		testN.outputToCSV(2, 100000);
		testN.resetStats();

		for ( index = 0; index < 10; index++ )
			testN.simThree(noisy, 100000);

		cout << "Node based Three Tellers One Queue simulation: 100 000 values, 10 iterations:" << endl;
		testN.outputToConsole(3, 100000);
		testN.outputToCSV(3, 100000);
		testN.resetStats();

	testN.endCSVOutput();

	cout << "Summary data has been output to 'output.csv', ending program ... " << endl;

	//end program

	return 0;

	}

