#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include "CGfxOpenGL.h"


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK    WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL                SetupPixelFormat(HDC hdc);


char *className     = "GLClass";
long windowWidth    = 800;
long windowHeight   = 600;
long windowBits		= 32;
bool exiting        = false;
bool fullScreen		= false;

HDC         main_hdc;
HGLRC       main_hrc;
CGfxOpenGL  *g_glRender = NULL;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	g_glRender = new CGfxOpenGL();
	g_glRender->Init();

    MSG     msg;
    DWORD   dwExStyle;
    DWORD   dwStyle;

    if ( !MyRegisterClass(hInstance) )
    {
        return FALSE;
    }

    if ( !InitInstance(hInstance, nShowCmd) )
    {
        return FALSE;
    }

    while ( !exiting )
    {
		g_glRender->Prepare(0.0f);
		g_glRender->Render();
		SwapBuffers(main_hdc);

		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
			if ( !GetMessage(&msg, NULL, 0, 0) )
            {
                exiting = true;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	delete g_glRender;

	if ( fullScreen )
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wndClass;

    wndClass.cbSize         = sizeof(WNDCLASSEX);
    wndClass.style          = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = WndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = className;
    wndClass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	DWORD	dwExStyle;
	DWORD	dwStyle;

	RECT windowRect;
	windowRect.left = 0;
	windowRect.right = windowRect.left + windowWidth;
	windowRect.top = 0;
	windowRect.bottom = windowRect.top + windowHeight;

	if ( fullScreen )
	{
		DEVMODE dmScreenSetting;
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);
		dmScreenSetting.dmPelsWidth = windowWidth;
		dmScreenSetting.dmPelsHeight = windowHeight;
		dmScreenSetting.dmBitsPerPel = windowBits;
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if ( ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL )
		{
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			fullScreen = false;
		}
	}

	if ( fullScreen )
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

    HWND hWnd = CreateWindowEx(NULL,
                               className,
							   "BOGLGP - Chapter 2 - OpenGL Application",
                               dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                               0, 0, windowWidth, windowHeight,
                               NULL,
                               NULL,
                               hInstance,
                               NULL);

    if ( !hWnd )
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch ( message )
    {
        case WM_CREATE:
        {
            main_hdc = GetDC(hWnd);
            SetupPixelFormat(main_hdc);
            main_hrc = wglCreateContext(main_hdc);
            wglMakeCurrent(main_hdc, main_hrc);

            return 0;
        } break;

        case WM_SIZE:
        {
            windowHeight = HIWORD(lParam);
            windowWidth = LOWORD(lParam);

            g_glRender->SetupProjection(windowWidth, windowHeight);

            return 0;
        } break;

        case WM_KEYDOWN:
        {
            int fwKeys;
            LPARAM keyData;
            fwKeys = (int)wParam;
            keyData = lParam;

            switch ( fwKeys )
            {
                case VK_ESCAPE:
                {
                    PostQuitMessage(0);
                } break;

                default:
                    break;
            }

            return 0;
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);

            return 0;
        } break;

        case WM_TIMER:
        {
            return 0;
        } break;

        case WM_CLOSE:
        {
            wglMakeCurrent(main_hdc, NULL);
            wglDeleteContext(main_hrc);
            PostQuitMessage(0);

            return 0;
        } break;

        default:
            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
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

    int pixelformat = ChoosePixelFormat(hdc, &pfd);
    return SetPixelFormat(hdc, pixelformat, &pfd);
}
