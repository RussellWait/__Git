#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>


#define WND_CLASS_NAME		"WNDCLASS1"

#define KEYDOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


HWND	main_window_handle	= NULL;

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

		if (KEYDOWN(VK_ESCAPE))
		{
			//SendMessage(main_window_handle, WM_CLOSE, 0, 0);
			PostMessage(main_window_handle, WM_CLOSE, 0, 0);
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
	wndClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor			= LoadCursor(NULL, IDC_CROSS);
	wndClass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName		= NULL;
	wndClass.lpszClassName		= WND_CLASS_NAME;
	wndClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	main_window_handle = CreateWindowEx(	NULL,
											WND_CLASS_NAME,
											"WM_DESTROY Message Sending Demo",
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
