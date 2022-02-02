//Zeynep Tandogan 25200
#ifndef _HASHTABLE_CPP
#define _HASHTABLE_CPP
#include <vector>
#include <string>
#include <iostream>
#include "math.h"
using namespace std;

template <class Key,class Value>
class HashTable{
public:
	explicit HashTable( const Value & notFound ,int size = 53 );

	HashTable( const HashTable & rhs )//constructor
		: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),array( rhs.array ), currentSize( rhs.currentSize ) { }

	const Value & find( const Key & x ) const;
	
	void insert(int count, const Key & x ,const Value & y );
	void remove( const Key & x );
	void makeEmpty( );
	const HashTable & operator=( const HashTable & rhs );
	enum EntryType { ACTIVE, EMPTY, DELETED };
	double calculateload();
	int hashfunc(const Key & word,int currentSize)const; 
private:
	struct HashEntry{
		Key element;
		Value details;
		EntryType info;

		HashEntry( const Key & e = Key( ),Value t=NULL, EntryType i = EMPTY )
			: element( e ), details(t),info( i ) { }
	};

	vector<HashEntry> array;
	int currentSize;
	const Value ITEM_NOT_FOUND;
	bool isActive( int currentPos ) const;
	int findPos( const Key & x ) const;
	void rehash(int count );
};

int nextPrime( int n );
bool isPrime( int n );
//this part in the comment because this program is worked without an error in two different,seperate ways.
//first, use HashTable.cpp and exclude it from the build
//secondly, implement functions in just header, but i don't prefer that one,for this reason they are all in comment.

//bool isPrime( int n ){
//	if ( n == 2 || n == 3 )
//		return true;
//	if ( n == 1 || n % 2 == 0 )
//		return false;
//	for ( int i = 3; i * i <= n; i += 2 )
//		if ( n % i == 0 )
//			return false;
//	return true;
//}
//
//int nextPrime( int n ){
//	if ( n % 2 == 0 )
//		n++;
//	for ( ; ! isPrime( n ); n += 2 )
//		;
//	return n;
//}
//
//
//template <class Key, class Value>
//HashTable<Key,Value>::HashTable( const Value & notFound, 
//								int size )
//								: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
//{
//	makeEmpty( );
//}
//
//template <class Key, class Value>
//int HashTable<Key,Value>::findPos( const Key & x ) const
//{
//	int collisionNum = 0;
//	int currentPos = hashfunc( x, array.size( ) );
//
//	while ( array[ currentPos ].info != EMPTY && 
//		array[ currentPos ].element != x )
//	{
//		currentPos += 2 * ++collisionNum - 1;  // add the difference
//		if ( currentPos >= array.size( ) )             // perform the mod
//			currentPos =currentPos - array.size( );               // if necessary
//	}
//	return currentPos;
//}
//
//template <class Key, class Value>
//bool HashTable<Key,Value>::isActive( int currentPos ) const
//{
//	return array[ currentPos ].info == ACTIVE;
//}
//template <class Key, class Value>
//void HashTable<Key,Value>::remove( const Key & x )
//{
//	int currentPos = findPos( x );
//	if ( isActive( currentPos ) )
//		array[ currentPos ].info = DELETED;
//}
//template <class Key, class Value>
//const Value & HashTable<Key,Value>::find( const Key & x ) const
//{
//	int currentPos = findPos( x );
//	if (isActive( currentPos )) 
//		return array[ currentPos ].details; 
//
//	return   ITEM_NOT_FOUND;
//}
//template <class Key, class Value>
//void HashTable<Key,Value>::insert( int count,const Key & x ,const Value & y )
//{
//	// Insert x as active
//	if(count==1)
//		currentSize=0;
//	int currentPos = findPos( x );
//	if ( isActive( currentPos ) )
//		return;
//	array[ currentPos ] = HashEntry( x,y, ACTIVE );
//	// enlarge the hash table if necessary 
//	if ( ++currentSize >= 9*array.size( ) / 10 )
//		rehash(count );
//}
//template <class Key, class Value>
//double HashTable<Key,Value>:: calculateload(){
//	return (double)currentSize/(double)array.size();
//}
//template <class Key, class Value>
//void HashTable<Key,Value>::rehash(int count )
//{
//	vector<HashEntry> oldArray = array;
//	cout<<"rehashed..."<<endl;
//	// Create new double-sized, empty table
//	array.resize( nextPrime( 2 * oldArray.size( ) ) );
//	double loadfactor=(double)currentSize/(double)array.size();
//	cout<<"previous table size: "<<oldArray.size()<<", new table size: "<<array.size()<<", current unique word count "<<currentSize<<", current load factor:"<<(double)currentSize/(double)array.size()<<endl;
//
//	for ( int j = 0; j < array.size( ); j++ )
//		array[ j ].info = EMPTY;
//
//	// Copy table over
//	currentSize = 0;
//	for ( int i = 0; i < oldArray.size( ); i++ )
//		if ( oldArray[ i ].info == ACTIVE )
//			insert( count,oldArray[ i ].element,oldArray[ i ].details );
//}
//template <class Key, class Value>
//void HashTable<Key,Value>::makeEmpty( ){
//	for(int i=0;i<array.size(); i++){
//		array[ i ].info == EMPTY;
//	}
//}
//template <class Key, class Value>
//const HashTable<Key,Value> & HashTable<Key,Value>::operator = (const HashTable<Key,Value> & rhs ){
//	if(this!=&rhs){
//		makeEmpty();
//		array.size()=rhs.size();
//		for (int i=0;i<rhs.size();i++){
//			array[i].info=rhs[i].info;
//			array[i].element=rhs[i].element;
//			array[i].details=rhs[i].details;
//		}
//	}
//	return *this;
//}
//
//template <class Key, class Value>
//int HashTable<Key,Value>:: hashfunc(const Key& word,int currentSize)const
//{ 
//    int hashVal = 0;
//  
//    for (int i = 0; i < word.length();i++) 
//	  hashVal = 37 * hashVal + word[ i ];
//
//    hashVal = hashVal % currentSize;
//
//    if (hashVal < 0) 
//	  hashVal = hashVal + currentSize;
//
//   return(hashVal);
//}
#include "HashTable.cpp"
#endif