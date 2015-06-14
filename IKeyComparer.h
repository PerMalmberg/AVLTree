#pragma once

namespace PM {

	template<typename TKey>
	class IKeyComparer
	{
	public:
		// Shall return true if lhs > rhs
		virtual bool IsGreater(TKey lhs, TKey rhs) const = 0;
		// Shall return true if lhs < rhs
		virtual bool IsLess( TKey lhs, TKey rhs ) const = 0;
		// Shall return true if lhs == rhs
		virtual bool AreEqual( TKey lhs, TKey rhs ) const = 0;
	};

}
