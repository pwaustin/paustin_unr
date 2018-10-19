#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

//globals

int POS_INFINITY =  100000000;
int NEG_INFINITY =  POS_INFINITY * -1;
int WIN_HEURISTIC = 1000000;

//structs

struct node
{ int board[4][4][4]; };

struct Move {
	int x;
	int y;
	int z;
};

/*

Heuristic function: return an estimate of how good a board is, with neg values denoting favorable boards for P2 and
pos values denoting favorable boards for P1. Returns + or - WIN_HEURISTIC for a terminal board, so can be used in lieu
of a seperate terminal test function.

Algorithm: Consider each possible way to win for P1 and P2, giving an increasingly better heuristic for controlling 
1/2/3 spots on that "lane", unless the lane is blocked by the opponent at some point in which case it's worthless. 
If 4 spots on the lane, abort immediately and return currentPlayer * MAX_HEURISTIC, as that means a terminal board.

To accomplish this, go through the ways to win from each player's POV. Track usefulness of each space on the board
in the utilization array. Then, use the utilization array to calculate the heuristic value. On the
first round we consider P2 and subtract from the heuristic value, on round 2 we consider P1 and add.

*/

int heuristic ( int board[4][4][4] )
	{
	
	int i,j,k;
	int currentPlayer;
	int h = 0;
	int opponent;
	int utilization[4][4][4];
	int tally;

	for ( currentPlayer = -1; currentPlayer < 2; currentPlayer += 2 )	//run through the options twice: first for P2 and then for P1
		{

		//initialize the utlization board. spaces with moves will have a value of 5, spaces with no moves start at 0

		opponent = currentPlayer * -1;

		for ( i = 0; i < 4; i++ )
			for ( j = 0; j < 4; j++ )
				for ( k = 0; k < 4; k++ )
					{
					if ( board[i][j][k] != 0 )
						utilization[i][j][k] = 5;
					else
						utilization[i][j][k] = 0;
					}

		//enumerate and handle ways to win: x/y/z straight lines, 2d diagonals, 3d diagonals. 
		//prepare to enter the realm of pure excitement, better take your heart meds because hoo boy

			//handle x/y/z straight lines

			for ( i = 0; i < 4; i++ )
				for ( j = 0; j < 4; j++ )
					{

					tally = 0;

					for ( k = 0; k < 4; k++ )
						{

						if ( board[i][j][k] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[i][j][k] == currentPlayer )
							tally++;

						}		

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( k = 0; k < 4; k++ )
							{

							if ( utilization[i][j][k] < tally )
								utilization[i][j][k] = tally;

							}

						}
								
					}

			for ( i = 0; i < 4; i++ )
				for ( j = 0; j < 4; j++ )
					{

					tally = 0;

					for ( k = 0; k < 4; k++ )
						{

						if ( board[i][k][j] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[i][k][j] == currentPlayer )
							tally++;

						}		

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( k = 0; k < 4; k++ )
							{

							if ( utilization[i][k][j] < tally )
								utilization[i][k][j] = tally;

							}

						}
								
					}	 

			for ( i = 0; i < 4; i++ )
				for ( j = 0; j < 4; j++ )
					{

					tally = 0;

					for ( k = 0; k < 4; k++ )
						{

						if ( board[k][i][j] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[k][i][j] == currentPlayer )
							tally++;

						}		

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( k = 0; k < 4; k++ )
							{

							if ( utilization[k][i][j] < tally )
								utilization[k][i][j] = tally;

							}

						}
								
					}

			//handle 2d diagonals on x/y/z planes

			for ( i = 0; i < 4; i++ )
				{
				
				tally = 0;

				for ( j = 0; j < 4; j++ )
					{

					if ( board[i][j][j] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[i][j][j] == currentPlayer )
							tally++;
					}

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( j = 0; j < 4; j++ )
							{

							if ( utilization[i][j][j] < tally )
								utilization[i][j][j] = tally;

							}

						}				

				tally = 0;

				for ( j = 0; j < 4; j++ )
					{

					if ( board[i][3-j][j] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[i][3-j][j] == currentPlayer )
							tally++;
					}

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( j = 0; j < 4; j++ )
							{

							if ( utilization[i][3-j][j] < tally )
								utilization[i][3-j][j] = tally;

							}
						}				
				}

			for ( i = 0; i < 4; i++ )
				{
				
				tally = 0;

				for ( j = 0; j < 4; j++ )
					{

					if ( board[j][i][j] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[j][i][j] == currentPlayer )
							tally++;
					}

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( j = 0; j < 4; j++ )
							{

							if ( utilization[j][i][j] < tally )
								utilization[j][i][j] = tally;

							}

						}				

				tally = 0;

				for ( j = 0; j < 4; j++ )
					{

					if ( board[3-j][i][j] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[3-j][i][j] == currentPlayer )
							tally++;
					}

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( j = 0; j < 4; j++ )
							{

							if ( utilization[3-j][i][j] < tally )
								utilization[3-j][i][j] = tally;

							}
						}				
				}
		
			for ( i = 0; i < 4; i++ )
				{
				
				tally = 0;

				for ( j = 0; j < 4; j++ )
					{

					if ( board[j][j][i] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[j][j][i] == currentPlayer )
							tally++;
					}

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( j = 0; j < 4; j++ )
							{

							if ( utilization[j][j][i] < tally )
								utilization[j][j][i] = tally;

							}

						}				

				tally = 0;

				for ( j = 0; j < 4; j++ )
					{

					if ( board[j][3-j][i] == opponent )
							{

							tally = -1;
							break;

							}			
						else if ( board[j][3-j][i] == currentPlayer )
							tally++;
					}

					if ( tally == 4 )
						{

						return currentPlayer * WIN_HEURISTIC;

						}

					if ( tally != -1 )
						{

						for ( j = 0; j < 4; j++ )
							{

							if ( utilization[j][3-j][i] < tally )
								utilization[j][3-j][i] = tally;

							}
						}				
				}

			//handle 3d diagonals: 4 ways to win

				//way 1

				tally = 0;

				for ( i = 0; i < 4; i++ )
					{

					if ( board[i][i][i] == opponent )
						{

						tally = -1;
						break;

						}			
					else if ( board[i][i][i] == currentPlayer )
						tally++;

					}

				if ( tally == 4 )
					{

					return currentPlayer * WIN_HEURISTIC;

					}

				if ( tally != -1 )
					{

					for ( i = 0; i < 4; i++ )
						{

						if ( utilization[i][i][i] < tally )
							utilization[i][i][i] = tally;

						}
					}

				//way 2

				tally = 0;

				for ( i = 0; i < 4; i++ )
					{

					if ( board[3-i][i][i] == opponent )
						{

						tally = -1;
						break;

						}			
					else if ( board[3-i][i][i] == currentPlayer )
						tally++;

					}

				if ( tally == 4 )
					{

					return currentPlayer * WIN_HEURISTIC;

					}

				if ( tally != -1 )
					{

					for ( i = 0; i < 4; i++ )
						{

						if ( utilization[3-i][i][i] < tally )
							utilization[3-i][i][i] = tally;

						}
					}	

				//way 3

				tally = 0;

				for ( i = 0; i < 4; i++ )
					{

					if ( board[i][3-i][i] == opponent )
						{

						tally = -1;
						break;

						}			
					else if ( board[i][3-i][i] == currentPlayer )
						tally++;

					}

				if ( tally == 4 )
					{

					return currentPlayer * WIN_HEURISTIC;

					}

				if ( tally != -1 )
					{

					for ( i = 0; i < 4; i++ )
						{

						if ( utilization[i][3-i][i] < tally )
							utilization[i][3-i][i] = tally;

						}
					}		

				//way 4

				tally = 0;

				for ( i = 0; i < 4; i++ )
					{

					if ( board[3-i][3-i][i] == opponent )
						{

						tally = -1;
						break;

						}			
					else if ( board[3-i][3-i][i] == currentPlayer )
						tally++;

					}

				if ( tally == 4 )
					{

					return currentPlayer * WIN_HEURISTIC;

					}

				if ( tally != -1 )
					{

					for ( i = 0; i < 4; i++ )
						{

						if ( utilization[3-i][3-i][i] < tally )
							utilization[3-i][3-i][i] = tally;

						}
					}

			//still awake? let's add it all up to get a final heuristic value for this player

			for ( i = 0; i < 4; i++ )
				{
				for ( j = 0; j < 4; j++ )
					{
					for ( k = 0; k < 4; k++ )
						{

						if ( utilization[i][j][k] == 1 )
							h += currentPlayer * 1;

						else if ( utilization[i][j][k] == 2 )
							h += currentPlayer * 10;

						else if ( utilization[i][j][k] == 3 )
							h += currentPlayer * 1000;
						}
					}
				}	

		}

	//whew, we made it: return the final heuristic, the sum of the two runs

	return h;

	}

