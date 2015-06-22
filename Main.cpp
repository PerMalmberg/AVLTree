#include "AVLTree.h"
#include <iostream>

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

class CharPrinter : public AVLPrinter<char>
{
public:
	void Print( char c ) const {
		std::cout << c << " ";
	}
};

void main( void )
{
	// Test cases:
	//http://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct/24064555#24064555

	CharComparer cc;
	AVLTree<char, char> avl( cc );

	const char* input = "hckbeiladfg";

	for( size_t i = 0; i < strlen( input ); ++i ) {
		avl.Add( input[i], input[i] );
	}
	
	avl.Delete( 'a' );
	

	avl.PrintInOrder( CharPrinter() );
}