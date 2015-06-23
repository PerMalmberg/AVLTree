#pragma once

template<typename TData>
class ITraverseCallback
{
public:
	virtual void Traversed( TData data ) = 0;
};