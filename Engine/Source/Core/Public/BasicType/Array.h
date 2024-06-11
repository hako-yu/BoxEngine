#pragma once

#include <vector>

template<class ElemType>
class TArray : protected std::vector<ElemType>
{
public:
	void Add(ElemType& Elem)
	{
		push_back(Elem);
	}
};
