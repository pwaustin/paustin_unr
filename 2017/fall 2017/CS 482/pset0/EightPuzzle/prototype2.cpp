#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

//The 2D board for our 8-puzzle in format board[x][y]
int** board;
//The output logging file. Don't worry about this one
FILE* output;

/*
ReadBoardFile: Read board data in from a file to populate our board structure.
Arguments:
char* fname: The name of the file to read
This just reads a simple file format of a b c each line. There should be three lines.
Each of the 9 entries should go from 0-8 inclusive. If you spot a problem let us know.
Returns bool: Returns true if the file was opened and read successfuly, and false if the file could not be read
*/
bool ReadBoardFile(char* fname)
{
	FILE* file = fopen(fname, "r");
	if (file)
	{
		rewind(file);
		int a, b, c;

		board = new int*[3];
		for (int u = 0; u < 3; u++)
		{
			board[u] = new int[3];

			for (int v = 0; v < 3; v++)
			{
				board[u][v] = 0;
			}
		}

		int i = 0;
		//while (fscanf_s(file, "%d %d %d", &a, &b, &c) != EOF)
		while (fscanf(file, "%d %d %d", &a, &b, &c) != EOF)
		{
			board[0][i] = a;
			board[1][i] = b;
			board[2][i] = c;
			i++;
		}

		fclose(file);

		return true;
	}
	else
	{
		printf("Failed to read file...\n");
		return false;
	}
}

/*
LogCell: Prints the current cell traveled to and its value and saves the output to a file
Arguments:
int x: The x of the cell you are visiting
int y: The y of the cell you are visiting
In order for us to grade you, you must print the cell you are travelling to in your algorithm.
This function makes it easier for you to print the proper data. It also saves the data to a file.
Returns void: No values returned
*/
void LogCell(int x, int y)
{
	printf("(%d, %d): %d\n", x, y, board[x][y]);
	fprintf(output, "(%d, %d): %d\n", x, y, board[x][y]);
}

/*
SetartLogging: Opens the logging file for later writing
Arguments:
None
Pretty much just a wrapper for fopen so that we make sure you are writing your logging data to the right file.
Returns void: No values returned
*/
void StartLogging()
{
	output = fopen("log.txt", "w");
}

/*
EndLogging: Closes the logging file properly
Arguments:
None
Pretty much just a wrapper for fclose so that we make sure you close the right file.
Returns void: No values returned
*/
void EndLogging()
{
	fclose(output);
}

int calcDistance()
{

	int manhattan = 0;
	int distX;
	int distY;

	for ( int x = 0; x < 3; x++ )
		{

		for ( int y = 0 ; y < 3; y++ )
			{

			if ( board[x][y] != 0 )
				{
		
				distX = x - ( board[x][y] ) / 3;
				distY = y - ( board[x][y] ) % 3;
				manhattan += abs(distX) + abs(distY);

				}

			}

		}

return manhattan;

}

