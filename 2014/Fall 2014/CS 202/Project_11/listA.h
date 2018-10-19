#ifndef __LISTN_H_
#define __LISTN_H_
#include <iostream>

using namespace std;

class ListA{
        public:
                ListA(int = 10);
                ListA(const ListA&);
                ~ListA();
		bool gotoBeginning();
		bool gotoEnd();
		bool gotoNext();
                bool gotoPrior();
		bool insertAfter(int);
		bool insertBefore(int);
                bool remove(int&);
		bool replace(int);
		bool getCursor(int&) const;
                bool empty() const;
                bool full() const;
                bool clear();
		ListA& operator=(const ListA&);
                friend ostream& operator<<(ostream&, const ListA&);
                bool operator==(const ListA&) const;
        private:
                int size;
		int actual;
                int cursor;
                int *data;
};

#endif
