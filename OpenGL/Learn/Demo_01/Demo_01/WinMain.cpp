#include <windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>

// �¼�����ص�����
HDC hdc;

// �����Ⱦ�����ľ��
HGLRC hrc;

void setupPixelFormat(HDC hdc)
{
	// ����������ظ�ʽ��������ֵ
	// ������¼���������ĵ�ǰ�����ص��Ƿ���Ա���ǰ�豸������
	// �������ͨ���������ظ�����һ����ֵ����ȷ�����ǵ����������ĸ�ʽ
	int pixelFormat;

	// PIXELFORMATDESCRIPTOR �����������ؽṹ��ı���
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// �����ṹ�Ĵ�С
		1,									// �汾��

		PFD_DRAW_TO_WINDOW	|
		PFD_SUPPORT_OPENGL	|
		PFD_DOUBLEBUFFER,					// �������ػ��������Ա�־��
											//		PFD_DRAW_TO_WINDOW			���������Ի��Ƶ�һ�����ڻ����豸����
											//		PFD_SUPPORT_OPENGL			������֧��OpenGL����
											//		PFD_DOUBLEBUFFER			֧��˫���壬��PFD_SUPPORT_GDI����
											//		PFD_DEPTH_DONTCARE			����������ظ�ʽ�����Դ�Ҳ���Բ�����Ȼ���������ָ���Ļ�������Ȼ����������ظ�ʽ������
											//		PFD_DOUBLEBUFFER_DONTCARE	���ظ�ʽ�����ǵ�һ��Ҳ������˫��������
											//		PFD_GENERIC_ACCELERATED		���ظ�ʽ���豸������������
											//		PFD_GENERIC_FORMAT			���ظ�ʽ��������б�֧��

		PFD_TYPE_RGBA,						// ���������������ͣ�
											//		PFD_TYPE_RGBA				�졢�̡�����͸��
											//		PFD_TYPE_COLORINDEX			��ɫ��ģʽ

		32,									// ÿ�����ص��ֽ�λ�����������ǿ���ͼƬ��ɫ��λ
		0, 0, 0, 0, 0, 0, 0, 0,				// ��ɫ�ֽ�λ������λ��������ɫ...����ɫ...��alphaͨ��...
		0,									// �ۼӻ������ֽ�λ��
		0, 0, 0, 0,							// �졢�̡�����alpha�ۼ��ֽ�λ��
		32, 0, 0,							// ��ȡ������������������ֽ�λ��

		PFD_MAIN_PLANE,						// ��ͼͼ�����ͣ�
											//		PFD_MAIN_PLANE				��Ϊ��ͼ��
											//		PFD_OVERLAY_PLANE			��Ϊ�ϲ�
											//		PFD_UNDERLAY_PLANE			��Ϊ�ײ�

		0,									// ��֧�ֵ��ϲ���²�ƽ�������
		0, 0, 0								// ����ʹ��
	};

	// ������ǵ����ص����ݽṹ���ҵ���֮��ƥ������ظ�ʽ
	pixelFormat = ChoosePixelFormat(hdc, &pfd);

	// �趨���ظ�ʽ
	SetPixelFormat(hdc, pixelFormat, &pfd);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
			hdc = GetDC(hwnd);

			setupPixelFormat(hdc);

			// ������Ⱦ�Ļ���
			// wglCreateContext ����һ���µ�OpenGL��Ⱦ������
			// ����������������ڻ��Ƶ�hdc���ص��豸
			// ���������к��豸�����ģ�dc��һ�������ظ�ʽ
			// ������뱨����� glaux.lib glu32.lib OpenGL32.lib
			hrc = wglCreateContext(hdc);


			// �趨��ǰ�豸�Ļ����Լ���Ⱦ����
			// wglMakeCurrent �趨OpenGL��ǰ�̵߳���Ⱦ����
			// �Ժ�����߳����е�OpenGL���ö��������hdc��ʶ���豸�ϻ���
			// ��Ҳ����ʹ�� wglMakeCurrent ���ı�����̵߳ĵ�ǰ��Ⱦ������ʹ֮�����ǵ�ǰ����Ⱦ����
			
			// hdc���豸�����ľ������������������߳̽�����������OpenGL���õ������hdc����ʶ���豸�ϻ���
			// hrc�������趨��OpenGL��Ⱦ�����ľ������Ϊ��ǰ�̵߳���Ⱦ����
			//		���hrcΪNULL��������ʹ�����̵߳ĵ�ǰ��Ⱦ����������Ϊ��ǰ����Ⱦ���������ͷ������Ⱦ������ʹ�õ��豸��������ʱhdc������������
			wglMakeCurrent(hdc, hrc);

			return (0);
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return(0);
		}
	}

	return(DefWindowProc(hwnd, msg, wParam, lParam));
}

// �������
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	WNDCLASSEX winClass;

	winClass.cbSize				= sizeof(WNDCLASSEX);
	winClass.style				= NULL;
	winClass.lpfnWndProc		= WindowProc;
	winClass.cbClsExtra			= 0;
	winClass.cbWndExtra			= 0;
	winClass.hInstance			= hinstance;
	winClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName		= "Test";
	winClass.lpszClassName		= "Test";
	winClass.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winClass))
	{
		return (0);
	}

	if (!(hWnd = CreateWindowEx(NULL, "Test", NULL, WS_OVERLAPPEDWINDOW, 0, 0, 640, 480,
								NULL, NULL, hinstance, NULL)))
	{
		return (0);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (TRUE)
	{
		// �����Ϣ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				break;
			}

			// ��Ϣת��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (msg.wParam);
}
