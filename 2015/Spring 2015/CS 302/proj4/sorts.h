/**
@file sorts.h
@author Patrick Austin
@date 3/9/2015
*/

const int MAX_VALUES = 1000000;
const int MAX_SIZE = 500000;

class bubbleSort
	{

	private:

	int arr[MAX_VALUES];
	double time;
	long long comparisons;
	long long swaps;

	public:

	bubbleSort();
	void sort( const int& );
	void bubbleUp( const int&, const int&, bool& );
	void readin( const int& );
	double getTime() const;
	int getComparisons() const;
	int getSwaps() const;
	void resetCounts();

	};

class mergeSort
	{

	private:

	int arr[MAX_VALUES];
	double time;
	int comparisons;
	int swaps;

	public:

	mergeSort();
	void timeSort ( const int&, const int & );
	void sort( const int&, const int &);
	void merge( const int&, const int&, const int& );
	void readin( const int& );
	double getTime() const;
	int getComparisons() const;
	int getSwaps() const;
	void resetCounts();

	};

class countingSort
	{

	private:

	int arr[MAX_VALUES];
	double time;
	int comparisons;
	int swaps;

	public:

	countingSort();
	void sort( const int& );
	void readin( const int& );
	double getTime() const;
	int getComparisons() const;
	int getSwaps() const;
	void resetCounts();

	};
