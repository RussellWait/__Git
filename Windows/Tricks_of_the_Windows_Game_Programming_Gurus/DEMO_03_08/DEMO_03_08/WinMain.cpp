#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#define WND_CLASS_NAME		"WNDCLASS1"


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
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, UINT nShowCmd)
{
	HWND hWnd;
	hWnd = CreateWindowEx(	NULL,
							WND_CLASS_NAME,
							"WM_CLOSE Demo with Verify",
							WS_OVERLAPPEDWINDOW,
							0, 0, 400, 300,
							NULL,
							NULL,
							hInstance,
							NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;
	HDC				hdc;
	RECT			rect;

	char buffer[80];
	static int activeCount = 0;

	switch (msg)
	{
	case WM_CREATE:
		{
			return (0);
		} break;

	case WM_PAINT:
		{
			//hdc = BeginPaint(hWnd, &ps);
			//EndPaint(hWnd, &ps);

			hdc = GetDC(hWnd);
			ReleaseDC(hWnd, hdc);

			GetClientRect(hWnd, &rect);
			ValidateRect(hWnd, &rect);

			return (0);
		} break;

	case WM_ACTIVATE:
		{
			hdc = GetDC(hWnd);

			SetBkColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, OPAQUE);

			if (WA_INACTIVE == LOWORD(wParam))
			{
				SetTextColor(hdc, RGB(255, 0, 0));
				sprintf(buffer, "WA_INACTIVE %d  ", ++activeCount);
			}
			else
			{
				SetTextColor(hdc, RGB(0, 255, 0));
				sprintf(buffer, "WA_ACTIVE %d    ", ++activeCount);
			}

			TextOut(hdc, 0, 0, buffer, strlen(buffer));

			ReleaseDC(hWnd, hdc);

			return 0;
		} break;

	case WM_CLOSE:
		{
			int result = MessageBox(hWnd,
									"Are you sure you want to close this application?",
									"WM_CLOSE Message Processor",
									MB_YESNO | MB_ICONQUESTION);
			if (IDYES == result)
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			else
			{
				return (0);
			}

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
