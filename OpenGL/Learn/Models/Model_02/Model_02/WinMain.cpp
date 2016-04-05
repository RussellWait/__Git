#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>

#include "3D_Function.h"
#include "MD3.h"


#define WND_CLASS_NAME	"Test"
#define WND_WIDTH		800
#define WND_HEIGHT		600


HDC		main_hdc;
HGLRC	main_hrc;


CMD3    g_MD3_1;
CMD3    g_MD3_2;
CMD3    g_MD3_3;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL				SetupPixelFormat(HDC hdc);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	MSG msg;

	if ( !MyRegisterClass(hInstance) )
	{
		return FALSE;
	}

	if ( !InitInstance(hInstance, nShowCmd) )
	{
		return FALSE;
	}

	while ( TRUE )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			if ( WM_QUIT == msg.message )
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

	return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	HWND hwnd = CreateWindowEx(NULL,
							   WND_CLASS_NAME,
							   NULL,
							   WS_OVERLAPPEDWINDOW,
							   0, 0, WND_WIDTH, WND_HEIGHT,
							   NULL,
							   NULL,
							   hInstance,
							   NULL);

	if ( !hwnd )
	{
		return FALSE;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
        case WM_CREATE:
        {
            main_hdc = GetDC(hwnd);
            SetupPixelFormat(main_hdc);

            main_hrc = wglCreateContext(main_hdc);
            wglMakeCurrent(main_hdc, main_hrc);

            InitOpenGL();
            SetupMatrices(WND_WIDTH, WND_HEIGHT);

            g_MD3_1.Load("Models\\players\\doom\\lower.md3");
            g_MD3_2.Load("Models\\players\\doom\\upper.md3");
            g_MD3_3.Load("Models\\players\\doom\\head.md3");

            SetTimer(hwnd, 1, 1, NULL);

            return 0;
        } break;

        case WM_TIMER:
        {
            Render();
            SwapBuffers(main_hdc);

            return 0;
        } break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return 0;
        } break;

		default:
		break;
	}

    return DefWindowProc(hwnd, message, wParam, lParam);
}

BOOL SetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1.0f,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        32, 0, 0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    return SetPixelFormat(hdc, pixelFormat, &pfd);
}