/*

Alphabeta search function: conduct ab search on the current node up to the specified ply.

Next node holds the final board chosen by the search. isRoot should be high on the first search call, where tracking the next board matters,
and will be low on all recursive calls. Alpha and beta are used for pruning and should be initially set to NEG_INFINITY and POS_INFINITY 
respectively. 

*/

int alphabeta ( node current, node& next, int ply, int alpha, int beta, int player, bool isRoot )
	{

	int i, j, k;
	int h;
	int value;
	int ab;
	node temp;
	node nextCandidate;
	vector<node> children;







	//TODO: if we're near the specified time threshold, stop searching- treat this as a losing board






	//calculate heuristic. if this is a final state or we've reached the ply specified, stop searching

	h = heuristic(current.board);

	if ( h == WIN_HEURISTIC || h == ( -1 * WIN_HEURISTIC ) || ply == 0  )
		{

		//if the root is terminal, output current move

		if ( isRoot )
			{

			next = current;

			}

		//return the heuristic value for this board

		return h;

		}

	//otherwise, search. first, generate child nodes

	for ( i = 0; i < 4; i++ )
		for ( j = 0; j < 4; j++ )
			for ( k = 0; k < 4; k++ )
				{

				//every spot on the given board with a 0 represents a possible move. Add each of these boards to the children vector

				if ( current.board[i][j][k] == 0 )
					{

					//if a move is possible, copy the current board to a temp, add the move, and push the new node

					temp = current;

					temp.board[i][j][k] = player;

					children.push_back(temp);

					}

				}

	//maximize for player 1

	if ( player == 1 ) 
		{

		//consider each possible child board, maintaining highest board found so far. initially, this value is low

		value = NEG_INFINITY;

		for ( i = 0; i < children.size(); i++ )
			{

			//alphabeta the child board, get a value

			ab = alphabeta(children[i], temp, ply - 1, alpha, beta, -1, false);

			//if this is the best board we've found so far on the uppermost ply, it's the new candidate for our move

			if ( ab > value && isRoot )
				{
				next = children[i];
				}

			//prune if possible

			value = max(value, ab);

			alpha = max(alpha, value);

			if ( beta <= alpha )
				{
				break;
				}

			}

		return value;

		}

	//minimize for player 2

	else if ( player == -1 )
		{

		//consider each possible child board, maintaining lowest board found so far. initially, this value is high

		value = POS_INFINITY;

		for ( i = 0; i < children.size(); i++ )
			{

			//alphabeta the child board, get its value

			ab = alphabeta(children[i], temp, ply - 1, alpha, beta, 1, false);

			//if this is the best board we've found so far on the uppermost ply, it's the new candidate for our move

			if ( ab < value && isRoot )
				{
				next = children[i];
				}

			//prune if possible

			value = min(value, ab);

			beta = min(beta, value);

			if ( beta <= alpha )
				{
				break;
				}

			}

		return value;

		}

	}


