
#pragma once

enum class ERHIType : uint32
{
	None,
	D3D12RHI
};

class FRHIViewport;

class FRHI
{
public:
	virtual void Init() = 0;

	virtual FRHIViewport* CreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY) = 0;

private:
	ERHIType RHIType = ERHIType::None;
};
