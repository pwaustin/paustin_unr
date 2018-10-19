//part B: creates and prints table of subproblems and an optimal value for the
//optimization problem

//note: uses hard-coded problem size of 9 weeks for clarity of code. 
//modification for i weeks should be self-explanatory

#include <iostream>
#include <cstdlib>
using namespace std;

//prototypes

int schedule (int rValue, int cValue, int* weights);

int main()
{

//declare specified sample values for testing the algorithm

//r*s[i] is the cost of shipping with A for one week
int r = 1;

//c is the cost of shipping with B for one week (but must book 4 consecutive weeks)
int c = 10;

//supplyValues[i] is the number of pounds that must be shipped for week i (9 weeks hard-coded)
int supplyValues[] = {11, 9, 9, 12, 12, 12, 12, 9, 9, 11};

//int result to denote total cost of the schedule
int result;

//run the algorithm on the sample values. will print table containing solutions to subproblems
result = schedule(r, c, supplyValues);	

//spit out results to the console

cout << "Part B: An optimal schedule will cost " << result << "." << endl << endl;

//end program

return 0;

}

//implementations

int schedule (int rValue, int cValue, int* weights)
{

int i = 0;

//order of business: create table containing solutions to the subproblems. 
//Will have 2 rows, optimalA and optimalB
//optimalA will contain the total cost at week i for choosing A,
//assuming optimal choices were made in the previous i-1 weeks.
int optimalA[9];
//optimalB will contain the total cost at week i for choosing B,
//assuming optimal choices were made in the previous i-1 weeks.
int optimalB[9];

//zero out the table

for ( i = 0; i <= 9; i++ )
	{
	optimalA[i] = 0;
	optimalB[i] = 0;
	}

//calculate values for the first week - base case, no subproblems
optimalA[0] = weights[0] * rValue;	//cost of A for week 0 is simply s[0] * r
optimalB[0] = 4*cValue;			//cost of B for week 0 is simply 4c

//for each subsequent week, add the current week's choice + 
//the optimal solution for the previous weeks

for ( i = 1; i <= 9; i++ )
	{
	if ( (i-4) < 0 )	//case to avoid accessing negative indices- refer to optB[0] instead of optB[neg value]
		{
		optimalA[i] = std::min(optimalA[i-1], optimalB[0]) 	//cost of choosing A is optimal prior + s[i]*r
					+ (weights[i] * rValue);
		optimalB[i] = std::min(optimalA[i-1], optimalB[0]) 	//cost of choosing B is optimal prior + 4*c
					+ (4 * cValue);
		} 

	else			//normal case
		{
		optimalA[i] = std::min(optimalA[i-1], optimalB[i-4])    //cost of choosing A is optimal prior + s[i]*r
					+ (weights[i] * rValue);
		optimalB[i] = std::min(optimalA[i-1], optimalB[i-4]) 	//cost of choosing B is optimal prior + 4*c
					+ (4 * cValue);			
		}
	}

//table built, spit to console

cout << "Part B: Table of Subproblems" << endl;
cout << "Week      ";
for ( i = 0; i <= 9; i++ )
	cout << i << '\t';
cout << endl;
cout << "-----------------------------------------------------------------------------------" << endl;
cout << "Choose A: ";
for ( i = 0; i <= 9; i++ )
	cout << optimalA[i] << '\t';
cout << endl << "Choose B: ";
for ( i = 0; i <= 9; i++ )
	cout << optimalB[i] << '\t';
cout << endl << endl;

//now, calculate the result

return std::min(optimalA[9], optimalB[9]);	//as expected, optimal result is min between
						//r*s[i] + opt(i-1) and 4*c + opt(i-4)
}