/*
	read_from_file: reads the board from a file
	args:
		char* inputfilename: filename to be read
		int board[][4][4]: array to store board
	returns: 0 if all is well; -2 if the file cannot be opened for reading
*/

int read_from_file( char* inputfilename, int board[][4][4] );

/*
	write_to_file: writes the board from a file
	args:
		char* outputfilename: filename to be written
		int board[4][4][4]: array to store board
	returns: 0 if all is well; -2 if the file cannot be opened for writing
*/

int write_to_file( char* outputfilename, int board[4][4][4] );

/*
	print_move_to_screen: prints the board so that the autograder should be able to read your answer
	args:
		Move m: struct storing the x,y,z coordinate of the square to move to
	returns: void
*/
void print_move_to_screen( Move m);

int main( int argc, char* argv[] )
{

	char* inputfilename = NULL, *outputfilename = NULL;
	int board[4][4][4];
	Move m = {0,0,0};
	int ply = 0;


	int i, j, k;
	node given;
	node next;

	// parse command-line arguments
	for( i = 1; i < argc; i++ )
	{
		// input file
		if( !strcmp(argv[i], "-i" ) )
		{
			inputfilename = argv[i+1];
			i++;
		}
		// output file
		else if( !strcmp( argv[i], "-o") )
		{
			outputfilename = argv[i+1];
			i++;
		}
		// number of ply to search ahead
		else if( !strcmp( argv[i], "-p") )
		{
			ply = atoi(argv[i+1]);
			i++;
		}
	}

	// check to make sure command-line arguments have been specified
	if( inputfilename == NULL || outputfilename == NULL )
	{
		printf( "input and output filenames need to be specified on the command line (-i <filename> -o <filename>\n");
		return -1;
	}

	if( ply <= 0 )
	{
		printf( "need to have ply set to be greater than 0 (use -p <ply>)\n");
		return -1;
	}

	// read from file
	read_from_file( inputfilename, board );

//my code here

//search for the best move

	//determine whose turn it is: if sum of moves on board == 0 then P1, else P2

	int tally = 0;
	int player;

	for ( i = 0; i < 4; i++ )
		for ( j = 0; j < 4; j++ )
			for ( k = 0; k < 4; k++ )
				{
				tally += board[i][j][k];
				}

	if ( tally == 0 )
		player = 1;
	else
		player = -1;

	//copy the read in board to a node object

	for ( i = 0; i < 4; i++ )
		for ( j = 0; j < 4; j++ )
			for ( k = 0; k < 4; k++ )
				{
				given.board[i][j][k] = board[i][j][k];
				}


	//for all boards reachable at the given ply, search for a winning terminal board or board with best heuristic
	//the node variable next will hold the board which was found

	alphabeta (given, next, ply, NEG_INFINITY, POS_INFINITY, player, true);

	//extract move by comparing given with next: the move was the location where values don't match

	for ( i = 0; i < 4; i++ )
		for ( j = 0; j < 4; j++ )
			for ( k = 0; k < 4; k++ )
				{
				if ( given.board[i][j][k] != next.board[i][j][k] )
					{
					m.x = i;
					m.y = j;
					m.z = k;
					}
				}

//end my code here

	//output move
	
	print_move_to_screen( m );

	//write board state to file and exit
	return write_to_file(outputfilename, next.board);
}


