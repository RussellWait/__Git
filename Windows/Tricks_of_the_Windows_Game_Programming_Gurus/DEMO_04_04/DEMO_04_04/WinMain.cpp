#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>


#define WND_CLASS_NAME		"WNDCLASS1"
#define WND_WIDTH			640
#define WND_HEIGHT			480

#define BALL_RADIUS			50


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

	int ball_x = WND_WIDTH/2;
	int ball_y = WND_HEIGHT/2;
	int v_x = rand()%10 - 5;
	int v_y = rand()%10 - 5;

	HDC hdc = GetDC(main_window_handle);
	HPEN white_hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN black_hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH black_hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH green_hBrush = CreateSolidBrush(RGB(0, 255, 0));

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

		SelectObject(hdc, black_hPen);
		SelectObject(hdc, black_hBrush);
		Ellipse(hdc, ball_x - BALL_RADIUS, ball_y - BALL_RADIUS, ball_x + BALL_RADIUS, ball_y + BALL_RADIUS);

		ball_x += v_x;
		ball_y += v_y;
		if (ball_x <= BALL_RADIUS || ball_x >= WND_WIDTH - BALL_RADIUS)
		{
			v_x = -v_x;
		}
		if (ball_y <= BALL_RADIUS || ball_y >= WND_HEIGHT - BALL_RADIUS)
		{
			v_y = -v_y;
		}

		SelectObject(hdc, white_hPen);
		SelectObject(hdc, green_hBrush);
		Ellipse(hdc, ball_x - BALL_RADIUS, ball_y - BALL_RADIUS, ball_x + BALL_RADIUS, ball_y + BALL_RADIUS);

		Sleep(10);
	}

	DeleteObject(white_hPen);
	DeleteObject(black_hPen);
	DeleteObject(black_hBrush);
	DeleteObject(green_hBrush);
	ReleaseDC(main_window_handle, hdc);

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
											"Ellipse Animation Demo",
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
