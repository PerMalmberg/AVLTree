#pragma once

namespace PM {

	template<typename TKey>
	class IKeyComparer
	{
	public:
		// Shall true if lhs > rhs
		virtual bool IsGreater(TKey lhs, TKey rhs) const = 0;
		// Shall true if lhs < rhs
		virtual bool IsLess( TKey lhs, TKey rhs ) const = 0;
		// Shall true if lhs == rhs
		virtual bool AreEqual( TKey lhs, TKey rhs ) const = 0;
	};

}
