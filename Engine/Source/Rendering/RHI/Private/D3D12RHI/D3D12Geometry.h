#pragma once

#include "RHICore/RHIGeometry.h"

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Resource;

class FD3D12Geometry : public FRHIGeometry, public FD3D12DeviceChild
{
public:
	FD3D12Geometry(FD3D12Device* ParentDevice);
	~FD3D12Geometry();

public:
	virtual void RefreshResource() override;
protected:
	void ClearBuffer();
	void InitBuffer();
protected:
	FD3D12Resource* VertexBuffer = nullptr;
	FD3D12Resource* VertexUploadBuffer = nullptr;
	FD3D12Resource* IndexBuffer = nullptr;
	FD3D12Resource* IndexUploadBuffer = nullptr;
};
