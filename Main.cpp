#include "BinarySearchTree.h"

using namespace PM;

class IntComparer : public IKeyComparer<int>
{
	// Shall return true if lhs > rhs
	virtual bool IsGreater( int lhs, int rhs ) const
	{
		return lhs > rhs;
	}

	// Shall return true if lhs < rhs
	virtual bool IsLess( int lhs, int rhs ) const
	{
		return lhs < rhs;
	}

	// Shall return true if lhs == rhs
	virtual bool AreEqual( int lhs, int rhs ) const
	{
		return lhs == rhs;
	}
};

void main( void )
{
	IntComparer ic;
	BinarySearchTree<int, int> bt( ic );

	bt.Add( 5, 30 );
	bt.Add( 3, 20 );	
	bt.Add( 4, 10 );
	
	
	
	/*
	int val;
	bool res = bt.Find( 2, val );
	bt.Delete( 36 );
	bt.Delete( 50 );
	bt.Delete( 70 );
	bt.Delete( 50 );
	*/
}