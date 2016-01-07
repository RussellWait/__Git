#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	MessageBox(	NULL, 
		"THERE CAN BE ONLY ONE!!!", 
		"MY FIRST WINDOWS PROGRAM",
		MB_OK | MB_ICONEXCLAMATION);

	return 0;
}
