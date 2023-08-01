
#include "Application/PlatformApp.h"
#include "Application/WindowsApp.h"

/*
 * AppCore
 */
FPlatformAppConfig GPlatformAppConfig;
IPlatformAppCallbackInterface* GPlatformAppProc = nullptr;

/*
 * WindowsApp
 */
HINSTANCE hInstance = nullptr;
HWND hMainWnd = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*
 * Function
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		GPlatformAppProc->OnActivate();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		GPlatformAppProc->OnDestory();
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		GPlatformAppProc->OnMouseDown();
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		GPlatformAppProc->OnMouseUp();
		return 0;
	case WM_MOUSEMOVE:
		GPlatformAppProc->OnMouseMove();
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void FPlatformApplication::CreateMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass Failed.", 0, 0);
		return;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, GPlatformAppConfig.Width, GPlatformAppConfig.Height };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	hMainWnd = CreateWindow(
		"MainWnd",
		"BoxEngine",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
	if (!hMainWnd)
	{
		MessageBox(0, "CreateWindow Failed.", 0, 0);
		return;
	}
}

void FPlatformApplication::ShowMainWindow()
{
	ShowWindow(hMainWnd, SW_SHOW);
}

void FPlatformApplication::PumpMessages()
{
	MSG Msg;
	while (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}
