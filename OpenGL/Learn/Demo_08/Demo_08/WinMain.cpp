#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>


#define WND_CLASS_NAME		"Test"
#define WND_WIDTH			640
#define WND_HEIGHT			480


HDC		main_hdc;
HGLRC	main_hrc;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void				SetupPixelFormat(HWND hWnd);


int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
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

}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

}

void SetupPixelFormat(HWND hWnd)
{

}
