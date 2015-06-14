#pragma once
#include "NodeComparer.h"

namespace PM {

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	class Node
	{
	public:
		Node( const INodeComparer<TKey>& comparer, Node<TKey, TData>* parent, TKey k, TData d );
		virtual ~Node();
		TData Get();

		typedef Node<TKey, TData> NodeType;

		bool Add( TKey key, TData data );
		Node<TKey, TData>* FindNode( TKey key );
		Node<TKey, TData>* Remove();
		int CountChildren();
	private:

		TKey myKey;
		TData myData;
		NodeType* less;
		NodeType* greater;
		const INodeComparer<TKey>& myComparer;
		Node<TKey, TData>* myParent;

		void ReplaceWith( Node<TKey, TData>* node );
		void Skip( NodeType* toSkip, NodeType* next );
		void Clear();

		// Disable copying
		Node<TKey, TData>( const NodeType& );
		NodeType& operator=( const NodeType& ) { return *this; }; // VS2015 gives a warning if no function is defined.
	};

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>::Node( const INodeComparer<TKey>& comparer, Node<TKey, TData>* parent, TKey key, TData data )
		: myKey( key ),
		myData( data ),
		less( __nullptr ),
		greater( __nullptr ),
		myComparer( comparer ),
		myParent( parent )
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
			if( greater == __nullptr ) {
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
			if( less == __nullptr ) {
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
	Node<TKey, TData>* Node<TKey, TData>::FindNode( TKey key )
	{
		// Assume no hit
		NodeType* node = __nullptr;

		if( myComparer.AreEqual( key, myKey ) ) {
			// We are it!
			node = this;
		}
		else if( myComparer.IsLess( key, myKey ) ) {
			// If we have a less node, try it
			node = less != 0 ? less->FindNode( key ) : __nullptr;
		}
		else if( myComparer.IsGreater( key, myKey ) ) {
			// If we have a greater node, try it.
			node = greater != 0 ? greater->FindNode( key ) : __nullptr;
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
		return (less == __nullptr ? 0 : 1) + (greater == nullptr ? 0 : 1);
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	void Node<TKey, TData>::Clear()
	{
		less = __nullptr;
		greater = __nullptr;
		myParent = __nullptr;
	}

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>* Node<TKey, TData>::Remove()
	{
		Node<TKey, TData>* replacementRoot = __nullptr;

		int count = CountChildren();

		if( count == 0 ) {
			if( myParent ) {
				myParent->Skip( this, __nullptr );
			}

			Clear();
			delete this;
		}
		else if( count == 1 ) {
			replacementRoot = less ? less : greater;
			
			if( myParent ) {
				myParent->Skip( this, replacementRoot );
			}

			Clear();
			delete this;
		}
		else { // count == 2
			// Find next to largest key by following less-side of the right tree.
			NodeType* nextToGreatest = greater;
			while( nextToGreatest->less != __nullptr ) {
				nextToGreatest = nextToGreatest->less;
			}
			
			ReplaceWith( nextToGreatest );

			nextToGreatest->Remove();
			replacementRoot = this;
		}
		
		return replacementRoot;
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
		if( less == toSkip ) {
			less = next;
		}
		else if( greater == toSkip ) {
			greater = next;
		}
	}
}