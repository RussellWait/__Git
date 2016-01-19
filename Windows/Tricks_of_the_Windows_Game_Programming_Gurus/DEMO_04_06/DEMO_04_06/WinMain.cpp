#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>


#define WND_CLASS_NAME		"WNDCLASS1"
#define WND_WIDTH			640
#define WND_HEIGHT			480

#define TIMER_ID1_SEC		1
#define TIMER_ID2_SEC		2
#define TIMER_ID3_SEC		3


HWND main_window_handle = NULL;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nShowCmd);
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

	return (msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass;

	wndClass.cbSize			= sizeof(WNDCLASSEX);
	wndClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	main_window_handle = CreateWindowEx(	NULL,
											WND_CLASS_NAME,
											"Multiple Timer Demo",
											WS_OVERLAPPEDWINDOW,
											0, 0, WND_WIDTH, WND_HEIGHT,
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
	HDC			hdc;
	PAINTSTRUCT	ps;
	
	char buffer[80];
	static int counter1 = 0;
	static int counter2 = 0;
	static int counter3 = 0;

	switch (msg)
	{
	case WM_CREATE:
		{
			SetTimer(hWnd, TIMER_ID1_SEC, 1000, NULL);
			SetTimer(hWnd, TIMER_ID2_SEC, 3000, NULL);
			SetTimer(hWnd, TIMER_ID3_SEC, 10000, NULL);

			return (0);
		} break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);

			return (0);
		} break;

	case WM_TIMER:
		{
			hdc = GetDC(hWnd);

			SetBkColor(hdc,RGB(0, 0, 0));
			SetBkMode(hdc, OPAQUE);

			switch (wParam)
			{
			case TIMER_ID1_SEC:
				{
					SetTextColor(hdc, RGB(255, 0, 0));
					sprintf(buffer, "The 1 second timer has fired %d times", ++counter1);
					TextOut(hdc, 0, 0, buffer, strlen(buffer));
				} break;

			case TIMER_ID2_SEC:
				{
					SetTextColor(hdc, RGB(0, 255, 0));
					sprintf(buffer, "The 3 second timer has fired %d times", ++counter2);
					TextOut(hdc, 0, 20, buffer, strlen(buffer));
				} break;

			case TIMER_ID3_SEC:
				{
					SetTextColor(hdc, RGB(0, 0, 255));
					sprintf(buffer, "The 10 second timer has fired %d times", ++counter3);
					TextOut(hdc, 0, 40, buffer, strlen(buffer));
				}

			default:
				break;
			}

			ReleaseDC(hWnd, hdc);
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
