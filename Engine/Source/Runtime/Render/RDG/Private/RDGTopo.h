
#pragma once

#include "CoreMinimal.h"

class FRDGNode
{
	friend class FRDGTopoGraph;

protected:
	TArray<FRDGNode*> In;
	TArray<FRDGNode*> Out;

private:
	uint32 NodeIndex;
};

class FRDGTopoGraph
{
public:
	const TArray<FRDGNode*>& GetResult() { return NodeList; }

public:
	void AddNode(FRDGNode* Node);

	void Sort();
	void Clear();

private:
	void SwapNode(uint32 IndexA, uint32 IndexB);

private:
	bool IsCompiled = false;

	TArray<FRDGNode*> NodeList;
};
