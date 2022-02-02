//Zeynep Tandogan
#ifndef _AVLSEARCHTREE_H
#define _AVLSEARCHTREE_H
#include "AVLsearchtree.h"
//#include <iostream>

template <class Key, class Value>
 AVLSearchTree<Key,Value>::AVLSearchTree(const Value & notFound )//constructor
	 :ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

template <class Key, class Value>
const Value & AVLSearchTree<Key,Value>::elementAt( AvlNode<Key,Value> *t ) const {//what the elements info(value) 
	if(t==NULL)
		return ITEM_NOT_FOUND;
    return t->info;
}

template <class Key, class Value>
const Value & AVLSearchTree<Key,Value>::find( const Key & x ) const{//public find 
	 return elementAt(find(x,root));  
}

template <class Key, class Value>
AvlNode<Key,Value> *AVLSearchTree<Key,Value>::find( const Key & x, AvlNode<Key,Value> *t  ) const {//private find 
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
const Key & AVLSearchTree<Key,Value>::findMin( ) const{//public findMin
	return elementAt( findMin( root ) );
}

template <class Key, class Value>
AvlNode<Key,Value> *AVLSearchTree<Key,Value>::findMin( AvlNode<Key,Value> *t ) const{//private findMin
    if( t == NULL )
       return NULL;
    if( t->left == NULL )
       return t;
	return findMin( t->left );
}

template <class Key, class Value>
const Key & AVLSearchTree<Key,Value>::findMax( ) const{//public findMax
	return elementAt( findMax( root ) );
}
template <class Key, class Value>
AvlNode<Key,Value> *AVLSearchTree<Key,Value>::findMax( AvlNode<Key,Value> *t ) const{//private findMax
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::makeEmpty( ){//public
	 makeEmpty( root );
 }

template <class Key, class Value>
 void AVLSearchTree<Key,Value>::makeEmpty( AvlNode<Key,Value> * &  t ) {//private
	 if( t != NULL ){
		 makeEmpty( t->left );
		 makeEmpty( t->right );
		 delete t;
	 }
	 t = NULL;
}
template <class Key, class Value>
void AVLSearchTree<Key,Value>::printTree( ) const{
	if( isEmpty( ) )
		cout << "Empty tree" << endl;
	else
		printTree( root );
}

template <class Key, class Value>
AVLSearchTree<Key,Value>::~AVLSearchTree( ){
	makeEmpty( );
}

template <class Key, class Value>
AVLSearchTree<Key,Value>::AVLSearchTree( const AVLSearchTree<Key,Value> & rhs  )
             : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){ 
				  *this = rhs;
}
template <class Key, class Value>
const AVLSearchTree<Key,Value> & AVLSearchTree<Key,Value>::operator = (const AVLSearchTree<Key,Value> & rhs ){
     if( this != &rhs )
	 {
		 makeEmpty( );
		 root = clone( rhs.root );
     }
     return *this;
}


template <class Key, class Value>
AvlNode<Key,Value> *AVLSearchTree<Key,Value>::clone( AvlNode<Key,Value> *t )const{//clone function
	if(t==NULL)
		return t;
	AvlNode<Key,Value> *temp=new AvlNode<Key,Value>(t->element,t->info,t->left,t->right,t->height);
	return temp;
}

template <class Key, class Value>
int AVLSearchTree<Key,Value>::height( AvlNode<Key,Value> *t ) const{

      if (t == NULL)
		return -1;
	
      return t->height;
}
template <class Key, class Value>
int AVLSearchTree<Key,Value>::max( int lhs, int rhs ) const
{
      if (lhs > rhs)
	  return lhs;

      return rhs;            
}
template <class Key, class Value>
 void AVLSearchTree<Key,Value>::insert( const Key & x,const Value & y, AvlNode<Key,Value> * & t) const{//private insert
      if ( t == NULL )
           t = new AvlNode<Key,Value>( x,y, NULL, NULL );//put y for value info
      else if ( x < t->element ) {
           
           insert( x,y, t->left );
           // Check if the left tree is out of balance (left subtree grew in height!)
           if ( height( t->left ) - height( t->right ) == 2 )
                if ( x < t->left->element )  // X was inserted to the left-left subtree!
                     rotateWithLeftChild( t );
                else			     // X was inserted to the left-right subtree!
                     doubleWithLeftChild( t );
     }      
	 else if( t->element < x ){    
         insert( x,y, t->right );
         if ( height( t->right ) - height( t->left ) == 2 )
		// height of the right subtree increased
              if ( t->right->element < x )
		     // X was inserted to right-right subtree
                     rotateWithRightChild( t );
              else // X was inserted to right-left subtree
                     doubleWithRightChild( t );
     }
     else
                ;  
            
     t->height = max( height( t->left ), height( t->right ) ) + 1;
       
 }
template <class Key, class Value>
void AVLSearchTree<Key,Value>:: insert( const Key & x ,const Value & y/*,AvlNode<Key,Value> * &t*/){
	//AvlNode<Key,Value> *t=find(x);
	insert(x,y,root);
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::rotateWithLeftChild( AvlNode<Key,Value> * & k2 ) const{
	AvlNode<Key,Value> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}
template <class Key, class Value>
void AVLSearchTree<Key,Value>::rotateWithRightChild( AvlNode<Key,Value> * & k1 ) const{
	AvlNode<Key,Value> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}
template <class Key, class Value>
void AVLSearchTree<Key,Value>::doubleWithLeftChild( AvlNode<Key,Value> * & k3 ) const{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}
template <class Key, class Value>
void AVLSearchTree<Key,Value>::doubleWithRightChild( AvlNode<Key,Value> * & k1 ) const{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}

template <class Key, class Value>
void AVLSearchTree<Key,Value>::remove(const Key & x, AvlNode<Key,Value> * & t ) const{//private delete
	if (t==NULL) 
		return t;
	else if(t->element<x)
		remove(x,t->right);
	else if(t->element>x)
		remove(x,t->left);
//	two children case
	else if(t->right!=NULL &&t->left!=NULL){
		AvlNode<Key,Value> *p=findMin(t->right);
		t->element=p->element;
		remove(t->element,t->right);
	}
//one or no children
	else{
		AvlNode<Key,Value> * tobedeleted=t;
		if(t->right!=NULL)
			t=t->right;
		else if(t->left!=NULL)
			t=t->left;
		delete tobedeleted;
	}

	t->height=max(height(t->left),height(t->right))+1;//update the height

	if(height(t->left)-height(t->right)==2){//according to the pattern
		if (height(t->left->left)-height(t->left->right)==1){
			rotateWithLeftChild( t );
		}
		else{		
			doubleWithLeftChild( t );
		}
		
	}

	if(height(t->right)-height(t->left)==2){
		if(height(t->right->right)-height(t->right->left)==1){
			rotateWithRightChild( t )
		}
		else
			doubleWithRightChild( t );
	}
}
template <class Key, class Value>
void AVLSearchTree<Key,Value>:: remove( const Key & x ){//public remove
	AvlNode<Key,Value> *t=find(x);
	remove(x,t);
}
template <class Key, class Value>
bool AVLSearchTree<Key,Value>::isEmpty( ) const{
	return root==NULL;
}


 #endif	