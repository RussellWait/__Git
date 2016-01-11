#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include "resource.h"


#define WND_CLASS_NAME	"WNDCLASS1"

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
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


	return msg.wParam;
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
	wndClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor			= LoadCursor(NULL, IDC_CROSS);
	wndClass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName		= MAKEINTRESOURCE(MENU_MAINMENU1);	// 所有由该窗口类创建的实例都含有此菜单（优先级低）
	wndClass.lpszClassName		= WND_CLASS_NAME;
	wndClass.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindowEx(	NULL,
							WND_CLASS_NAME,
							"Menu Resource Demo",
							WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							0, 0, 400, 300,
							NULL,
							LoadMenu(hInstance, MAKEINTRESOURCE(MENU_MAINMENU2)),	// 当前窗口含有菜单（优先级中）
							hInstance,
							NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SetMenu(hWnd, LoadMenu(hInstance, MAKEINTRESOURCE(MENU_MAINMENU3)));			// 当前窗口含有菜单（优先级高）

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

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}
