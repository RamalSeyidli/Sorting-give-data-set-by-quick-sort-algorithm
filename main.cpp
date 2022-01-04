#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm> //in case sensitive comparision
#include <time.h> //clock and srand, rand 

using namespace std;


struct tweets{
		string tweet_id;
		string tweet_datetime;
		string tweet_unixtime;
		string artist_name;	
		string track_title;
		string country;	
	};
	
void swap(tweets* first, tweets* second){
	tweets temp = *first;
	*first = *second;
	*second = temp;
}

int partition (tweets arr[], int left, int right){ //asked by quickSort to place pivot			arr[bigger].artist_name.compare(arr[pivot].artist_name)	< 0			
//swaps to left smaller values and bigger to right 

	int pivot = right;  // pivot
    int smaller = left; //smaller element
 
    for (int bigger = left; bigger < right; bigger++)
    {
        // If current element is smaller than or equal to pivot
        if(arr[bigger].country.compare(arr[pivot].country) < 0 || (arr[bigger].country.compare(arr[pivot].country) == 0 && (arr[bigger].artist_name.compare(arr[pivot].artist_name)	< 0	) || (arr[bigger].country.compare(arr[pivot].country) == 0 && arr[bigger].artist_name.compare(arr[pivot].artist_name)) == 0 && arr[bigger].tweet_unixtime < arr[pivot].tweet_unixtime) || (arr[bigger].country.compare(arr[pivot].country) == 0 && arr[bigger].artist_name.compare(arr[pivot].artist_name)	== 0	 && arr[bigger].tweet_unixtime == arr[pivot].tweet_unixtime &&  arr[bigger].tweet_id < arr[pivot].tweet_id))
        {
            // increment index of smaller element
            swap(&arr[smaller], &arr[bigger]);
            smaller++; //move iterator to the right
        }
    }
    swap(&arr[smaller], &arr[pivot]);
    return smaller;
}

int partitionRandom(tweets arr[], int left, int right)
{
    srand(time(NULL));
    int random = left + rand() % (right - left);
    //determining a random value between rightmost and leftmost elements
 
    swap(arr[random], arr[right]);
    //instead of leftmost and rightmost iterators random and rightmost iterators will be swapped
 
    return partition(arr, left, right);
}

	
void quickSort(tweets arr[], int left, int right, string A)
{
	//arr is array will be sorted
	//left is starting index
	//right is ending index
	if (left < right){
		
		int pivot;
		
		if(A == "deterministic"){
    		pivot = partition(arr, left, right);
    		//pivot will be determined for sorting operation
    	}else if(A == "randomized"){
    		pivot = partitionRandom(arr, left, right);
    		//pivot will be determined for sorting operation randomly
		}

    	quickSort(arr, left, pivot - 1, A); 
    	//recursively repeats for left part of pivot
        quickSort(arr, pivot + 1, right, A);
        //recursively repeats for right part of pivot
    }
}	

void print(tweets arr[], int N, string tableHeader, string O) {

	ofstream outfile;

	outfile.open(O); // to open or create and open output file			

	if (!outfile) {
		cerr << "Output file cannot be opened";	//controo
	}

	outfile << tableHeader << endl; // to write header of the table

	for(int i = 0; i < N; i++) { // to write sorted tweets to the output file
		outfile << arr[i].tweet_id << '\t' << arr[i].tweet_datetime << '\t' << arr[i].tweet_unixtime << '\t' << arr[i].artist_name << '\t' << arr[i].track_title << '\t' << arr[i].country << '\n';
	}

	outfile.close(); // close "sorted.csv"
}


int main(int argc, char** argv){
	
	clock_t elapsedTime; //to count runing time
	elapsedTime = clock();
	
	
	// ./a.out N A I O
	
	int N;	//number of entries
	string A; //deterministic or randomized pivot selection
	string I; //input file path
	string O; //output file path
	
	
	if (argc > 1) {
		N = atoi(argv[1]); // ./a.out N A I O
		A = argv[2];
		I = argv[3];
		O = argv[4];
		
	} else {
		N = 1000; // default value for N
		A = "deterministic";
		I = "tweets_sorted_1000.csv";
		O = "tweets_sorted_1000.csv";
	}
	
	
	ifstream file;
	file.open(I);		
	
	if(!file.is_open()){
		cerr << "File cannot be opened" << endl;
	}
	
	string line;
	getline(file, line);
	string tableHeader = line; //to skip header
	
	tweets * arr = new tweets[N]; //to keep tweets and all of their information

	for(int i = 0; i<N; i++){
		
		getline(file, line, '\t'); //to read tweet_id 
		arr[i].tweet_id = line; 
		
		getline(file, line, '\t'); //to read tweet_datetime 
		arr[i].tweet_datetime = line;
		
		getline(file, line, '\t'); //to read tweet_unixtime 
		arr[i].tweet_unixtime = line;
		
		getline(file, line, '\t'); //to read artist_name 
		arr[i].artist_name = line;
		
		getline(file, line, '\t'); //to read track_title 
		arr[i].track_title = line;
		
	    getline(file, line, '\n'); //to read country
		arr[i].country = line;
		
	    
	}
	
	quickSort(arr, 0, N-1, A);	//askes quicksort 
		
	print(arr, N, tableHeader, O); // to write sorted tweets to the O file
		
	delete [] arr; // delete tweets
		
	elapsedTime = clock() - elapsedTime;	//calculates time
	
	cout << "Sorted in " << ( (float) elapsedTime ) * 1000 / CLOCKS_PER_SEC << " miliseconds by using " << A << " pivot selection." <<endl;
		
	return 0;
}
