//class declarations

	//card class

	class card{
	
		public:
		card();
		~card();
		void setRank(char*);
		void setSuit(char*);
		void setLocation(char*);
		void setCardValue(int);
		char* getRank();
		char* getSuit();
		char* getLocation();
		int getCardValue();
		void print();
		void copy(card*);

		private:
		char* rank;
		char* suit;
		char* location;
		int cardValue;

		};

	//player class

	class player{
	
		public:
		player( int = 0 );
		~player();
		void setName(char*);
		void setTotal(int);
		void resetTotal();
		void setHand(card*);
		char* getName();
		int getTotal();
		card* getHand();
		void print();

		private:
		char* name;
		int total;
		card* hand;

		};
