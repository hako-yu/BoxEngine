#include "MeshProcessor/VertexFactor.h"

#include "RHICore/RHICommon.h"
#include "RHICore/RHICommands.h"

FVertexFactor::FVertexFactor()
{

}

FVertexFactor::~FVertexFactor()
{

}

void FVertexFactor::Init()
{
	Layout.push_back({ "POSITION", ERHIVertexLayoutItemFormat::Float3 });
	Layout.push_back({ "COLOR", ERHIVertexLayoutItemFormat::Float4 });
}

void FVertexFactor::SetupVertexLayout()
{
	EXECUTE_RHI_COMMAND(ResetVertexLayout)();

	for (const FVertexLayout& Item : Layout)
	{
		EXECUTE_RHI_COMMAND(AddVertexLayoutItem)(Item.Name, Item.Format);
	}
}
