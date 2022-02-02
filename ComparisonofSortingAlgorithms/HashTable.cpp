//Zeynep Tandogan 25200
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include "HashTable.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
//IMPORTANT NOTE: please change this cpp's property as "excluded from build" if not it wont work!
//free functions 
bool isPrime( int n ){//checking whether it is a prime number or not.
	if ( n == 2 || n == 3 )
		return true;
	if ( n == 1 || n % 2 == 0 )
		return false;
	for ( int i = 3; i * i <= n; i += 2 )
		if ( n % i == 0 )
			return false;
	return true;
}

int nextPrime( int n ){//finding the next prime
	if ( n % 2 == 0 )
		n++;
	for ( ; ! isPrime( n ); n += 2 )
		;
	return n;
}


template <class Key, class Value>
HashTable<Key,Value>::HashTable( const Value & notFound, 
								int size )
								: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
	makeEmpty( );
}

template <class Key, class Value>
int HashTable<Key,Value>::findPos( const Key & x ) const
{
	int collisionNum = 0;
	int currentPos = hashfunc( x, array.size( ) );

	while ( array[ currentPos ].info != EMPTY && 
		array[ currentPos ].element != x )
	{
		currentPos += 2 * ++collisionNum - 1;  // add the difference, perform the mod
		if ( currentPos >= array.size( ) )             
			currentPos =currentPos - array.size( );               
	}
	return currentPos;
}

template <class Key, class Value>
bool HashTable<Key,Value>::isActive( int currentPos ) const
{
	return array[ currentPos ].info == ACTIVE;
}
template <class Key, class Value>
void HashTable<Key,Value>::remove( const Key & x )
{
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		array[ currentPos ].info = DELETED;
}
template <class Key, class Value>
const Value & HashTable<Key,Value>::find( const Key & x ) const
{
	int currentPos = findPos( x );
	if (isActive( currentPos )) 
		return array[ currentPos ].details; 

	return   ITEM_NOT_FOUND;
}
template <class Key, class Value>
void HashTable<Key,Value>::insert( int count,const Key & x ,const Value & y )
{
	// Insert x as active
	if(count==1)
		currentSize=0;
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		return;
	array[ currentPos ] = HashEntry( x,y, ACTIVE );
	// enlarge the hash table if necessary 
	if ( ++currentSize >= array.size( ) / 2 )//50% 
		rehash(count );
}
template <class Key, class Value>
double HashTable<Key,Value>:: calculateload(){
	return (double)currentSize/(double)array.size();//double division
}
template <class Key, class Value>
void HashTable<Key,Value>::rehash(int count )
{
	vector<HashEntry> oldArray = array;
	//cout<<"rehashed..."<<endl;
	// Create new double-sized, empty table
	array.resize( nextPrime( 2 * oldArray.size( ) ) );
	double loadfactor=(double)currentSize/(double)array.size();
	//cout<<"previous table size: "<<oldArray.size()<<", new table size: "<<array.size()<<", current unique word count "<<currentSize<<", current load factor:"<<(double)currentSize/(double)array.size()<<endl;

	for ( int j = 0; j < array.size( ); j++ )
		array[ j ].info = EMPTY;

	// Copy table over
	currentSize = 0;
	for ( int i = 0; i < oldArray.size( ); i++ )
		if ( oldArray[ i ].info == ACTIVE )
			insert( count,oldArray[ i ].element,oldArray[ i ].details );
}
template <class Key, class Value>
void HashTable<Key,Value>::makeEmpty( ){
	for(int i=0;i<array.size(); i++){
		array[ i ].info == EMPTY;//make all of them titled as EMPTY
	}
}
template <class Key, class Value>
const HashTable<Key,Value> & HashTable<Key,Value>::operator = (const HashTable<Key,Value> & rhs ){
	if(this!=&rhs){
		makeEmpty();
		array.size()=rhs.size();
		for (int i=0;i<rhs.size();i++){//take everything to the array
			array[i].info=rhs[i].info;
			array[i].element=rhs[i].element;
			array[i].details=rhs[i].details;
		}
	}
	return *this;
}

template <class Key, class Value>
int HashTable<Key,Value>:: hashfunc(const Key& word,int currentSize)const
{ 
    int hashVal = 0;
  
    for (int i = 0; i < word.length();i++) 
	  hashVal = 37 * hashVal + word[ i ];

    hashVal = hashVal % currentSize;

    if (hashVal < 0) //in the case for a negative result
	  hashVal = hashVal + currentSize;

   return(hashVal);
}
#endif