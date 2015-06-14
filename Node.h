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
		Node( const INodeComparer<TKey>& comparer, TKey k, TData d );
		virtual ~Node();
		TData Get();

		typedef Node<TKey, TData> NodeType;

		bool Add( TKey key, TData data );
	private:
		TKey myKey;
		TData myData;
		NodeType* less;
		NodeType* greater;
		const INodeComparer<TKey>& myComparer;

		// Disable copying
		Node<TKey, TData>( const NodeType& );
		NodeType& operator=( const NodeType& ) { return *this; }; // VS2015 gives a warning if no function is defined.
	};

	/////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////
	template<typename TKey, typename TData>
	Node<TKey, TData>::Node( const INodeComparer<TKey>& comparer, TKey key, TData data )
		: myKey( key ),
		myData( data ),
		less( __nullptr ),
		greater( __nullptr ),
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
		return myTData;
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
				greater = new NodeType( myComparer, key, data );
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
				less = new NodeType( myComparer, key, data );
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
}