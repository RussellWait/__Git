#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include "resource.h"


#define WND_CLASS_NAME	"WNDCLASS1"

HINSTANCE	hInstance_app		= NULL;
HWND		main_window_handle	= NULL;


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
	hInstance_app = hInstance;

	WNDCLASSEX wndClass;

	wndClass.cbSize			= sizeof(WNDCLASSEX);
	wndClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_T3DX));
	wndClass.hCursor		= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR_BLUE));
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU_MAINMENU);
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_T3DX));

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	main_window_handle = CreateWindowEx(	NULL,
											WND_CLASS_NAME,
											"Menu Resource Demo with Processing",
											WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDR_MENU_FILE_ID_EXIT:
				{
					PostQuitMessage(0);
				} break;

			case IDR_MENU_PLAY_ID_BEAM:
				{
					PlaySound(MAKEINTRESOURCE(IDR_SOUND_BEAM), hInstance_app, SND_RESOURCE | SND_ASYNC);
				} break;

			case IDR_MENU_PLAY_ID_CREATE:
				{
					PlaySound(MAKEINTRESOURCE(IDR_SOUND_CREATE), hInstance_app, SND_RESOURCE | SND_ASYNC);
				} break;

			case IDR_MENU_PLAY_ID_TECHNO:
				{
					PlaySound(MAKEINTRESOURCE(IDR_SOUND_TECHNO), hInstance_app, SND_RESOURCE | SND_ASYNC);
				} break;

			case IDR_MENU_PLAY_ID_TELEPORT:
				{
					PlaySound(MAKEINTRESOURCE(IDR_SOUND_TELEPORT), hInstance_app, SND_RESOURCE | SND_ASYNC);
				} break;

			case IDR_MENU_PLAY_ID_WARP:
				{
					PlaySound(MAKEINTRESOURCE(IDR_SOUND_WARP), hInstance_app, SND_RESOURCE | SND_ASYNC);
				} break;

			case IDR_MENU_HELP_ID_ABOUT:
				{
					MessageBox(hWnd, "Menu Sound Demo", "About Sound Menu", MB_OK | MB_ICONEXCLAMATION);
				} break;

			default:
				break;
			}
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
