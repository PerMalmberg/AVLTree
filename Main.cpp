#include "BinarySearchTree.h"

using namespace PM;

class IntComparer : public INodeComparer<int>
{
	virtual bool IsGreater( int lhs, int rhs ) const
	{
		return lhs > rhs;
	}

	// Shall true if lhs < rhs
	virtual bool IsLess( int lhs, int rhs ) const
	{
		return lhs < rhs;
	}

	// Shall true if lhs == rhs
	virtual bool AreEqual( int lhs, int rhs ) const
	{
		return lhs == rhs;
	}
};

void main( void )
{
	IntComparer ic;
	BinarySearchTree<int, int> bt( ic );

	bt.Add( 5, 5 );
	bt.Add( 4, 4 );
	bt.Add( 9, 9 );
	bt.Add( 2, 2 );
	bt.Add( 8, 8 );
	bt.Add( 7, 7 );

}