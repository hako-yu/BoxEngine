#pragma once

class FViewport
{
public:
	FViewport(int InWidth = 1024, int InHeight = 768);
	~FViewport();

public:
	void AddToWindow(void* InAppInstance);
	void Update();

private:
	// Viewport Size
	int Width;
	int Height;

	// Window Handle
	void* Wnd;

	void* AppInstance;
};
