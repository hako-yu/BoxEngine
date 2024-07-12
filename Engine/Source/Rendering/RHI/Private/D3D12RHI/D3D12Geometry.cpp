#include "D3D12RHI/D3D12Geometry.h"

#include "D3D12RHI/D3D12Resources.h"

FD3D12Geometry::FD3D12Geometry(FD3D12Device* ParentDevice)
	: FD3D12DeviceChild(ParentDevice)
{
	
}

FD3D12Geometry::~FD3D12Geometry()
{

}

void FD3D12Geometry::RefreshResource()
{
	ClearBuffer();

	if (VertexData == nullptr || VertexDataSize == 0) return;
	if (IndexData == nullptr || IndexDataSize == 0) return;

	InitBuffer();
}

void FD3D12Geometry::ClearBuffer()
{
	if (VertexBuffer) delete VertexBuffer;
	if (VertexUploadBuffer) delete VertexUploadBuffer;
	if (IndexBuffer) delete IndexBuffer;
	if (IndexUploadBuffer) delete IndexUploadBuffer;
}

void FD3D12Geometry::InitBuffer()
{
	D3D12_HEAP_PROPERTIES HeapProp;
	D3D12_RESOURCE_DESC ResourceDesc;

	FD3D12Resource::InitHeapProp(HeapProp, D3D12_HEAP_TYPE_DEFAULT);
	FD3D12Resource::InitResourceDesc(ResourceDesc, VertexDataSize);
	VertexBuffer = new FD3D12Resource(ParentDevice,
		&HeapProp,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr);

	FD3D12Resource::InitHeapProp(HeapProp, D3D12_HEAP_TYPE_UPLOAD);
	FD3D12Resource::InitResourceDesc(ResourceDesc, VertexDataSize);
	VertexUploadBuffer = new FD3D12Resource(ParentDevice,
		&HeapProp,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr);

	FD3D12Resource::InitHeapProp(HeapProp, D3D12_HEAP_TYPE_DEFAULT);
	FD3D12Resource::InitResourceDesc(ResourceDesc, IndexDataSize);
	IndexBuffer = new FD3D12Resource(ParentDevice,
		&HeapProp,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr);

	FD3D12Resource::InitHeapProp(HeapProp, D3D12_HEAP_TYPE_UPLOAD);
	FD3D12Resource::InitResourceDesc(ResourceDesc, IndexDataSize);
	IndexUploadBuffer = new FD3D12Resource(ParentDevice,
		&HeapProp,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr);
}
