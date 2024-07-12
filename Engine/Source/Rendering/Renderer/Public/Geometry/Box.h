#pragma once

#include "Geometry/MeshGeometry.h"

class FBox
{
public:
	static FMeshGeometry Create()
	{
		FMeshGeometry Mesh;
		Mesh.Vertexs = {
            FVector(-1.0f, -1.0f, -1.0f),
			FVector(-1.0f, +1.0f, -1.0f),
			FVector(+1.0f, +1.0f, -1.0f),
			FVector(+1.0f, -1.0f, -1.0f),
			FVector(-1.0f, -1.0f, +1.0f),
			FVector(-1.0f, +1.0f, +1.0f),
			FVector(+1.0f, +1.0f, +1.0f),
			FVector(+1.0f, -1.0f, +1.0f)
		};
		
		Mesh.Indexs = {
			// front face
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7
		};
		return Mesh;
	}
};
