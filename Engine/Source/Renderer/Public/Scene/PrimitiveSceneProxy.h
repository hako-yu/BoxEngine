#pragma once

#include <DirectXMath.h>
#include <vector>

struct FVertex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

class FPrimitiveSceneProxy
{
private:
    std::vector<FVertex> Vertexs;
    std::vector<int> Indexs;
};