int read_from_file( char* inputfilename, int board[][4][4] )
{
	FILE *ifile = fopen( inputfilename, "r" );
	if( !ifile )
	{
		printf( "could not open input file [%s] for reading\n", inputfilename );
		return -2;
	}

	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			for( int k = 0; k < 4; k++ )
			{
				char c = '.';
				fscanf(ifile, " %c", &c );
				switch( c )
				{
					case '.': board[i][j][k] = 0; break;
					case 'x': board[i][j][k] = -1; break;
					case 'o': board[i][j][k] = 1; break;
					default: board[i][j][k] = 0; break;
				}

			}
		}
	}

	fclose( ifile );
	return 0;
}

int write_to_file( char* outputfilename, int board[4][4][4] )
{
	FILE *ofile = fopen( outputfilename, "w" );
	if( !ofile )
	{
		printf( "could not open output file [%s] for writing\n", outputfilename );
		return -2;
	}

	// iterate through all squares on the board
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			for( int k = 0; k < 4; k++ )
			{
				// write the appropriate character to the file
				switch( board[i][j][k])
				{
					case 0: fprintf( ofile, "%c", '.'); break;
					case 1: fprintf( ofile, "%c", 'o'); break;
					case -1: fprintf( ofile, "%c", 'x'); break;
					default: fprintf( ofile, "%c", '.'); break;
				}
			}
			fprintf( ofile, "\n");
		}
		fprintf( ofile, "\n");
	}

	// close the output file
	fclose (ofile);
	return 0;
}

void print_move_to_screen( Move m)
{
	printf( "%d %d %d\n", m.x, m.y, m.z);
}

