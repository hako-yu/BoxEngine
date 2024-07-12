#pragma once

template<typename T>
struct TVector
{
	TVector(T InX, T InY, T InZ)
		: X(InX), Y(InY), Z(InZ)
	{}

	T X;
	T Y;
	T Z;
};

typedef TVector<float> FVector;
