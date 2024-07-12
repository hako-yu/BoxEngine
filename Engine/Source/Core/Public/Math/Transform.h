#pragma once

#include "Math/Vector.h"

class FTransform
{
public:
	FTransform()
		: Scale(1, 1, 1)
		, Transition(0, 0, 0)
		, Rotation(0, 0, 0)
	{}

public:
	FVector Scale;
	FVector Transition;
	FVector Rotation;
};
