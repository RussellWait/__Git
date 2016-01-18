#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>


#define WND_CLASS_NAME		"WNDCLASS1"


HWND hWnd;


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

		HDC hdc = GetDC(hWnd);

		HBRUSH hBrush = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
		RECT rect = {rand()%640, rand()%480, rand()%640, rand()%480};

		int r = rand()%4;
		if (0 == r)
		{
			// ѡ��ˢ�����Σ��߿��û��ʻ��ƣ�
			HBRUSH old_hBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			SelectObject(hdc, old_hBrush);
		}
		else if (1 == r)
		{
			// ��ѡ��ˢ�򲻻����
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		}
		else if (2 == r)
		{
			// ֱ��ʹ�û�ˢ���
			FillRect(hdc, &rect, hBrush);
		}
		else if (3 == r)
		{
			// ֱ��ʹ�û�ˢ���߿�
			FrameRect(hdc, &rect, hBrush);
		}
		DeleteObject(hBrush);

		ReleaseDC(hWnd, hdc);
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
	wndClass.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= WND_CLASS_NAME;
	wndClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wndClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nShowCmd)
{
	hWnd = CreateWindowEx(	NULL,
							WND_CLASS_NAME,
							"Pixel Plotting Demo",
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
	HDC			hdc;
	PAINTSTRUCT	ps;

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
