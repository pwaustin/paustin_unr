#include "queue.h"
#include <iostream>
using namespace std;

int main()
{

Queue test;
int temp;

cout << "testing printing an empty queue:" << endl;

cout << test;

cout << "testing copying an empty queue:" << endl;

Queue test2 = test;

cout << test2;

cout << "testing whether two empty queues return ==:" << endl;

if ( test == test2 )
	{

	cout << "Yes." << endl;

	}

cout << "testing fully enqueueing:" << endl;

test.enqueue(0);
cout << test;
test.enqueue(1);
cout << test;
test.enqueue(2);
cout << test;
test.enqueue(3);
cout << test;
test.enqueue(4);
cout << test;
test.enqueue(5);
cout << test;
test.enqueue(6);
cout << test;
test.enqueue(7);
cout << test;
test.enqueue(8);
cout << test;
test.enqueue(9);
cout << test;

cout << "testing enqueuing over size:" << endl;

test.enqueue(0);
cout << test;

cout << "testing copying a full array. Here's the copy:" << endl;

test2 = test;

Queue test3 = test2;

cout << test3;
cout << test2;
cout << "is the == operator working correctly in this situation?" << endl;

if ( test2 == test )
{
cout << "Yes." << endl;
}

cout << "testing fully dequeueing:" << endl;

test.dequeue(temp);
cout << test;

test.dequeue(temp);
cout << test;

test.enqueue(0);
cout << test;

test.enqueue(1);
cout << test;

test.enqueue(2);
cout << test;



return 0;

}
