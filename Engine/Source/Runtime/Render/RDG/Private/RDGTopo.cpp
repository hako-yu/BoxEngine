
#include "RDGTopo.h"

void FRDGTopoGraph::AddNode(FRDGNode* Node)
{
	if (IsCompiled)
	{
		return;
	}

	Node->NodeIndex = NodeList.Num();
	NodeList.Add(Node);
}

void FRDGTopoGraph::Sort()
{
	if (IsCompiled)
	{
		return;
	}

	IsCompiled = true;

	int BeginSortIndex = 0;
	int EndSortIndex = NodeList.Num() - 1;

	while (BeginSortIndex < EndSortIndex)
	{
		int NewBeginSortIndex = BeginSortIndex;
		for (int i = BeginSortIndex; i <= EndSortIndex; i++)
		{
			FRDGNode* Node = NodeList[i];
			bool IsReady = true;

			for (int j = 0; j < Node->In.Num(); j++)
			{
				if (Node->In[j]->NodeIndex >= NewBeginSortIndex)
				{
					IsReady = false;
					break;
				}
			}

			if (IsReady)
			{
				SwapNode(Node->NodeIndex, NewBeginSortIndex);
				NewBeginSortIndex++;
			}
		}

		if (NewBeginSortIndex == BeginSortIndex)
		{
			// Error Topo Graph !!!
			return;
		}
	}
}

void FRDGTopoGraph::Clear()
{
	IsCompiled = false;
	NodeList.clear();
}

void FRDGTopoGraph::SwapNode(uint32 IndexA, uint32 IndexB)
{
	FRDGNode* TmpNode = NodeList[IndexA];
	NodeList[IndexA] = NodeList[IndexB];
	NodeList[IndexB] = TmpNode;

	NodeList[IndexA]->NodeIndex = IndexA;
	NodeList[IndexB]->NodeIndex = IndexB;
}
