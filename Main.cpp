#include "AVLTree.h"
#include <iostream>
#include <cstring>

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

class CharPrinter : public ITraverseCallback<char>
{
public:
	void Traversed( char c ) {
		std::cout << c << " ";
	}
};

class InOrderVerifier : public ITraverseCallback<char>
{
private:
	bool isOk;
	bool first;
	char myC;
public:
	InOrderVerifier()
		: isOk( true ), first( true )
	{		
	}
	
	void Traversed( char c ) {
		if( first ) {
			myC = c;
			first = false;
		}
		else {
			isOk &= myC < c;
			myC = c;
		}
	}

	void Reset() 
	{
		isOk = true;
		first = true;
	}

	bool IsOk() 
	{
		return isOk;
	}
};

template<typename TKey, typename TData>
void Test( const TKey* input, AVLTree<TKey,TData>& tree, const TKey* deleteKey )
{
	tree.Clear();
	for( size_t i = 0; i < strlen( input ); ++i ) {
		tree.Add( input[i], input[i] );
	}

	if( deleteKey ) {
		tree.Delete( *deleteKey );
	}

	InOrderVerifier iv;
	tree.TraverseInOrder( iv );

	std::cout << (iv.IsOk() ? "OK" : "FAIL") << std::endl;
}

void Test( bool result, bool expected )
{
	std::cout << (result == expected ? "OK" : "FAIL") << std::endl;
}

int main( void )
{
	// Test cases:
	//http://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct/24064555#24064555

	CharComparer cc;
	AVLTree<char, char> avl( cc );
	Test<char, char>( "cba", avl, nullptr );
	Test<char, char>( "acb", avl, nullptr );
	Test<char, char>( "cab", avl, nullptr );

	Test<char, char>( "bcad", avl, "a" );
	Test<char, char>( "cbda", avl, "d" );
	Test<char, char>( "bdac", avl, "a" );
	Test<char, char>( "cadb", avl, "d" );
	Test<char, char>( "cbedfag", avl, "a" );
	Test<char, char>( "cbedfg", avl, nullptr );
	Test<char, char>( "ecfbdga", avl, "g" );
	Test<char, char>( "ecfbda", avl, nullptr );
	Test<char, char>( "ecjadhkgilbf", avl, "b" );
	Test<char, char>( "ecjadhkgilf", avl, nullptr );
	Test<char, char>( "hckbeiladfjg", avl, "j" );
	Test<char, char>( "hckbeiladfg", avl, nullptr );


	Test<char, char>( "abc", avl, nullptr );
	Test( avl.Add( 'a', 'a' ), false );
	Test( avl.Add( 'b', 'c' ), false );
	Test( avl.Add( 'c', 'c' ), false );
	Test( avl.Add( 'd', 'd' ), true );
	Test( avl.Add( 'e', 'e' ), true );
	char out;
	Test( avl.Find( 'e', out ), true );
	Test( avl.Find( 'a', out ), true );
	Test( avl.Find( 'b', out ), true );
	Test( avl.Find( 'c', out ), true );
	Test( avl.Find( 'd', out ), true );
	Test( avl.Find( 'f', out ), false );

	Test<char, char>( "abcdefghijklmnopqrstuvwxyz", avl, nullptr );
	Test<char, char>( "abcdefghijklmnopqrstuvwxyz", avl, "p" );
	Test<char, char>( "abcdefghijklmnopqrstuvwxyz", avl, "a" );
	Test<char, char>( "abcdefghijklmnopqrstuvwxyz", avl, "z" );
	Test<char, char>( "abcdefghijklmnopqrstuvwxyz", avl, "e" );
	Test<char, char>( "abcdefghijklmnopqrstuvwxyz", avl, "y" );

	return 0;
}