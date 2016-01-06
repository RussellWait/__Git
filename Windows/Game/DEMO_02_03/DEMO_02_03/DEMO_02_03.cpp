// DEMO_02_03.cpp : 定义应用程序的入口点。
//

#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
#include "DEMO_02_03.h"

// 主窗口类名
#define WINDOW_CLASS_NAME		"WINCLASS1"

// 当前实例
HINSTANCE hInst;

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK	WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// 入口函数
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}


/************************************************************************/
/* 函数名：MyRegisterClass
/* 功  能：注册窗口类
/************************************************************************/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize					= sizeof(WNDCLASSEX);
	wcex.style					= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc			= WindowProc;
	wcex.cbClsExtra				= 0;
	wcex.cbWndExtra				= 0;
	wcex.hInstance				= hInstance;
	wcex.hIcon					= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_DEMO_02_03));
	wcex.hCursor				= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground			= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName			= MAKEINTRESOURCE(IDC_DEMO_02_03);
	wcex.lpszClassName			= WINDOW_CLASS_NAME;
	wcex.hIconSm				= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_DEMO_02_03));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;

	hWnd = CreateWindowEx(	NULL,
							WINDOW_CLASS_NAME,
							"Test Title",
							WS_OVERLAPPEDWINDOW,
							0, 0,
							400, 400,
							NULL,
							NULL,
							hInstance,
							NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

/************************************************************************/
/* 函数名：WindowProc
/* 功  能：处理窗消息
/************************************************************************/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			return (0);
		} break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// you would do all your painting here
			EndPaint(hWnd, &ps);

			return (0);
		} break;

	case WM_DESTROY:
		{
			PostQuitMessage(0);

			return (0);
		} break;

	default:
		break;
	}
}
