#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>


#define WND_CLASS_NAME		"WNDCLASS1"
#define WND_WIDTH			640
#define WND_HEIGHT			480


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

		HDC hdc = GetDC(main_window_handle);

		HPEN hPen = CreatePen(	PS_SOLID,									// 画笔类型
																			//		PS_SOLID		实心画笔
																			//		PS_DASH			虚线画笔
																			//		PS_DOT			点画笔
																			//		PS_DASHDOT		点画线画笔
																			//		PS_DASHDOTDOT	双点画线画笔
								1,											// 线宽
								RGB(rand()%255, rand()%255, rand()%255));	// 颜色
		HPEN old_hPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, rand()%WND_WIDTH, rand()%WND_HEIGHT, NULL);			// 最后一参数用于保存最后一个位置
		LineTo(hdc, rand()%WND_WIDTH, rand()%WND_HEIGHT);
		SelectObject(hdc, old_hPen);
		DeleteObject(hPen);

		ReleaseDC(main_window_handle, hdc);
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
											"Line Drawing Demo",
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
