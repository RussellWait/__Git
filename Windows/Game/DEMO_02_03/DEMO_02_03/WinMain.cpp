#define WIN32_LEAN_AND_MEAN		// just say no to MFC

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_CLASS_NAME		"WINCLASS1"


// 全局变量
HINSTANCE hInst;


// 函数声明
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	MSG msg;

	if (!MyRegisterClass(hInstance))
	{
		return FALSE;
	}

	// first window
	if (!InitInstance(hInstance, nShowCmd))
	{
		return FALSE;
	}

	// second window
	if (!InitInstance(hInstance, nShowCmd))
	{
		return FALSE;
	}

	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

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

		// game main
	}

	return (msg.wParam);
}

// 注册窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX winClass;

	winClass.cbSize				= sizeof(WNDCLASSEX);								// 结构体大小

	winClass.style				= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;	// 窗口样式信息标识：
																					//		CS_HREDRAW			移动或改变了窗口的宽度，则刷新整个窗口
																					//		CS_VREDRAW			移动或改变了窗口的高度，则刷新整个窗口
																					//		CS_OWNDC			为该类中每个窗口分配一个单值的设备描述表
																					//		CS_DBLCLKS			当用户双击鼠标时向窗口程序发送一个双击的信息
																					//							同时将光标位于属于该类的窗口中
																					//		CS_PARENTDC			在母窗口中设定一个子窗口的剪切区，以便子窗口能画在母窗口中
																					//		CS_SAVEBITS			在一个窗口中保存用户图像，以便于该窗口被遮住时不必每次刷新屏幕
																					//		CS_NOCLOSE			禁止菜单上的关闭按钮

	winClass.lpfnWndProc		= WndProc;											// 指向事件句柄的函数指针
	winClass.cbClsExtra			= 0;												// 保存附加的运行时信息
	winClass.cbWndExtra			= 0;												// 同上
	winClass.hInstance			= hInstance;										// 应用程序实例

	winClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);					// 程序图标句柄：
																					//		IDI_APPLICATION		默认应用程序图标
																					//		IDI_ASTREISX		星号
																					//		IDI_EXCLAMATION		感叹号
																					//		IDI_HAND			手形图标
																					//		IDI_QUESTION		问号
																					//		IDI_WINLOGO			Windows徽标

	winClass.hCursor			= LoadCursor(NULL, IDC_ARROW);						// 鼠标图标句柄：
																					//		IDC_ARROW			标准箭头
																					//		IDC_APPSTARTING		标准箭头和小沙漏
																					//		IDC_CROSS			横标线
																					//		IDC_IBEAM			文本I型标
																					//		IDC_NO				带正斜线的圆圈
																					//		IDC_SIZEALL			四向箭头
																					//		IDC_SIZENESW		指向东北-西南双向箭头
																					//		IDC_SIZENS			指向南-北双向箭头
																					//		IDC_SIZENWSE		指向东南-西北双向箭头
																					//		IDC_SIZEWE			指向东-西双向箭头
																					//		IDC_UPARROW			竖直方向箭头
																					//		IDC_WAIT			沙漏

	winClass.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);				// 背景色
																					//		GETStockObject		用于获得Windows系统画刷、画笔、调色板或字体的一个句柄
																					//			BLACK_BRUSH		黑色画刷
																					//			WHITE_BRUSH		白色画刷
																					//			GRAY_BRUSH		灰色画刷
																					//			LTGRAY_BRUSH	浅灰色画刷
																					//			DKGRAY_BRUSH	深灰色画刷
																					//			HOLLOW_BRUSH	空心画刷
																					//			NULL_BRUSH		空画刷
																					//			BLACK_PEN		黑色画笔
																					//			WHITE_PEN		白色画笔
																					//			NULL_PEN		空画笔
																					
	winClass.lpszMenuName		= "menu name";										// 菜单名称
	winClass.lpszClassName		= WINDOW_CLASS_NAME;								// 窗口类名称
	winClass.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);					// 小图标

	return (RegisterClassEx(&winClass));
}

// 实例化窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	// 该函数如果执行成功返回一个指向新窗口的句柄；否则返回NULL
	hWnd = CreateWindowEx(	NULL,							// 额外窗口类型
							WINDOW_CLASS_NAME,				// 所创建窗口类名
							NULL,							// 窗口标题
							WS_OVERLAPPEDWINDOW,			// 窗口外观和行为的通用窗口标识
							0, 0, 400, 400,					// 窗口左上角位置和宽高
							NULL,							// 父窗口句柄
							NULL,							// 菜单句柄
							hInstance,						// 应用程序实例
							NULL);							// 高级特征
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

// 事件处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC			hdc;

	switch (message)
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

	return (DefWindowProc(hWnd, message, wParam, lParam));
}
