//Zeynep Tandogan
#ifndef _AVLSEARCHTREE_CPP
#define _AVLSEARCHTREE_CPP


template <class Key, class Value>
class AVLSearchTree;

template <class Key, class Value>
 class AvlNode
{
	 Key 	element;
	 Value info;
	 AvlNode  *left;
	 AvlNode  *right;
	 int   height;
	 
	 AvlNode( const Key & theElement,Value t, AvlNode *lt, AvlNode *rt, int h = 0 )
                    : element( theElement ),info(t), left( lt ), right( rt ), height( h ) { }

     friend class AVLSearchTree<Key,Value>;
};

template <class Key, class Value>
class AVLSearchTree
{
public:
	explicit AVLSearchTree( const Value & notFound );//
	AVLSearchTree( const AVLSearchTree & rhs );//
    ~AVLSearchTree( );//

	const Key & findMin( ) const;//
	const Key & findMax( ) const;//
	const Value & find( const Key & x ) const;//
	bool isEmpty( ) const;//
	void printTree( ) const;//
	
	void makeEmpty( );//
	void insert( const Key & x,const Value & y );//
	void remove( const Key & x );//
	const AVLSearchTree & operator=( const AVLSearchTree & rhs );//

private:
    AvlNode<Key,Value> *root;
    Value ITEM_NOT_FOUND;

	const Value & elementAt( AvlNode<Key,Value> *t ) const;//

    void insert( const Key & x,const Value & y, AvlNode<Key,Value> * & t ) const;//
    void remove(const Key & x, AvlNode<Key,Value> * & t ) const;//

    AvlNode<Key,Value> * findMin( AvlNode<Key,Value> *t ) const;//
    AvlNode<Key,Value> * findMax( AvlNode<Key,Value> *t ) const;//
    AvlNode<Key,Value> * find( const Key & x, AvlNode<Key,Value> *t )  const;//
                                                                                                       
   void makeEmpty( AvlNode<Key,Value> * & t ) ;//
   void printTree( AvlNode<Key,Value> *t ) const;//
   AvlNode<Key,Value> * clone( AvlNode<Key,Value> *t ) const;//

   // Avl manipulations
   int height( AvlNode<Key,Value> *t ) const;//
   int max( int lhs, int rhs ) const;//
   void rotateWithLeftChild( AvlNode<Key,Value> * & k2 ) const;//
   void rotateWithRightChild( AvlNode<Key,Value> * & k1 ) const;//
   void doubleWithLeftChild( AvlNode<Key,Value> * & k3 ) const;//
   void doubleWithRightChild( AvlNode<Key,Value> * & k1 ) const;//

};

#include "AVLsearchtree.cpp"
#endif