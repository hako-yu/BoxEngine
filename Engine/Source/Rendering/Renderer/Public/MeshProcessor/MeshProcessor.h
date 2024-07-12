#pragma once

class FVertexFactor;

class FMeshProcessor
{
public:
	FMeshProcessor();
	~FMeshProcessor();

public:
	void Process();

protected:
	FVertexFactor* VertexFactor = nullptr;
};
