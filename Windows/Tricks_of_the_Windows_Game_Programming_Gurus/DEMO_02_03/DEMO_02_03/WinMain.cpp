#define WIN32_LEAN_AND_MEAN		// just say no to MFC

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_CLASS_NAME		"WINCLASS1"


// ȫ�ֱ���
HINSTANCE hInst;


// ��������
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

// ע�ᴰ����
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX winClass;

	winClass.cbSize				= sizeof(WNDCLASSEX);								// �ṹ���С

	winClass.style				= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;	// ������ʽ��Ϣ��ʶ��
																					//		CS_HREDRAW			�ƶ���ı��˴��ڵĿ�ȣ���ˢ����������
																					//		CS_VREDRAW			�ƶ���ı��˴��ڵĸ߶ȣ���ˢ����������
																					//		CS_OWNDC			Ϊ������ÿ�����ڷ���һ����ֵ���豸������
																					//		CS_DBLCLKS			���û�˫�����ʱ�򴰿ڳ�����һ��˫������Ϣ
																					//							ͬʱ�����λ�����ڸ���Ĵ�����
																					//		CS_PARENTDC			��ĸ�������趨һ���Ӵ��ڵļ��������Ա��Ӵ����ܻ���ĸ������
																					//		CS_SAVEBITS			��һ�������б����û�ͼ���Ա��ڸô��ڱ���סʱ����ÿ��ˢ����Ļ
																					//		CS_NOCLOSE			��ֹ�˵��ϵĹرհ�ť

	winClass.lpfnWndProc		= WndProc;											// ָ���¼�����ĺ���ָ��
	winClass.cbClsExtra			= 0;												// ���渽�ӵ�����ʱ��Ϣ
	winClass.cbWndExtra			= 0;												// ͬ��
	winClass.hInstance			= hInstance;										// Ӧ�ó���ʵ��

	winClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);					// ����ͼ������
																					//		IDI_APPLICATION		Ĭ��Ӧ�ó���ͼ��
																					//		IDI_ASTREISX		�Ǻ�
																					//		IDI_EXCLAMATION		��̾��
																					//		IDI_HAND			����ͼ��
																					//		IDI_QUESTION		�ʺ�
																					//		IDI_WINLOGO			Windows�ձ�

	winClass.hCursor			= LoadCursor(NULL, IDC_ARROW);						// ���ͼ������
																					//		IDC_ARROW			��׼��ͷ
																					//		IDC_APPSTARTING		��׼��ͷ��Сɳ©
																					//		IDC_CROSS			�����
																					//		IDC_IBEAM			�ı�I�ͱ�
																					//		IDC_NO				����б�ߵ�ԲȦ
																					//		IDC_SIZEALL			�����ͷ
																					//		IDC_SIZENESW		ָ�򶫱�-����˫���ͷ
																					//		IDC_SIZENS			ָ����-��˫���ͷ
																					//		IDC_SIZENWSE		ָ����-����˫���ͷ
																					//		IDC_SIZEWE			ָ��-��˫���ͷ
																					//		IDC_UPARROW			��ֱ�����ͷ
																					//		IDC_WAIT			ɳ©

	winClass.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);				// ����ɫ
																					//		GETStockObject		���ڻ��Windowsϵͳ��ˢ�����ʡ���ɫ��������һ�����
																					//			BLACK_BRUSH		��ɫ��ˢ
																					//			WHITE_BRUSH		��ɫ��ˢ
																					//			GRAY_BRUSH		��ɫ��ˢ
																					//			LTGRAY_BRUSH	ǳ��ɫ��ˢ
																					//			DKGRAY_BRUSH	���ɫ��ˢ
																					//			HOLLOW_BRUSH	���Ļ�ˢ
																					//			NULL_BRUSH		�ջ�ˢ
																					//			BLACK_PEN		��ɫ����
																					//			WHITE_PEN		��ɫ����
																					//			NULL_PEN		�ջ���
																					
	winClass.lpszMenuName		= "menu name";										// �˵�����
	winClass.lpszClassName		= WINDOW_CLASS_NAME;								// ����������
	winClass.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);					// Сͼ��

	return (RegisterClassEx(&winClass));
}

// ʵ��������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	// �ú������ִ�гɹ�����һ��ָ���´��ڵľ�������򷵻�NULL
	hWnd = CreateWindowEx(	NULL,							// ���ⴰ������
							WINDOW_CLASS_NAME,				// ��������������
							NULL,							// ���ڱ���
							WS_OVERLAPPEDWINDOW,			// ������ۺ���Ϊ��ͨ�ô��ڱ�ʶ
							0, 0, 400, 400,					// �������Ͻ�λ�úͿ��
							NULL,							// �����ھ��
							NULL,							// �˵����
							hInstance,						// Ӧ�ó���ʵ��
							NULL);							// �߼�����
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

// �¼�������
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
