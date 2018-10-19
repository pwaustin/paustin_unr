#include <iostream>

using namespace std;

class Stack;

class Node{
	private:
		Node(char,Node*);
		char data;
		Node* next;
		friend class List;
                friend ostream& operator<<(ostream&, const List&);
};


class Stack {
        public:
                Stack(int = 10);
                Stack(const Stack&);
                ~Stack();
                Stack& operator=(const Stack&);
                bool push(char);
                bool pop(char&);
                bool empty() const;
                bool full() const;
                bool clear();
		bool operator==(const Stack&) const;
                friend ostream& operator<<(ostream&, const Stack&);
        private:
                int max;
                int top;
                int actual; //only used in stack (stay) implementation
                char* data;
};

