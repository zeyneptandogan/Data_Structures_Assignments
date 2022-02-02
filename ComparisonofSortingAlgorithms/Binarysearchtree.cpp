//Zeynep Tandogan
#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H
#include "BinarySearchTree.h"
#include <iostream>

template <class Key, class Value>
 BinarySearchTree<Key,Value>::BinarySearchTree(const Value & notFound )//constructor
	 :ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

template <class Key, class Value>
const Value & BinarySearchTree<Key,Value>::elementAt( BinaryNode<Key,Value> *t ) const {//what the elements info(value) 
	if(t==NULL)
		return ITEM_NOT_FOUND;
    return t->info;
}

template <class Key, class Value>
const Value & BinarySearchTree<Key,Value>::find( const Key & x ) const{//public find 
	 return elementAt(find(x,root));  
}

template <class Key, class Value>
BinaryNode<Key,Value> *BinarySearchTree<Key,Value>::find( const Key & x, BinaryNode<Key,Value> *t  ) const {//private find 
	if ( t == NULL )
		return NULL;
	else if( x < t->element )
		return find( x, t->left );
	else if( t->element < x )
		return find( x, t->right );
    else
		return t;   // Match
}

template <class Key, class Value>
const Key & BinarySearchTree<Key,Value>::findMin( ) const{//public findMin
	return elementAt( findMin( root ) );
}

template <class Key, class Value>
BinaryNode<Key,Value> *BinarySearchTree<Key,Value>::findMin( BinaryNode<Key,Value> *t ) const{//private findMin
    if( t == NULL )
       return NULL;
    if( t->left == NULL )
       return t;
	return findMin( t->left );
}

template <class Key, class Value>
const Key & BinarySearchTree<Key,Value>::findMax( ) const{//public findMax
	return elementAt( findMax( root ) );
}
template <class Key, class Value>
BinaryNode<Key,Value> *BinarySearchTree<Key,Value>::findMax( BinaryNode<Key,Value> *t ) const{//private findMax
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::makeEmpty( ){//public
	 makeEmpty( root );
 }

template <class Key, class Value>
 void BinarySearchTree<Key,Value>::makeEmpty( BinaryNode<Key,Value> * &  t ) {//private
	 if( t != NULL ){
		 makeEmpty( t->left );
		 makeEmpty( t->right );
		 delete t;
	 }
	 t = NULL;
}
template <class Key, class Value>
void BinarySearchTree<Key,Value>::printTree( ) const{//public
	if( isEmpty( ) )
		cout << "Empty tree" << endl;
	else
		printTree( root );
}

template <class Key, class Value>
BinarySearchTree<Key,Value>::~BinarySearchTree( ){
	makeEmpty( );
}

template <class Key, class Value>
BinarySearchTree<Key,Value>::BinarySearchTree( const BinarySearchTree<Key,Value> & rhs  )
             : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){ 
				  *this = rhs;
}
template <class Key, class Value>
const BinarySearchTree<Key,Value> & BinarySearchTree<Key,Value>::operator = (const BinarySearchTree<Key,Value> & rhs ){
     if( this != &rhs )
	 {
		 makeEmpty( );
		 root = clone( rhs.root );
     }
     return *this;
}


template <class Key, class Value>
BinaryNode<Key,Value> *BinarySearchTree<Key,Value>::clone( BinaryNode<Key,Value> *t )const{//clone function
	if(t==NULL)
		return t;
	BinaryNode<Key,Value> *temp=new BinaryNode<Key,Value>(t->element,t->info,t->left,t->right);
	return temp;
}


template <class Key, class Value>
 void BinarySearchTree<Key,Value>::insert( const Key & x,const Value & y, BinaryNode<Key,Value> * & t) const{//private insert
	 if( t == NULL ) //  create a new node at the right place
		 t = new BinaryNode<Key,Value>( x,y, NULL, NULL );//put y for value info
	 else if( x < t->element )
		 insert( x,y, t->left );  // insert at the left or 
	 else if( t->element < x )
		 insert( x,y,t->right );  // right subtree
	 else
		 ;  // Duplicate; do nothing    
 }

template <class Key, class Value>
void BinarySearchTree<Key,Value>:: insert( const Key & x ,const Value & y){
	insert(x,y,root);
}


template <class Key, class Value>
void BinarySearchTree<Key,Value>::remove(const Key & x, BinaryNode<Key,Value> * & t ) const{//private delete
	if( t == NULL )
		return;   // Item not found; do nothing
	if( x < t->element )
		remove( x, t->left );
	else if( t->element < x )
		remove( x, t->right );
	else if( t->left != NULL && t->right != NULL ) {// Two children
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else{ // one or no children
		BinaryNode<Key,Value> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
}    
template <class Key, class Value>
void BinarySearchTree<Key,Value>:: remove( const Key & x ){//public remove
	BinaryNode<Key,Value> *t=find(x);
	remove(x,t);
}
template <class Key, class Value>
bool BinarySearchTree<Key,Value>::isEmpty( ) const{
	return root==NULL;
}

#endif	