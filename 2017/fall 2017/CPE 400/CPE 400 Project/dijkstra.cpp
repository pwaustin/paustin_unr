#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

double NODE_POWER = 1000;
int BROADCASTER_POWER = 99999;
int BROADCAST_RADIUS = 5;
int BROADCASTERS = 10;

struct node{
double xLoc;
double yLoc;
double power;
double distToGateway;
int packetsHeld;
vector<int> neighborNodes; };

int main()
	{

	//initialize variables;

	vector<node> nodes;
	ifstream fin;
	int graphSize;
	int dummy;

	//read in graph data from input file

	fin.open("in.txt");

	fin >> graphSize;

	nodes.resize(graphSize);

	for ( int i = 0; i < graphSize; i++ )
		{
		fin >> dummy;
		fin >> nodes[i].xLoc;
		fin >> nodes[i].yLoc;
		
		}

	fin.close();

	//initialize nodes

	for ( int i = 0; i < graphSize; i++ )
		{

		//get each node's distance to the hub

		nodes[i].distToGateway = sqrt( 
			( (nodes[i].xLoc - nodes[0].xLoc) * (nodes[i].xLoc - nodes[0].xLoc) )
			+ ( (nodes[i].yLoc - nodes[0].yLoc) * (nodes[i].yLoc - nodes[0].yLoc) ) );

		//initialize power, packets held. nodes start with full power and 0 packets

		nodes[i].power = NODE_POWER;

		nodes[i].packetsHeld = 0;

		}

	sort(nodes.begin(), nodes.end(), [](const node&a, const node&b)
		{
		return (a.distToGateway > b.distToGateway); 
		});

	for ( int i = 0; i < graphSize; i++ )
		{
		//generate list of neighbors for each node- these are the nodes within this node's broadcast radius

		for ( int j = BROADCASTERS ; j < graphSize; j++ )
			{
	
			if ( i != j )
				{
				if ( sqrt( ( (nodes[i].xLoc - nodes[j].xLoc) * (nodes[i].xLoc - nodes[j].xLoc) )
				+ ( (nodes[i].yLoc - nodes[j].yLoc) * (nodes[i].yLoc - nodes[j].yLoc) ) ) <= BROADCAST_RADIUS )
					{

					nodes[i].neighborNodes.push_back(j);
						
					}

				}
			}
		}

	for ( int i = 0; i < BROADCASTERS; i++ )
		{

		nodes[i].power = BROADCASTER_POWER;

		}

	//initialize sim

	int t = 0;

	bool outOfPower = false;

	//continue sim until a node runs out of power

	while ( !outOfPower )
		{

		//1-3 packets arrive at the 5 farthest nodes from the gateway

		for ( int i = 0; i < BROADCASTERS; i++ )
			{

			nodes[i].packetsHeld += (t % 3) + 1;

			}

		//each node except the gateway needs to find a neighbor to send each of its packets to
	
		for ( int i = 0; i < graphSize; i++ )
			{
	
			if ( nodes[i].distToGateway != 0 )
				{

				//for each packet a node is holding...

				int packetsToSend = nodes[i].packetsHeld;

				for ( int j = 0; j < packetsToSend; j++ )
					{

					//find a destination for the packet - start by trying the first neighbor

					int dest = nodes[i].neighborNodes[0];

					//consider each neighbor

					for ( int k = 1; k < nodes[i].neighborNodes.size(); k++ )
						{

						int thisNeighbor = nodes[i].neighborNodes[k];

						//if this neighbor has a lower value for distance to gateway / % power remaining than the current choice, switch to this neighbor

						if ( nodes[thisNeighbor].distToGateway < nodes[dest].distToGateway  )
							{
							dest = thisNeighbor;
							}

						}

					//send the packet- this node loses a packet, the dest gains one, and this node loses a unit of power

					nodes[i].packetsHeld --;
					nodes[dest].packetsHeld ++;
					nodes[i].power--;

	//cout << "packet from x=" << nodes[i].xLoc << " y=" << nodes[i].yLoc << " to x=" << nodes[dest].xLoc << " y=" << nodes[dest].yLoc << endl;
					//if losing power from transmission has caused this node to run out of power, stop sending packets

					if ( nodes[i].power == 0 )
						break;

					}

				}

			}

		//if any nodes have died, flip the out of power bool to leave the sim

		for ( int i = 0; i < graphSize; i++ )
			{

			if ( nodes[i].power == 0 )
				{

				if ( outOfPower == false )
					{
					cout << "Node x=" << nodes[i].xLoc << "y= " << nodes[i].yLoc << " has run out of power, ending simulation..." << endl;
					}

				outOfPower = true;

				}
			}

		//increment time before looping again or stopping

		t++;

		}

	//output stats

	cout << "Simulation complete." << endl;
	cout << "Time to exhaust power: " << t << " time units" << endl;
	cout << "Throughput: " << nodes[graphSize-1].packetsHeld << " packets delivered over " << t << " time units = " << nodes[graphSize-1].packetsHeld / t << " packets per time unit" << endl;

	double packetsLost = 0;
	
	for ( int i = 0; i < graphSize - 1 ; i++ )
		packetsLost += nodes[i].packetsHeld;

	double packetLossRatio = packetsLost/ double( nodes[graphSize - 1].packetsHeld + packetsLost );

	cout << "Packets lost: " << packetsLost <<  " / " << nodes[graphSize-1].packetsHeld + packetsLost << " or approximately " << setprecision(4) << packetLossRatio << endl;

	int powerRemaining = 0;

	for ( int i = BROADCASTERS; i < graphSize - 1; i++ )
		{

		powerRemaining += nodes[i].power;

		}

		double avgPowerRemaining = double(double(powerRemaining) /( (graphSize - BROADCASTERS - 1) * NODE_POWER ) );

	cout << "Percent of power remaining: " << powerRemaining << " / " << (graphSize - BROADCASTERS - 1)*NODE_POWER << " = " << setprecision(4) << avgPowerRemaining << endl;
	
	return 0;

	}
