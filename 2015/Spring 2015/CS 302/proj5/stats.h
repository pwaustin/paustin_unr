/** CS 302 Project 5 - statistics class specification
@file stats.h
@author Patrick Austin
@date 3/21/2015 */

#ifndef _STATS_H
#define _STATS_H
#include <fstream>
using namespace std;

/**

Statistics class. Manages and stores various operations related to tracking specified statistics
on the simulation operations. Also manages output operations to console and .csv for the statistics.

*/

class statistics{

	public:

	statistics();
	void setSimulationTime(const double&);
	double getSimulationTime() const;
	void setProcessingTime(const int&);
	int getProcessingTime() const;
	void setAvgWaitTime(const double&);
	double getAvgWaitTime() const;
	void setMaxWaitTime(const int&);
	int getMaxWaitTime() const;
	void setAvgLineLength(const double&);
	double getAvgLineLength() const;
	void setMaxLineLength(const int&);
	int getMaxLineLength() const;
	void setIdleTime(const int&, const int&);
	int getIdleTime(const int&) const;
	void reset();
	void outputToConsole(const int&, const int&) const;
	void initCSVOutput();
	void outputToCSV(const char&, const int&, const int&);
	void endCSVOutput();


	private:

	ofstream fout;
	double simulationTime;
	int processingTime;
	double avgWaitTime;
	int maxWaitTime;
	double avgLineLength;
	int maxLineLength;
	int idleTime1;
	int idleTime2;
	int idleTime3;

	};

#endif
