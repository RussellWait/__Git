#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>


#define WND_CLASS_NAME		"WNDCLASS1"

#define KEYDOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, UINT nShowCmd);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


HWND	main_window_handle	= NULL;


int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	HDC		hdc;
	MSG		msg;
	char	buffer[80];

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

		hdc = GetDC(main_window_handle);

		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, OPAQUE);

		sprintf(buffer, "(2)  Up Arrow = %d", KEYDOWN(VK_UP));
		TextOut(hdc, 0, 100, buffer, strlen(buffer));

		sprintf(buffer, "(2)  Down Arrow = %d", KEYDOWN(VK_DOWN));
		TextOut(hdc, 0, 116, buffer, strlen(buffer));

		sprintf(buffer, "(2)  Left Arrow = %d", KEYDOWN(VK_LEFT));
		TextOut(hdc, 0, 132, buffer, strlen(buffer));

		sprintf(buffer, "(2)  Right Arrow = %d", KEYDOWN(VK_RIGHT));
		TextOut(hdc, 0, 148, buffer, strlen(buffer));

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
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, UINT nShowCmd)
{
	main_window_handle = CreateWindowEx(	NULL,
											WND_CLASS_NAME,
											"WM_CHAR Demo",
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

	char buffer[80];
	int yPos;

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

	case WM_KEYDOWN:
		{
			int virtual_code = (int)wParam;
			int key_state = (int)lParam;

			hdc = GetDC(hWnd);

			SetTextColor(hdc, RGB(255, 0, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, OPAQUE);

			switch (virtual_code)
			{
			case VK_UP:
				{
					sprintf(buffer, "(1)  Up Arrow = 1");
					yPos = 0;
				} break;

			case VK_DOWN:
				{
					sprintf(buffer, "(1)  Down Arrow = 1");
					yPos = 16;
				} break;

			case VK_LEFT:
				{
					sprintf(buffer, "(1)  Left Arrow = 1");
					yPos = 32;
				} break;

			case VK_RIGHT:
				{
					sprintf(buffer, "(1)  Right Arrow = 1");
					yPos = 48;
				} break;

			default:
				break;
			}

			TextOut(hdc, 0, yPos, buffer, strlen(buffer));

			ReleaseDC(hWnd, hdc);
		} break;

	case WM_KEYUP:
		{
			int virtual_code = (int)wParam;
			int key_state = (int)lParam;

			hdc = GetDC(hWnd);

			SetTextColor(hdc, RGB(0, 255, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, OPAQUE);

			switch (virtual_code)
			{
			case VK_UP:
				{
					sprintf(buffer, "(1)  Up Arrow = 0");
					yPos = 0;
				} break;

			case VK_DOWN:
				{
					sprintf(buffer, "(1)  Down Arrow = 0");
					yPos = 16;
				} break;

			case VK_LEFT:
				{
					sprintf(buffer, "(1)  Left Arrow = 0");
					yPos = 32;
				} break;

			case VK_RIGHT:
				{
					sprintf(buffer, "(1)  Right Arrow = 0");
					yPos = 48;
				} break;

			default:
				break;
			}

			TextOut(hdc, 0, yPos, buffer, strlen(buffer));

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
