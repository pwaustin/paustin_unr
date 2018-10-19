#include "stack.h"
#include <iostream>
using namespace std;

int main()
{

Stack test;
char temp;


test.push('a');

cout << test;
test.push('b');

cout << test;
test.push('c');

cout << test;

test.push('d');
test.push('e');
test.push('f');
test.push('g');
test.push('h');
test.push('i');

Stack test2(2);

test2 = test;

test.push('j');
test2.push('J');

cout << test;
cout << test2;

if ( test2 == test )
	{

	cout << "bad" << endl;

	}

else
	cout << "good" << endl;

test.pop(temp);

cout << test;

test.pop(temp);

cout << test;

test.pop(temp);

cout << "returning to empty state test:" << endl;

Stack test3;

test3.push('0');

test3.pop(temp);

Stack test4;

if ( test3 == test4 )
	{

	cout << "good" << endl;

	}


cout << test;








return 0;

}
