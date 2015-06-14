#pragma once
#include "Node.h"
#include "NodeComparer.h"

namespace PM {

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	class BinarySearchTree
	{
	public:
		BinarySearchTree( const INodeComparer<TKey>& comparer );
		virtual ~BinarySearchTree();
		bool Add( TKey key, TData data );
		bool Delete( TKey key );

		typedef Node<TKey, TData> NodeType;
	private:
		const INodeComparer<TKey>& myComparer;
		NodeType* root;
		NodeType* FindNode( TKey key );
	};

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	BinarySearchTree<TKey,TData>::BinarySearchTree( const INodeComparer<TKey>& comparer )
		: myComparer( comparer ), root( 0 )
	{

	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	BinarySearchTree<TKey,TData>::~BinarySearchTree()
	{
		delete root;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	bool BinarySearchTree<TKey,TData>::Add( TKey key, TData data )
	{
		bool res = false;
		if( root == 0 ) {
			// First node
			root = new NodeType( myComparer, key, data );
			if( root ) {
				res = true;
			}
		}
		else {
			// Add to tree
			res = root->Add( key, data );
		}

		return res;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey,TData>* BinarySearchTree<TKey, TData>::FindNode( TKey key )
	{	
		return root->Find( key );
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	bool BinarySearchTree<TKey, TData>::Delete( TKey key )
	{

	}
}