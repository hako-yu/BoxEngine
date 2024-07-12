#pragma once

#include "CoreMinimal.h"

class FRHIGeometry
{
public:
	void SetVertexData(void* Data, int Size);
	void SetIndexData(void* Data, int Size);
protected:
	void* VertexData = nullptr;
	int VertexDataSize = 0;
	void* IndexData = nullptr;
	int IndexDataSize = 0;

public:
	virtual void RefreshResource() = 0;
};

class FRHIGeometryManager
{

};
