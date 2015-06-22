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

class CharComparer : public IKeyComparer<char>
{
	// Shall return true if lhs > rhs
	virtual bool IsGreater( char lhs, char rhs ) const
	{
		return lhs > rhs;
	}

	// Shall return true if lhs < rhs
	virtual bool IsLess( char lhs, char rhs ) const
	{
		return lhs < rhs;
	}

	// Shall return true if lhs == rhs
	virtual bool AreEqual( char lhs, char rhs ) const
	{
		return lhs == rhs;
	}
};

void main( void )
{
	CharComparer cc;
	BinarySearchTree<char, char> bt( cc );

	const char* input = "hckbeiladfg";

	for( int i = 0; i < strlen( input ); ++i ) {
		bt.Add( input[i], input[i] );
	}
	
	bt.Delete( 'a' );
	
	/*
	int val;
	bool res = bt.Find( 2, val );
	bt.Delete( 36 );
	bt.Delete( 50 );
	bt.Delete( 70 );
	bt.Delete( 50 );
	*/

	bt.PrintInOrder();
}