#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include "CGfxOpenGL.h"


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK    WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL                SetupPixelFormat(HDC hdc);


char    *className      = "GLClass";
long    windowWidth     = 800;
long    windowHeight    = 600;
long    windowBits      = 32;
bool    exiting         = false;
bool    fullScreen      = false;

HDC     main_hdc;
HGLRC   main_hrc;


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

    while ( !exiting )
    {


        if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) )
        {
            while ( !GetMessage(&msg, NULL, 0, 0) )
            {
                exiting = true;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
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
long windowBits		= 32;           // ���������ֶεĴ�С
bool exiting        = false;		// ����Ƿ��˳���ѭ��
bool fullScreen		= false;		// �Ƿ����ȫ��ģʽ

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

    // ע����
    if ( !MyRegisterClass(hInstance) )
    {
        return FALSE;
    }

    // ��������ʾ����
    if ( !InitInstance(hInstance, nShowCmd) )
    {
        return FALSE;
    }

    while ( !exiting )
    {
        g_glRender->Prepare(0.0f);      // ���û���ǰ׼������
        g_glRender->Render();           // �������͵�����
        SwapBuffers(main_hdc);          // ����֡�������ݻ浽��Ļ��

        // ����߳���Ϣ���У�������Ϣ���Ƴ���
        if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) )
        {
            // ��ϵͳ��ȡ��Ϣ��������Ϣ��ϵͳ�Ƴ�
            while ( !GetMessage(&msg, NULL, 0, 0) )
            {
                exiting = true;
                break;
            }

            // windows��Ϣ������
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // ɾ��opengl��ͼʵ��
    delete g_glRender;

    // ȫ��ģʽ�£��ͷŴ����豸
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

    wndClass.cbSize         = sizeof(WNDCLASSEX);                   // �ṹ���С
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;              // ����ӵ������
    wndClass.lpfnWndProc    = WndProc;                              // ���ڻص�����
    wndClass.cbClsExtra     = 0;                                    // �������ԣ���ͬ
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;                            // Ӧ�ó�����
    wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);      // ��ͼ��
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);          // ���
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);  // ����ɫ
    wndClass.lpszMenuName   = NULL;                                 // �˵���Դ����
    wndClass.lpszClassName  = className;                            // Ϊ�˴�����������
    wndClass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);      // Сͼ��

    // ע�ᴰ����
    return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
    DWORD	dwExStyle;
    DWORD	dwStyle;

    // ��������
    RECT windowRect;
    windowRect.left = 0;
    windowRect.right = windowRect.left + windowWidth;
    windowRect.top = 0;
    windowRect.bottom = windowRect.top + windowHeight;

    if ( fullScreen )
    {
        // ���ô��ڷֱ���
        DEVMODE dmScreenSetting;
        memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
        dmScreenSetting.dmSize = sizeof(dmScreenSetting);       // �����ṹ���С
        dmScreenSetting.dmPelsWidth = windowWidth;              // ˮƽ��������������
        dmScreenSetting.dmPelsHeight = windowHeight;            // ��ֱ��������������
        dmScreenSetting.dmBitsPerPel = windowBits;              // ������ռ�ֽ�
        dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // ����Ƿ����ô���Ϊָ����С
        if ( ChangeDisplaySettings(&dmScreenSetting, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL )
        {
            MessageBox(NULL, "Display mode failed", NULL, MB_OK);
            fullScreen = false;
        }
    }

    // ָ��ȫ���ͷ�ȫ��ʱ���ڷ��
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

    // �����豸�������Ҫ�Ĵ��ڴ�С
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

    ShowWindow(hWnd, SW_SHOW);	// ��ʾ����
    UpdateWindow(hWnd);			// ���´���

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch ( message )
    {
        // ��������ʱ
        case WM_CREATE:
        {
            main_hdc = GetDC(hWnd);						// ��ȡ���������ľ��
            SetupPixelFormat(main_hdc);					// ���ô˴��ڵ���ɫ��ʽ
            main_hrc = wglCreateContext(main_hdc);		// ����һ���µ�OpenGL��Ⱦ������ӵ���豸����һ�������ظ�ʽ��
            wglMakeCurrent(main_hdc, main_hrc);			// �趨OpenGL��ǰ����Ⱦ����

            return 0;
        } break;

        // ���ڳߴ�ı�ʱ
        case WM_SIZE:
        {
            windowHeight = HIWORD(lParam);				// ��ȡ�ı��Ĵ��ڿ��
            windowWidth = LOWORD(lParam);

            g_glRender->SetupProjection(windowWidth, windowHeight);

            return 0;
        } break;

        // �����¼�
        case WM_KEYDOWN:
        {
            int fwKeys;
            LPARAM keyData;
            fwKeys = (int)wParam;
            keyData = lParam;

            switch ( fwKeys )
            {
                // ��ESC�˳�
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

        // ���ڹر�ʱ
        case WM_CLOSE:
        {
            wglMakeCurrent(main_hdc, NULL);		// �ͷŵ�ǰ������Ⱦ����
            wglDeleteContext(main_hrc);			// �����ǰ���������Ļ���
            PostQuitMessage(0);					// �����˳���Ϣ

            return 0;
        } break;

        default:
            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// �������ظ�ʽ
BOOL SetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),								// �˽ṹ���С
        1.0f,														// �汾��
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,	// ���Ʒ�ʽ
        PFD_TYPE_RGBA,												// ��ɫ��ʽ
        32,															// ʹ��32λ��ɫ
        0, 0, 0, 0, 0, 0, 0, 0,										// ��ɫ��λ����λ����
        0, 0, 0, 0, 0,
        32,															// ��Ȼ������ֽ���
        0,
        0,
        PFD_MAIN_PLANE,												// ����ͼ�ε����ԣ�����Ϊ����ͼ��
        0,
        0, 0, 0
    };

    // �����������ƥ������ظ�ʽ
    int pixelformat = ChoosePixelFormat(hdc, &pfd);

    // �������ظ�ʽ
    return SetPixelFormat(hdc, pixelformat, &pfd);
}