int calcUp(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 up on the board
	
	temp = board[xPos - 1][yPos];
	board[xPos - 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos - 1][yPos];
	board[xPos - 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int calcDown(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 down on the board
	
	temp = board[xPos + 1][yPos];
	board[xPos + 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos + 1][yPos];
	board[xPos + 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int calcLeft(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 left on the board
	
	temp = board[xPos][yPos - 1];
	board[xPos][yPos - 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos][yPos - 1];
	board[xPos][yPos - 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int calcRight(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 left on the board
	
	temp = board[xPos][yPos + 1];
	board[xPos][yPos + 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos][yPos + 1];
	board[xPos][yPos + 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int main(int argc, char** argv)
{
	//Setup
	//-----------------------------------
	if (argc == 2)
	{
		if (!ReadBoardFile(argv[1]))
			return 2;
	}
	else
	{
		printf("No file argument given...\n");
		return 1;
	}
	StartLogging();
	//-------------------------------------

//my code here

	//declare vars
	int prev = 0;
	int manhattan;
	int iterations = 0;
	int upVal;
	int downVal;
	int leftVal;
	int rightVal;
	int temp; //for swapping 0 with some other value on the board
	int xPos; //zero's location on the x axis
	int yPos; //zero's location on the y axis

	//get initial location of 0
	for ( int i = 0; i < 3; i++ )
		{
		for ( int j = 0; j < 3; j++ )
			{
cout << board[i][j] << '\t';
			if ( board[i][j] == 0 )
				{
				xPos = i;
				yPos = j;
				}
			}
cout << endl;
		}


	//get initial manhattan distance for the board that was read in

	manhattan = calcDistance();
cout << manhattan << endl;
	//loop until manhattan distance to the solution board is zero, meaning success, or -1, meaning we gave up

	while ( manhattan > 0 )
		{

		//all options are bad initially, start at 999

		upVal = 999;
		downVal = 999;
		leftVal = 999;
		rightVal = 999;

		//calculate heuristic for possible moves 

		if ( xPos != 0 && prev != 1 )
			{
			upVal = calcUp (xPos, yPos);
			}

		if ( xPos != 2 && prev != 0 )
			{
			downVal = calcDown(xPos, yPos);
			}

		if ( yPos != 0 && prev != 3)
			{
			leftVal = calcLeft(xPos, yPos);
			}
	
		if ( yPos != 2 && prev != 2 )
			{
			rightVal = calcRight(xPos, yPos);
			}

		//handle ties- randomly throw out one or the other
		
		if ( upVal == downVal )
			{
			if ( rand()%2 == 0 )
				{
				upVal = 999;
				}
			else
				downVal = 999;
			}

		if ( upVal == leftVal )
			{
			if ( rand()%2 == 0 )
				{
				upVal = 999;
				}
			else
				leftVal = 999;
			}

		if ( upVal == rightVal )
			{
			if ( rand()%2 == 0 )
				{
				upVal = 999;
				}
			else
				rightVal = 999;
			}

		if ( downVal == leftVal )
			{
			if ( rand()%2 == 0 )
				{
				downVal = 999;
				}
			else
				leftVal = 999;
			}

		if ( downVal == rightVal )
			{
			if ( rand()%2 == 0 )
				{
				downVal = 999;
				}
			else
				rightVal = 999;
			}

		if ( leftVal == rightVal )
			{
			if ( rand()%2 == 0 )
				{
				leftVal = 999;
				}
			else
				rightVal = 999;
			}

		//make the move

			//up won: move the empty block up, update the 0 position
		
			if ( upVal <= downVal && upVal <= leftVal && upVal <= rightVal )
				{

				temp = board[xPos - 1][yPos];
				board[xPos - 1][yPos] = board[xPos][yPos];
				board[xPos][yPos] = temp;
				xPos--;
cout << "went up" << endl;
prev = 0;
				}

			//down won

			else if ( downVal <= upVal && downVal <= rightVal && downVal <= leftVal )
				{

				temp = board[xPos + 1][yPos];
				board[xPos + 1][yPos] = board[xPos][yPos];
				board[xPos][yPos] = temp;
				xPos++;
cout << "went down" << endl;
prev = 1;
				}

			//left won

			else if ( leftVal <= upVal && leftVal <= downVal && leftVal <= rightVal )
				{

				temp = board[xPos][yPos - 1];
				board[xPos][yPos - 1] = board[xPos][yPos];
				board[xPos][yPos] = temp;
				yPos--;
cout << "went left" << endl;
prev = 2;
				}

			//right won

			else if ( rightVal <= upVal && rightVal <= downVal && rightVal <= leftVal )
				{

				temp = board[xPos][yPos + 1];
				board[xPos][yPos + 1] = board[xPos][yPos];
				board[xPos][yPos] = temp;
				yPos++;
cout << "went right" << endl;
prev = 3;
				}

			//report the new 0 position to log

			LogCell(xPos, yPos);
			

		//prepare for next loop

			//count this pass through - if we go over 1000 passes, we'll call it impossible

			iterations++;

			//if over, call it impossible			

			if ( iterations > 25 )
				{
				manhattan = -1;
				}

			//otherwise, keep trying with the manhattan value for the updated board

			else
				{
				manhattan = calcDistance();
				}

for ( int x = 0; x < 3; x++ )
	{
	for ( int y = 0; y < 3; y++ )
		cout << board[x][y] << '\t';

	cout << endl;

	}

		}

if ( manhattan == 0 )
	cout << "success in " << iterations + 1 << " moves" <<  endl;

else
	cout << "an epic fail..." << endl;

	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------
	return 0;
}
