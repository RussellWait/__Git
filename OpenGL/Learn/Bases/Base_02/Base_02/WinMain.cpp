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
long windowBits		= 32;           // 
bool exiting        = false;        // 标记是否退出主循环
bool fullScreen		= false;        // 全屏标记

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

    // 注册类
    if ( !MyRegisterClass(hInstance) )
    {
        return FALSE;
    }

    // 创建并显示窗口
    if ( !InitInstance(hInstance, nShowCmd) )
    {
        return FALSE;
    }

    while ( !exiting )
    {
		g_glRender->Prepare(0.0f);      // 调用绘制前准备函数
		g_glRender->Render();           // 绘内容型到窗口
		SwapBuffers(main_hdc);          // 将后帧缓存内容绘到屏幕上

        // 检查线程消息队列（检查的消息不移除）
        if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) )
        {
            // 从系统获取消息，并将消息从系统移除
			if ( !GetMessage(&msg, NULL, 0, 0) )
            {
                exiting = true;
                break;
            }

            // windows消息处理函数
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // 删除opengl绘图实例
	delete g_glRender;

	if ( fullScreen )
    {
        // 释放设备
		ChangeDisplaySettings(NULL, 0);

        // 显示光标
		ShowCursor(TRUE);
	}

    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wndClass;

    wndClass.cbSize         = sizeof(WNDCLASSEX);                   // 结构体大小
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;              // 窗口拥有特性
    wndClass.lpfnWndProc    = WndProc;                              // 窗口回调函数
    wndClass.cbClsExtra     = 0;                                    // 额外特性，下同
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;                            // 应用程序句柄
    wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);      // 大图标
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);          // 光标
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);  // 背景色
    wndClass.lpszMenuName   = NULL;                                 // 菜单资源名字
    wndClass.lpszClassName  = className;                            // 为此窗口类型命名
    wndClass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);      // 小图标
    
    // 注册窗口类
    return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	DWORD	dwExStyle;
	DWORD	dwStyle;

    // 窗口区域
	RECT windowRect;
	windowRect.left = 0;
	windowRect.right = windowRect.left + windowWidth;
	windowRect.top = 0;
	windowRect.bottom = windowRect.top + windowHeight;

	if ( fullScreen )
	{
        // 配置窗口分辩率
		DEVMODE dmScreenSetting;
		memset(&dmScreenSetting, 0, sizeof(dmScreenSetting));
		dmScreenSetting.dmSize = sizeof(dmScreenSetting);       // 参数结构体大小
		dmScreenSetting.dmPelsWidth = windowWidth;              // 水平方向上像素数量
		dmScreenSetting.dmPelsHeight = windowHeight;            // 竖直方向行像素数量
		dmScreenSetting.dmBitsPerPel = windowBits;              // 像素所占字节
		dmScreenSetting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // 检测是否配置窗口为指定大小
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

    // 根据设备计算出需要的窗口大小
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
