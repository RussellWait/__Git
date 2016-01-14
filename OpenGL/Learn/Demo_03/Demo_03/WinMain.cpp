#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>

#include "3D_Function.h"


#define WND_CLASS_NAME		"Test"


HDC		hdc;
HGLRC	hrc;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void				setupPixelFormat(HDC hdc);


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
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return (RegisterClassEx(&wndClass));
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	HWND hWnd;

	hWnd = CreateWindowEx(	NULL,
							WND_CLASS_NAME,
							NULL,
							WS_OVERLAPPEDWINDOW,
							0, 0, 640, 480,
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
	switch (msg)
	{
	case WM_CREATE:
		{
			hdc = GetDC(hWnd);

			setupPixelFormat(hdc);
			hrc = wglCreateContext(hdc);
			wglMakeCurrent(hdc, hrc);

			SetupMatrices(640, 480);

			InitOpenGL();
			SetTimer(hWnd, 1, 200, NULL);

			return (0);
		} break;

	case WM_TIMER:
		{
			Render();

			// ½»»»»º³åÇø
			SwapBuffers(hdc);
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

void setupPixelFormat(HDC hdc)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0,
		0, 0, 0, 0,
		32, 0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
}
