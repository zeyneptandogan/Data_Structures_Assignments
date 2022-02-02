//Zeynep Tandogan 25200
#ifndef _SORTALGORTIHMS_CPP
#define _SORTALGORTIHMS_CPP
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
using namespace std;
//i prefer to use templated class.
template <class Value>
class Sortalgorithms
{
public:

	Sortalgorithms(vector<Value>&myvec):vec(myvec){
	}
	//this is the insertion algorithm that makes comparison between the elements in the vector orderly.
	void insertionSort (){
		int j;
		for (int p = 1; p < vec.size(); p++){
			Value tmp = vec[p];
			j=p;
			for (j = p; j > 0 && (*tmp)< (*vec[j - 1]); j--)
				vec[j]= vec[j-1];
			vec[j] = tmp;
		}
	}
	//it rearrange vector according to heap properties-structure property and heap-order property
	void percDown(int i, int n ){
		int child;
		Value tmp;
		for (tmp=vec[i] ; leftChild(i) < n; i = child ){
			child = leftChild(i);
			if ( child != n-1 && (*vec[ child ]) < (*vec[ child+1 ]) )
				child++;
			if ( (*vec[child ]) > (*tmp) )
				vec[i] = vec[ child ];
			else
				break;
		}
		vec[ i ] = tmp;
	}
	//forming heap sort accordþng to rules of heap sort performed by percDown
	void heapsort()	{
		// buildHeap
		for (int i = vec.size()/2; i >=0; i--)
			percDown(i, vec.size());
		// sort
		for (int j = vec.size()-1; j >0; j--){
			swapfunc(vec[0], vec[j]); // swap max to the last pos.
			percDown(0, j); // re-form the heap
		}
	}
	void mergeSort( ){
		vector<Value> tmpArray( vec.size( ) );
		mergeSort( tmpArray, 0, vec.size( ) - 1 );
	}

	//this is the sorting part by dividing the vector into two repeatedly.
	void mergeSort(vector<Value> & tmpArray, int left, int right ){
		if ( left < right ){
			int center = ( left + right ) / 2;
			mergeSort(tmpArray, left, center );
			mergeSort(tmpArray, center + 1, right );
			merge(tmpArray, left, center + 1, right );
		}
	}
	//merge operation is done here by comparing the elements in the vectors.
	void merge(vector<Value> & tmpArray,int leftPos, int rightPos, int rightEnd ){
		int leftEnd = rightPos - 1;
		int tmpPos = leftPos;
		int numElements = rightEnd - leftPos + 1;
		while ( leftPos <= leftEnd && rightPos <= rightEnd )
			if ( (*vec[ leftPos ]) <= (*vec[ rightPos ]) )
				tmpArray[ tmpPos++ ] = vec[ leftPos++ ];
			else
				tmpArray[ tmpPos++ ] = vec[ rightPos++ ];
		while ( leftPos <= leftEnd ) // Copy rest of first half
			tmpArray[ tmpPos++ ] = vec[ leftPos++ ];
		while ( rightPos <= rightEnd ) // Copy rest of right half
			tmpArray[ tmpPos++ ] = vec[ rightPos++ ];
		// Copy tmpArray back
		for ( int i = 0; i < numElements; i++, rightEnd-- )
			vec[ rightEnd ] = tmpArray[ rightEnd ];
	}
	void medianquicksort(){
		medianquicksort( 0, vec.size( ) - 1 );
	}
	const Value & median3(int left, int right ){
		int center = ( left + right ) / 2;
		if ( (*vec[ center ]) < (*vec[ left ]) )
			swapfunc( vec[ left ],vec[ center ] );
		if ((*vec[ right ]) < (*vec[ left ]) )
			swapfunc( vec[ left ], vec[ right ] );
		if ( (*vec[ right ]) < (*vec[ center ]) )
			swapfunc( vec[ center ], vec[ right ] );
		// Place pivot at position right - 1
		swapfunc( vec[ center ], vec[ right - 1 ] );
		return vec[ right - 1 ];
	}
	void insertionSort(int left, int right ){//this is for the insertion sort in the quick sorts
		for ( int p = left + 1; p <= right; p++ ){
			Value tmp = vec[ p ];
			int j;
			for ( j = p; j > left && (*tmp) < (*vec[ j - 1 ]); j-- )
				vec[ j ] = vec[ j - 1 ];
			vec[ j ] = tmp;
		}
	}
	void medianquicksort(int left, int right ){
		if ( left + 10 <= right ){
			Value pivot = median3( left, right );
			int i = left, j = right - 1;
			for ( ; ; ){
				while ( (*vec[ ++i ]) < (*pivot) ) { }
				while ( (*pivot) < (*vec[ --j ]) ) { }
				if ( i < j )
					swap( vec[ i ], vec[ j ] );
				else
					break;
			}
			swapfunc( vec[ i ], vec[ right - 1 ] ); // Restore pivot
			medianquicksort( left, i - 1 ); // Sort small elements
			medianquicksort( i + 1, right ); // Sort large elements
		}
		else // Do an insertion sort on the subarray
			insertionSort( left, right );
	}
	//for first and random quick sort, i applied different way in comparison to median quick sort
	//since they can have a value that make vector out of subscript, i changed them to this version.
	//i form a seperate partition part and in the second partition function i swap their places
	void firstquicksort(){
		firstquickSort( 0, vec.size( ) - 1 );//
	}
	int partition_first( int low, int high) 
	{ 
		// Swap A[random] with A[high] 
		swapfunc(vec[low], vec[high]); 

		return partition(low, high); 
	} 
	void firstquickSort(int low, int high) 
	{ 
		if (low +10<= high) { 

			/* pi is partitioning index, arr[p] is now 
			at right place */
			int pi = partition_first(low, high); 

			// Separately sort elements before 
			// partition and after partition 
			firstquickSort(low, pi - 1); 
			firstquickSort( pi + 1, high); 
		} 
		else
			insertionSort(low,high);
	} 
	void randomquicksort(){
		randomquickSort( 0, vec.size( ) - 1 );
	}
	int partition( int low, int high) 
	{ 
		Value pivot = vec[high]; // pivot 
		int i = (low - 1); // Index of smaller element 

		for (int j = low; j <= high - 1; j++) { 

			// If current element is smaller than or 
			// equal to pivot 
			if ((*vec[j]) <= (*pivot)) { 

				i++; // increment index of smaller element 
				swapfunc(vec[i], vec[j]); 
			} 
		} 
		swapfunc(vec[i + 1], vec[high]); 
		return (i + 1); 
	} 
	int partition_r( int low, int high) 
	{ 
		// Generate a random number in between 
		// low .. high  i used rand() and srand() for randomness
		srand(time(NULL)); 
		int random = low + rand() % (high - low); 

		// Swap A[random] with A[high] 
		swapfunc(vec[random], vec[high]); 

		return partition(low, high); 
	} 
	void randomquickSort(int low, int high) 
	{ 
		if (low +10<= high) { 

			/* pi is partitioning index, arr[p] is now 
			at right place */
			int pi = partition_r(low, high); 

			// Separately sort elements before 
			// partition and after partition 
			randomquickSort(low, pi - 1); 
			randomquickSort( pi + 1, high); 
		} 
		else
			insertionSort(low,high);
	} 
	void swapfunc(int i,int j){
		Value tmp = vec[i];
		vec[i]= vec[j];
		vec[j] = tmp;
	}
private:

	vector<Value>&vec;
	inline int leftChild( int i ){
		return 2*i+1;
	}

	void swapfunc(Value& i,Value& j){
		Value tmp = i;
		i= j;
		j = tmp;
	}

};
#endif