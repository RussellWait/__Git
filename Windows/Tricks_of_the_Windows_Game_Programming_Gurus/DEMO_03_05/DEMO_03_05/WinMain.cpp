#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>


#define WND_CLASS_NAME		"WNDCLASS1"

HWND		main_window_handle	= NULL;
HINSTANCE	hinstance_app		= NULL;


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


	HDC hdc = GetDC(main_window_handle);
	char *str = "GDI Text Demo!";
	UINT len = strlen(str);

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

		SetTextColor(hdc, RGB(rand()%256, rand()%256, rand()%256));
		SetBkColor(hdc, RGB(rand()%256, rand()%256, rand()%256));
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, rand()%400, rand()%300, str, len);

		Sleep(10);
	}

	ReleaseDC(main_window_handle, hdc);

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
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor		= LoadCursor(NULL, IDC_CROSS);
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

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
