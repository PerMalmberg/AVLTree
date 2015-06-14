#pragma once
#include "Node.h"
#include "IKeyComparer.h"

namespace PM {

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	class BinarySearchTree
	{
	public:
		// Creates the BTS. The provided comparer is used to determine
		// relation ship between the keys.
		BinarySearchTree( const IKeyComparer<TKey>& comparer );
		virtual ~BinarySearchTree();

		// Adds the data based on the provided key
		bool Add( TKey key, TData data );

		// Finds data, based on the key.
		// The data is provided on the output parameter 'data'.
		bool Find( TKey key, TData& data );

		// Delets a key from the tree
		void Delete( TKey key );
	private:
		typedef Node<TKey, TData> NodeType;
		const IKeyComparer<TKey>& myComparer;
		NodeType* root;
		NodeType* FindNode( TKey key );
	};

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	BinarySearchTree<TKey,TData>::BinarySearchTree( const IKeyComparer<TKey>& comparer )
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
			root = NodeType::Create( myComparer, nullptr, key, data );
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
		NodeType* node = nullptr;

		if( root ) {
			node = root->FindNode( key );
		}

		return node;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	bool BinarySearchTree<TKey, TData>::Find( TKey key, TData& data )
	{		
		bool res = false;
		NodeType* node = FindNode( key );

		if( node ) {
			data = node->Get();
			res = true;
		}

		return res;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	void BinarySearchTree<TKey, TData>::Delete( TKey key )
	{
		// First, find the node to remove
		NodeType* toRemove = FindNode( key );
		if( toRemove ) {
			// We have found a key to remove.

			// Are we removing the root?
			bool removingRoot = toRemove == root;
			
			// Get the replacement node 
			NodeType* replacement = toRemove->Remove();

			// Update the root, if it was deleted.
			if( removingRoot ) {
				root = replacement;
			}
		}
	}
}