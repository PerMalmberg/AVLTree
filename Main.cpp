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

	bt.Add( 50, 50 );
	bt.Add( 30, 30 );
	bt.Add( 20, 20 );
	bt.Add( 40, 40 );
	bt.Add( 32, 32 );
	bt.Add( 34, 34 );
	bt.Add( 36, 36 );
	bt.Add( 70, 70 );
	bt.Add( 60, 60 );
	bt.Add( 65, 65 );
	bt.Add( 80, 80 );
	bt.Add( 75, 75 );
	bt.Add( 85, 85 );


	int val;
	bool res = bt.Find( 2, val );
	bt.Delete( 50 );
	bt.Delete( 70 );
	bt.Delete( 50 );

}