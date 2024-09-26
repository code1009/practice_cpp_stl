/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <SDKDDKVer.h>

//===========================================================================
// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN

//===========================================================================
// Windows ��� ����
#include <windows.h>

//===========================================================================
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//===========================================================================
#if defined(_DEBUG)
#include "../../vld/vld.h"
#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if defined(UNICODE)
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
# .manifest ���ҽ� �߰��� ���� ����

/������Ʈ �Ӽ�/���� �Ӽ�/�޴��佺Ʈ ����/�Է� �� ���
- �Ŵ��佺Ʈ ����: �ƴϿ�

*/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void test_utf8(void)
{
	// vld test
	char* p = new char{ 0 };

	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");
	OutputDebugStringA((LPCSTR)u8"MESSAGE:");
	OutputDebugStringA((LPCSTR)u8"�����ٶ�"); // ��� �ȵ�
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");

	char8_t A_ga_B[6] = { 65, 234, 176, 128, 66, 0 };

	MessageBoxA(nullptr, (LPCSTR)u8"�����ٶ�", (LPCSTR)A_ga_B, MB_OK);
	OutputDebugStringA((LPCSTR)A_ga_B); // ��� �ȵ�
	
#if 0
<?xml version="1.0" encoding="utf-8" standalone="yes"?>
<assembly manifestVersion="1.0" xmlns="urn:schemas-microsoft-com:asm.v1">
  <assemblyIdentity type="win32" name="..." version="6.0.0.0"/>
  <application>
    <windowsSettings>
      <activeCodePage xmlns="http://schemas.microsoft.com/SMI/2019/WindowsSettings">UTF-8</activeCodePage>
    </windowsSettings>
  </application>
</assembly>
#endif
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int getch() 
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE) 
	{
		return -1;
	}

	DWORD mode;
	if (!GetConsoleMode(hStdin, &mode)) 
	{
		return -1;
	}

	// �ܼ� ��带 �����Ͽ� �Է��� ��� ó���ϵ��� ����
	SetConsoleMode(hStdin, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

	INPUT_RECORD inputRecord;
	DWORD events;
	char ch = 0;

	while (true) 
	{
		if (!ReadConsoleInput(hStdin, &inputRecord, 1, &events)) 
		{
			return -1;
		}

		if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) 
		{
			ch = inputRecord.Event.KeyEvent.uChar.AsciiChar;
			break;
		}
	}

	// ���� �ܼ� ���� ����
	SetConsoleMode(hStdin, mode);

	return ch;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int practice_cpp_stl_cotask_0(void);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void practice_main(void)
{
	//char* p = new char[1];

//test_utf8();

	practice_cpp_stl_cotask_0();

	getch();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int APIENTRY
wWinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow
)
{
	practice_main();
	return 0;
}

//===========================================================================
int APIENTRY
WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow
)
{
	practice_main();
	return 0;
}