#include "MeshProcessor/MeshProcessor.h"

#include "MeshProcessor/VertexFactor.h"

FMeshProcessor::FMeshProcessor()
{
	VertexFactor = new FVertexFactor();
	VertexFactor->Init();
	VertexFactor->SetupVertexLayout();
}

FMeshProcessor::~FMeshProcessor()
{

}
