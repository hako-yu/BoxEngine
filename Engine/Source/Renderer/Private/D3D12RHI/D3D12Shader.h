#pragma once

#include "D3D12RHI/D3D12Common.h"
#include <string>

class FD3D12Shader
{
private:
	std::wstring FileName;

private:
	ComPtr<ID3DBlob> Code;
};
