#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>


#define WND_CLASS_NAME		"WNDCLASS1"

HWND		main_window_handle	= NULL;
HINSTANCE	hinstance_app		= NULL;

char buffer[80];
static int wm_paint_count = 0;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, UINT nShowCmd);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
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
	hinstance_app = hInstance;

	WNDCLASSEX wndClass;

	wndClass.cbSize			= sizeof(WNDCLASSEX);
	wndClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wndClass.hCursor		= LoadCursor(NULL, MAKEINTRESOURCE(IDC_CROSS));
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, MAKEINTRESOURCE(IDI_HAND));

	return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, UINT nShowCmd)
{
	main_window_handle = CreateWindowEx(	NULL,
		WND_CLASS_NAME,
		"GDI Text Printing Demo",
		WS_OVERLAPPEDWINDOW,
		0, 0, 400, 300,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!main_window_handle)	
	{
		return FALSE;
	}

	ShowWindow(main_window_handle, nShowCmd);
	UpdateWindow(main_window_handle);

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

			SetTextColor(hdc, RGB(rand()%256, rand()%256, rand()%256));
			SetBkColor(hdc, RGB(rand()%256, rand()%256, rand()%256));
			SetBkMode(hdc, OPAQUE);

			sprintf_s(buffer, 80, "WM_PAINT called %d times.", ++wm_paint_count);
			TextOut(hdc, 0, 0, buffer, strlen(buffer));

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

	DefWindowProc(hWnd, msg, wParam, lParam);
}
