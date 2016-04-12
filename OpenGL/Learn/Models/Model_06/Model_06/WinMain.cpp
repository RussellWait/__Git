#define WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>

#include "3D_Function.h"
#include "MD5.h"


#define WND_CLASS_NAME	"Test"
#define WND_WIDTH		800
#define WND_HEIGHT		600


HDC		main_hdc;
HGLRC	main_hrc;

MD5_Model_t *md5File    = NULL; // 指向读取MD5模型信息的存储空间
MD5_Anim_t  *md5Anim    = NULL;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nShowCmd);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
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
	HWND hWnd = CreateWindowEx(NULL,
							   WND_CLASS_NAME,
							   NULL,
							   WS_OVERLAPPEDWINDOW,
							   0, 0, WND_WIDTH, WND_HEIGHT,
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

            SetupPixelFormat(main_hdc);

            InitOpenGL();
            SetupMatrices(WND_WIDTH, WND_HEIGHT);

			md5File = (MD5_Model_t *)malloc(sizeof(MD5_Model_t));
			memset(md5File, 0, sizeof(MD5_Model_t));

			if ( !ReadModel("models/hellknight.md5mesh", md5File) )
			{
				exit(-1);
			}
			else
			{
				AllocVertexArrays();
			}

            md5Anim = (MD5_Anim_t *)malloc(sizeof(MD5_Anim_t));
            memset(md5Anim, 0, sizeof(MD5_Anim_t));

            if ( !ReadAnim("models/turret_attack.md5anim", md5Anim) )
            {
                if ( md5Anim )
                {
                    FreeAnim(md5Anim);
                    free(md5Anim);
                    md5Anim = NULL;
                }
            }

            SetTimer(hWnd, 1, 35, NULL);

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
			FreeModel(md5File);
			FreeVertexArrays();

			// 取消渲染环境
            if ( main_hdc )
            {
                wglMakeCurrent(main_hdc, NULL);
            }

			// 删除hrc指向的渲染
            if ( main_hrc )
            {
                wglDeleteContext(main_hrc);
            }

            if ( hWnd )
            {
                DestroyWindow(hWnd);
            }

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
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0,
		32, 0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	return SetPixelFormat(hdc, pixelFormat, &pfd);
}
