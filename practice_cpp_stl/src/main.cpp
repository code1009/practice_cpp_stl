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

#include <stdio.h>
#include <locale.h>

//===========================================================================
#include <clocale>
#include <iostream>

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

//===========================================================================
const char* cast_const_char_ptr(char8_t* p)
{
	return
		const_cast<const char*>
		(
			reinterpret_cast<char*>(p)
			);
}

const char* cast_const_char_ptr(const char8_t* p)
{
	return
		reinterpret_cast<const char*>(p);
}

const wchar_t* cast_const_wchar_ptr(char16_t* p)
{
	return
		const_cast<const wchar_t*>
		(
			reinterpret_cast<wchar_t*>(p)
			);
}

const wchar_t* cast_const_wchar_ptr(const char16_t* p)
{
	return
		reinterpret_cast<const wchar_t*>(p);
}

//===========================================================================
// ���� �� ��
//#pragma execution_character_set("utf-8")

//===========================================================================
void test_utf8(void)
{
	//-----------------------------------------------------------------------
	//SetConsoleOutputCP(65001);


	//-----------------------------------------------------------------------
	//const char* cpp_local = ".utf8";
	//const char* cpp_local = "ko_KR.utf8";
	//const char* cpp_local = "ko_KR";

	//std::setlocale(LC_ALL, cpp_local); // cpp runtime


	//-----------------------------------------------------------------------
	//const char* c_local = ".utf8";
	const char* c_local = "ko_KR.utf8";
	//const char* c_local = "ko_KR";

	setlocale(LC_ALL, c_local); // c runtime


	//-----------------------------------------------------------------------
	unsigned char _ga_euckr  [3] = { 0xb0, 0xa1, 0 };
	char8_t       _ga_utf8   [4] = { 0xea, 0xb0, 0x80, 0 };
	wchar_t       _ga_unicode[2] = { 0xac00, 0 }; // linux 32 bit, window 16 bit
	char16_t      _ga_utf16  [2] = { 0xac00, 0 };


	std::cout  <<  "std::cout  << _ga_euckr  : " << _ga_euckr << std::endl;
	std::cout  <<  "std::cout  << _ga_utf8   : " << cast_const_char_ptr(_ga_utf8) << std::endl;
	std::wcout << L"std::wcout << _ga_utf16  : " << cast_const_wchar_ptr(_ga_utf16) << std::endl; // local �̼����� ��µ��� ����
	std::wcout << L"std::wcout << _ga_unicode: " << _ga_unicode << std::endl; // local �̼����� ��µ��� ����
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;



	//-----------------------------------------------------------------------
	char8_t A_ga_B[6] = { 65, 234, 176, 128, 66, 0 };


	printf("printf()    : %s\r\n",
		//reinterpret_cast<char*>(&A_ga_B[0])
		cast_const_char_ptr(&A_ga_B[0])
	);

	std::cout << "std::cout<< : " << cast_const_char_ptr(A_ga_B) << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	//-----------------------------------------------------------------------
	// vld test
	//char* p = new char[1];
	char* p = new char{ 0 };

	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");

	OutputDebugStringA((LPCSTR)u8"MESSAGE:");
	OutputDebugStringA("\r\n");

	OutputDebugStringA((LPCSTR)u8"�����ٶ�a"); // ��� �ȵ�(a�� ��¾ȵ�)
	OutputDebugStringA("\r\n");

	OutputDebugStringA((LPCSTR)A_ga_B); // ��� ����
	OutputDebugStringA("\r\n");

	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");


	MessageBoxA(nullptr, (LPCSTR)u8"�����ٶ�", (LPCSTR)A_ga_B, MB_OK);


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
	char ch;


	ch = 0;

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
int practice_cpp_stl_coroutine_0(void);
int practice_cpp_stl_coroutine_1(void);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void practice_main(void)
{
	//test_utf8();

	//practice_cpp_stl_coroutine_0();
	practice_cpp_stl_coroutine_1();

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

int main()
{
	practice_main();
	return 0;
}

int wmain()
{
	practice_main();
	return 0;
}


