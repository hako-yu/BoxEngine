
#pragma once

#include <queue>

template<class T>
class TQueue : public std::queue<T>
{

public:
	TQueue() : std::queue<T>() {}
	TQueue(TQueue<T>&& Other) : std::queue<T>(std::move(Other)) {}
	TQueue(TQueue<T>& Other) : std::queue<T>(Other) {}

	void operator=(TQueue<T>&& Other)
	{
		std::queue<T>::operator=(std::move(Other));
	}

	int32 Num() const
	{
		return static_cast<int32>(std::queue<T>::size());
	}

	void Push(const T& Elem)
	{
		std::queue<T>::push(Elem);
	}

	void Pop()
	{
		std::queue<T>::pop();
	}

	T* Front()
	{
		if (std::queue<T>::empty())
		{
			return nullptr;
		}
		return &std::queue<T>::front();
	}

};
