#pragma once
#include "IKeyComparer.h"

namespace PM {

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	class Node
	{
	public:
		virtual ~Node();
		TData Get();

		typedef Node<TKey, TData> NodeType;

		// Adds the key/data to the tree
		bool Add( TKey key, TData data );
		// Finds the node based on the key
		Node<TKey, TData>* FindNode( const TKey key );
		// Removes the node
		Node<TKey, TData>* Remove();
		// Counts the children of the node.
		int CountChildren();

		// Static factory function, used together with the private constructor to force items to be created on the heap.
		// Update this when a custom memory manager is used. Also see DeleteSelf().
		static NodeType* Create( const IKeyComparer<TKey>& comparer, Node<TKey, TData>* parent, TKey k, TData d );
	private:

		TKey myKey;
		TData myData;
		NodeType* less;
		NodeType* greater;
		NodeType* myParent;
		const IKeyComparer<TKey>& myComparer;		

		Node( const IKeyComparer<TKey>& comparer, Node<TKey, TData>* parent, TKey k, TData d );
		void ReplaceWith( Node<TKey, TData>* node );
		void Skip( NodeType* toSkip, NodeType* next );
		void DeleteSelf();

		// Disable copying
		Node<TKey, TData>( const NodeType& );
		NodeType& operator=( const NodeType& ) { return *this; }; // VS2015 gives a warning if no function is defined.
	};

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>::Node( const IKeyComparer<TKey>& comparer, Node<TKey, TData>* parent, TKey key, TData data )
		: myKey( key ),
		myData( data ),
		less( nullptr ),
		greater( nullptr ),
		myParent( parent ),
		myComparer( comparer )		
	{
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>::~Node() {
		// Delete childs, if any.
		delete less;
		delete greater;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	TData Node<TKey, TData>::Get() {
		return myData;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	bool Node<TKey, TData>::Add( TKey key, TData data )
	{
		bool res;

		if( myComparer.AreEqual( key, myKey ) ) {
			// Can't add same key
			res = false;
		}
		else if( myComparer.IsGreater( key, myKey ) ) {
			// Greater than our own key
			if( greater == nullptr ) {
				// No existing child
				greater = new NodeType( myComparer, this, key, data );
				if( greater ) {
					res = true;
				}
			}
			else {
				res = greater->Add( key, data );
			}
		}
		else {
			// Less than our own key
			if( less == nullptr ) {
				// No existing child
				less = new NodeType( myComparer, this, key, data );
				if( less ) {
					res = true;
				}
			}
			else {
				res = less->Add( key, data );
			}
		}

		return res;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>* Node<TKey, TData>::FindNode( const TKey key )
	{
		// Assume no hit
		NodeType* node = nullptr;

		if( myComparer.AreEqual( key, myKey ) ) {
			// We are it!
			node = this;
		}
		else if( myComparer.IsLess( key, myKey ) ) {
			// If we have a less node, try it
			node = less != 0 ? less->FindNode( key ) : nullptr;
		}
		else if( myComparer.IsGreater( key, myKey ) ) {
			// If we have a greater node, try it.
			node = greater != 0 ? greater->FindNode( key ) : nullptr;
		}

		return node;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	int Node<TKey, TData>::CountChildren()
	{
		return (less == nullptr ? 0 : 1) + (greater == 0 ? 0 : 1);
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>* Node<TKey, TData>::Create( const IKeyComparer<TKey>& comparer, Node<TKey, TData>* parent, TKey k, TData d )
	{
		return new Node( comparer, parent, k, d );
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	void Node<TKey, TData>::DeleteSelf()
	{
		less = nullptr;
		greater = nullptr;
		myParent = nullptr;

		// Assume that we have been allocated dynamically.
		// When this class is extended to use a custom memory manager
		// such as one that allocates a fixed array and uses in place new,
		// that MM needs to be called here instead.
		delete this;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>* Node<TKey, TData>::Remove()
	{
		// Three possible scenarios exists:
		// 1. No children - simply remove it.
		// 2. One child - remove it, letting the parent point to our child.
		// 3. Two children - replace it with the node with next-to-greatest key. Find the left most child in the right tree.

		Node<TKey, TData>* replacement = nullptr;

		int count = CountChildren();

		if( count == 0 ) {
			if( myParent ) {
				// Remove us from our parent
				myParent->Skip( this, nullptr );
			}

			DeleteSelf();
		}
		else if( count == 1 ) {
			replacement = less ? less : greater;
			
			if( myParent ) {
				// Tell our parent to skip us.
				myParent->Skip( this, replacement );
			}

			DeleteSelf();
		}
		else { // count == 2
			// Find next to largest key by following less-side of the right tree.
			NodeType* nextToGreatest = greater;
			while( nextToGreatest->less != nullptr ) {
				nextToGreatest = nextToGreatest->less;
			}
			
			// Replace our key and data
			ReplaceWith( nextToGreatest );
			// Remove the node we took the key and data from
			nextToGreatest->Remove();
			// We are now the replacement
			replacement = this;
		}
		
		// Return the replacement node, in practice only used when the root is removed.
		return replacement;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	void Node<TKey, TData>::ReplaceWith( Node<TKey, TData>* node )
	{
		myKey = node->myKey;
		myData = node->myData;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	void Node<TKey, TData>::Skip( NodeType* toSkip, NodeType* next )
	{
		// Skip the specified node, and use 'next' as the new node.
		if( less == toSkip ) {
			less = next;
		}
		else if( greater == toSkip ) {
			greater = next;
		}
	}
}