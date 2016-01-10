#include <windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>

// 事件句柄回调函数
HDC hdc;

// 存放渲染环境的句柄
HGLRC hrc;

void setupPixelFormat(HDC hdc)
{
	// 用来存放像素格式的索引数值
	// 用来记录我们描述的当前的像素点是否可以被当前设备所接收
	// 如果可以通过，它返回给我们一个数值，来确定我们的像素描述的格式
	int pixelFormat;

	// PIXELFORMATDESCRIPTOR 用来描述像素结构体的变量
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// 描述结构的大小
		1,									// 版本号

		PFD_DRAW_TO_WINDOW	|
		PFD_SUPPORT_OPENGL	|
		PFD_DOUBLEBUFFER,					// 描述像素缓冲区属性标志：
											//		PFD_DRAW_TO_WINDOW			缓冲区可以绘制到一个窗口或者设备表面
											//		PFD_SUPPORT_OPENGL			缓冲区支持OpenGL绘制
											//		PFD_DOUBLEBUFFER			支持双缓冲，与PFD_SUPPORT_GDI互斥
											//		PFD_DEPTH_DONTCARE			被请求的像素格式，可以带也可以不带深度缓冲区，不指定的话仅带深度缓冲区的像素格式被考虑
											//		PFD_DOUBLEBUFFER_DONTCARE	像素格式可以是单一的也可以是双缓冲区的
											//		PFD_GENERIC_ACCELERATED		像素格式被设备驱动器所加速
											//		PFD_GENERIC_FORMAT			像素格式仅在软件中被支持

		PFD_TYPE_RGBA,						// 描述像素数据类型：
											//		PFD_TYPE_RGBA				红、绿、蓝、透明
											//		PFD_TYPE_COLORINDEX			调色板模式

		32,									// 每个像素的字节位数，就是我们看到图片颜色的位
		0, 0, 0, 0, 0, 0, 0, 0,				// 红色字节位数、移位计数，绿色...，蓝色...，alpha通道...
		0,									// 累加缓冲区字节位数
		0, 0, 0, 0,							// 红、绿、蓝、alpha累加字节位数
		32, 0, 0,							// 深度、特征、辅助缓冲区字节位数

		PFD_MAIN_PLANE,						// 绘图图层类型：
											//		PFD_MAIN_PLANE				设为主图层
											//		PFD_OVERLAY_PLANE			设为上层
											//		PFD_UNDERLAY_PLANE			设为底层

		0,									// 所支持的上层或下层平面的数量
		0, 0, 0								// 不再使用
	};

	// 检测我们的像素点数据结构，找到与之最匹配的像素格式
	pixelFormat = ChoosePixelFormat(hdc, &pfd);

	// 设定像素格式
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

			// 创建渲染的环境
			// wglCreateContext 创建一个新的OpenGL渲染描述表
			// 此描述表必须适用于绘制到hdc返回的设备
			// 此描述表将有和设备上下文（dc）一样的像素格式
			// 如果编译报错加载 glaux.lib glu32.lib OpenGL32.lib
			hrc = wglCreateContext(hdc);


			// 设定当前设备的环境以及渲染环境
			// wglMakeCurrent 设定OpenGL当前线程的渲染环境
			// 以后这个线程所有的OpenGL调用都是在这个hdc标识的设备上绘制
			// 你也可以使用 wglMakeCurrent 来改变调用线程的当前渲染环境，使之不再是当前的渲染环境
			
			// hdc：设备环境的句柄，调用这个函数的线程接下来的所有OpenGL调用倒在这个hdc所标识的设备上绘制
			// hrc：函数设定的OpenGL渲染环境的句柄，作为当前线程的渲染环境
			//		如果hrc为NULL，函数将使调用线程的当前渲染环境不再作为当前的渲染环境，并释放这个渲染环境所使用的设备环境。此时hdc参数将被忽略
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

// 程序入口
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
		// 检测消息
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				break;
			}

			// 消息转换
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (msg.wParam);
}
