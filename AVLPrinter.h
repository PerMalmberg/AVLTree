#pragma once

template<typename TData>
class AVLPrinter
{
public:
	virtual void Print( TData data ) const = 0;
};