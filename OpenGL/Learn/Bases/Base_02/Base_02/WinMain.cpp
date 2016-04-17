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


char *className     = "Test";
long windowWidth    = 800;
long windowHeight   = 600;
bool exiting        = false;

HDC         main_hdc;
HGLRC       main_hrc;
CGfxOpenGL  *g_glRender = NULL;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    MSG     msg;
    DWORD   dwExStyle;
    DWORD   dwStyle;
    RECT    windowRect;

    g_glRender = new CGfxOpenGL;
    windowRect.left = 0;
    windowRect.right = windowWidth;
    windowRect.top = 0;
    windowRect.bottom = windowHeight;

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
        if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
        {
            if ( WM_QUIT == msg.message )
            {
                exiting = true;
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
    HWND hWnd = CreateWindowEx(NULL,
                               className,
                               NULL,
                               WS_OVERLAPPEDWINDOW,
                               0, 0, windowWidth, windowHeight,
                               NULL,
                               NULL,
                               hInstance,
                               NULL);

    if ( !hWnd )
    {
        return FALSE;
    }

    ShowWindow(hWnd, nShowCmd);
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
