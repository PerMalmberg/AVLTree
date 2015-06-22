#pragma once
#include "Node.h"
#include "IKeyComparer.h"
#include "AVLPrinter.h"

namespace PM {
	
	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	class AVLTree
	{
	public:
		// Creates the BTS. The provided comparer is used to determine
		// relation ship between the keys.
		AVLTree( const IKeyComparer<TKey>& comparer );
		virtual ~AVLTree();

		// Adds the data based on the provided key
		bool Add( TKey key, TData data );

		// Finds data, based on the key.
		// The data is provided on the output parameter 'data'.
		bool Find( TKey key, TData& data );

		// Delets a key from the tree
		void Delete( TKey key );

		void PrintInOrder( const AVLPrinter<TData>& printer );
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
	AVLTree<TKey,TData>::AVLTree( const IKeyComparer<TKey>& comparer )
		: myComparer( comparer ), root( 0 )
	{

	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	AVLTree<TKey,TData>::~AVLTree()
	{
		delete root;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	bool AVLTree<TKey,TData>::Add( TKey key, TData data )
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
	Node<TKey,TData>* AVLTree<TKey, TData>::FindNode( TKey key )
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
	bool AVLTree<TKey, TData>::Find( TKey key, TData& data )
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
	void AVLTree<TKey, TData>::Delete( TKey key )
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

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	void AVLTree<TKey, TData>::PrintInOrder( const AVLPrinter<TData>& printer )
	{
		if( root ) {
			root->PrintInOrder( printer );
		}
	}
}