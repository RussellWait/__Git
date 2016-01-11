// 不使用MFC
#define WIN32_LEAN_AND_MEAN

// 加载头文件
#include <windows.h>
#include <windowsx.h>
#include "resource.h"


// 窗口类名称
#define WINDOW_CLASS_NAME	"WNDCLASS1"

// 函数前向声明
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// 主函数
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	// 测试字符串表
	char loadString[80];
	char saveString[80];

	if (!LoadString(hInstance, IDS_STRING_LOAD, loadString, 80) ||
		!LoadString(hInstance, IDS_STRING_SAVE, saveString, 80))
	{
		return FALSE;
	}
	// 测试结束

	
	MSG msg;

	if (!MyRegisterClass(hInstance))
	{
		return FALSE;
	}

	if (!InitInstance(hInstance, nShowCmd))
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

	wndClass.cbSize					= sizeof(WNDCLASSEX);
	wndClass.style					= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc			= WndProc;
	wndClass.cbClsExtra				= 0;
	wndClass.cbWndExtra				= 0;
	wndClass.hInstance				= hInstance;
	wndClass.hIcon					= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_T3DX));
	wndClass.hCursor				= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR_BLUE));
	wndClass.hbrBackground			= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName			= NULL;
	wndClass.lpszClassName			= WINDOW_CLASS_NAME;
	wndClass.hIconSm				= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_T3DX));

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	HWND hWnd;

	hWnd = CreateWindowEx(	NULL,
							WINDOW_CLASS_NAME,
							"Demo of Custom Cursor and Icon",
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
			PostQuitMessage(0);
			
			return (0);
		} break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
