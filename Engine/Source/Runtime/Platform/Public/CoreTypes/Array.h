
#pragma once

#include <vector>

template<class T>
class TArray : public std::vector<T>
{

public:
	TArray() : std::vector<T>() {}
	TArray(TArray<T>&& Other) : std::vector<T>(std::move(Other)) {}
	TArray(TArray<T>& Other) : std::vector<T>(Other) {}

	void operator=(TArray<T>&& Other)
	{
		std::vector<T>::operator=(std::move(Other));
	}

	int32 Num() const
	{
		return static_cast<int32>(std::vector<T>::size());
	}

	void Add(const T& Elem)
	{
		std::vector<T>::push_back(Elem);
	}

};
