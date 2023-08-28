
#pragma once

#include <functional>

template<class InFuncType>
class TFunction : public std::function<InFuncType>
{
public:
	TFunction(const function& _Right) : std::function() {}

	template<class T>
	TFunction(T& Func) : std::function<InFuncType>(Func) {}

	/*
	TFunction() : std::function<InFuncType>() {}


	TFunction(const function&& Func) : std::function<InFuncType>(std::move(Func)) {}

	template<class T>
	TFunction(T&& Func) : std::function<InFuncType>(std::move(Func)) {}


	TFunction(const function& Func) : std::function<InFuncType>(Func) {}

	template<class T>
	TFunction(T& Func) : std::function<InFuncType>(Func) {}
	*/
};
