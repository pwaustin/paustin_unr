#include <iostream>
using namespace std;

//class declarations

	//card class

	class card{
	
		public:
		card( const char* = "rank", const char* = "location" );
		card( const char*, const char*, const char*, const int );
		card( const card& );
		~card();
		card operator= ( const card& );
		bool operator< ( const card& ) const;
		void setLocation( const char* );
		const int getCardValue() const;
		friend bool operator<= ( const card&, const card& );
		friend ostream &operator<< ( ostream&, const card& );
		friend istream &operator>> ( istream&, card& );

		private:
		char* rank;
		char* suit;
		char* location;
		int cardValue;

		};

	//player class

	class player{
	
		public:
		player();
		~player();
		void setTotal( const int );
		const char* getName() const;
		const int getTotal() const;
		card* getHand() const;
		friend ostream &operator<< ( ostream&, const player& );
		friend istream &operator>> ( istream&, player& );

		private:
		char* name;
		int total;
		card* hand;

		};
