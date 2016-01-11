#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include "resource.h"


// 窗口类名称
#define WND_CLASS_NAME		"WNDCLASS1"

// 函数前向声明
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 全局变量
HWND		main_window_handle	= NULL;
HINSTANCE	hinstance_app		= NULL;


// 主函数
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	MSG msg;

	if (!MyRegisterClass(hInstance))
	{
		return FALSE;
	}

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass;

	wndClass.cbSize				= sizeof(WNDCLASSEX);
	wndClass.style				= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc		= WndProc;
	wndClass.cbClsExtra			= 0;
	wndClass.cbWndExtra			= 0;
	wndClass.hInstance			= hInstance;
	wndClass.hIcon				= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_T3DX));
	wndClass.hCursor			= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR_GREEN));
	wndClass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName		= NULL;
	wndClass.lpszClassName		= WND_CLASS_NAME;
	wndClass.hIconSm			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_T3DX));

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindowEx(	NULL,
							WND_CLASS_NAME,
							"Sound Resource Demo",
							WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							0, 0, 400, 300,
							NULL,
							NULL,
							hInstance,
							NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;
	HDC				hdc;

	switch (msg)
	{
	case WM_CREATE:
		{
			PlaySound(MAKEINTRESOURCE(IDR_SOUND_CREATE), hinstance_app, SND_RESOURCE | SND_SYNC);
			PlaySound(MAKEINTRESOURCE(IDR_SOUND_TECHNO), hinstance_app, SND_RESOURCE | SND_ASYNC | SND_LOOP);

			return (0);
		} break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);

			return (0);
		} break;

	case WM_DESTROY:
		{
			PlaySound(NULL, hinstance_app, SND_PURGE);

			PostQuitMessage(0);

			return (0);
		} break;

	default:
		break;
	}

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}
