#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <utility>

using namespace std;

#define PI 3.14159
#define R 5
#define NODES 100


int main()
{
   srand(time(NULL));
   
   ofstream fout;
   fout.open("in.txt");
   
   fout << NODES << endl;
   fout << 0 << " " << 10 << " " << 10 << endl;
   double previousX = 10;
   double previousY = 10;
   
   pair<double, double> array[NODES];
   get<0>(array[0]) = 10;
   get<1>(array[0]) = 10;
   
   double a, b, x, y, newX, newY;
   for (int i = 1; i < NODES; i++) {
       cout << "new node " << i << " around: ";
       cout << previousX << " " << previousY << endl;
       a = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
       b = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
       
       x = b * R * cos(2*PI*a/b);
       y = b * R * sin(2*PI*a/b);
       
       newX = previousX + x;
       newY = previousY + y;
       
       get<0>(array[i]) = newX;
       get<1>(array[i]) = newY;
       
       fout << i << " " << newX << " " << newY << endl;
       
       int random = rand() % (i+1);
       previousX = get<0>(array[random]);
       previousY = get<1>(array[random]);
   }
 
   

   return 0;
}
