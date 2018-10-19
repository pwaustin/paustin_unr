#include <iostream>

using namespace std;

class Queue;

class Node{
	private:
		Node(char,Node*);
		char data;
		Node* next;
		friend class List;
                friend ostream& operator<<(ostream&, const List&);
};


class Queue{
        public:
                Queue(int = 10);
                Queue(const Queue&);
                ~Queue();
                Queue& operator=(const Queue&);
                bool enqueue(char);
                bool dequeue(char&);
                bool empty() const;
                bool full() const;
                bool clear();
                bool operator==(const Queue&) const;
                friend ostream& operator<<(ostream&, const Queue&);
        private:
                node* front;
		node* rear;
};

