//Zeynep Tandogan
#ifndef _BINARYSEARCHTREE_CPP
#define _BINARYSEARCHTREE_CPP


template <class Key, class Value>
class BinarySearchTree;

template <class Key, class Value>
 class BinaryNode
{
	 Key 	element;
	 Value info;
	 BinaryNode  *left;
	 BinaryNode  *right;
	
	 BinaryNode( const Key & theElement,Value t, BinaryNode *lt, BinaryNode *rt)
                    : element( theElement ),info(t), left( lt ), right( rt ){ }

     friend class BinarySearchTree<Key,Value>;
};

template <class Key, class Value>
class BinarySearchTree
{
public:
	explicit BinarySearchTree( const Value & notFound );
	BinarySearchTree( const BinarySearchTree & rhs );
    ~BinarySearchTree( );//

	const Key & findMin( ) const;
	const Key & findMax( ) const;
	const Value & find( const Key & x ) const;
	bool isEmpty( ) const;
	void printTree( ) const;
	
	void makeEmpty( );
	void insert( const Key & x,const Value & y );
	void remove( const Key & x );
	const BinarySearchTree & operator=( const BinarySearchTree & rhs );

private:
    BinaryNode<Key,Value> *root;
    Value ITEM_NOT_FOUND;

	const Value & elementAt( BinaryNode<Key,Value> *t ) const;

    void insert( const Key & x,const Value & y, BinaryNode<Key,Value> * & t ) const;
    void remove(const Key & x, BinaryNode<Key,Value> * & t ) const;

    BinaryNode<Key,Value> * findMin( BinaryNode<Key,Value> *t ) const;
    BinaryNode<Key,Value> * findMax( BinaryNode<Key,Value> *t ) const;
    BinaryNode<Key,Value> * find( const Key & x, BinaryNode<Key,Value> *t )  const;
                                                                                                       
   void makeEmpty( BinaryNode<Key,Value> * & t ) ;
   void printTree( BinaryNode<Key,Value> *t ) const;
   BinaryNode<Key,Value> * clone( BinaryNode<Key,Value> *t ) const;

};


#include "BinarySearchTree.cpp"
#endif