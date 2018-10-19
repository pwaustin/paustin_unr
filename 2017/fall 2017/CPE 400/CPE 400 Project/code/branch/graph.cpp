#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

#define PI 3.14159
#define R 5
#define NODES 100


int main()
{
   ofstream fout;
   fout.open("in.txt");
   
   fout << NODES << endl;
   fout << 0 << " " << 10 << " " << 10 << endl;
   double previousX = 10;
   double previousY = 10;
   
   
   
   
   double a, b, x, y, newX, newY;
   for (int i = 1; i < NODES; i++) {
       a = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
       b = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
       
       x = b * R * cos(2*PI*a/b);
       y = b * R * sin(2*PI*a/b);
       
       newX = previousX + x;
       newY = previousY + y;
       
       fout << i << " " << newX << " " << newY << endl;
       
       previousX = newX;
       previousY = newY;
   }
 
   

   return 0;
}
