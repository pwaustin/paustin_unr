#include <exception>
#include <iostream>
using namespace std;

void a();

int main()
{

try
{
a();
}
catch(const char* message)
{
cerr << message << endl;
}

return 0;
}

void a()
{

throw "hey, idiot";
cout << "a" << endl;

}

