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
		bool Find( TKey key, TData& data );
		void Delete( TKey key );

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
			root = new NodeType( myComparer, __nullptr, key, data );
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
		NodeType* node = __nullptr;

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
		// Three possible scenarios exists:
		// 1. No children - simply remove it.
		// 2. One child - remove it, letting the parent point to the child.
		// 3. Two children - replace it with the node with next biggest key. Find the left most child in the right tree.
		// If the node to remove is the root, we must update our root-pointer aswell.

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