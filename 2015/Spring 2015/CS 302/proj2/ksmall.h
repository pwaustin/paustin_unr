/** CS 302 Project 2 - header for ksmall sort class
@file ksmall.h
@author Patrick Austin
@date 2/9/2015 */

class ksmall
	{

	private:

	int* data;
	int size;

	public:

	ksmall(const int);
	~ksmall();
	int search(const int, const int, const int);
	void display() const;
	
	};
