/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <SDKDDKVer.h>

//===========================================================================
// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN

//===========================================================================
// Windows 헤더 파일
#include <windows.h>

//===========================================================================
// C 런타임 헤더 파일입니다.
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
/*
# .manifest 리소스 추가시 빌드 설정

/프로젝트 속성/구성 속성/메니페스트 도구/입력 및 출력
- 매니페스트 포함: 아니요

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
	OutputDebugStringA((LPCSTR)u8"가나다라"); // 출력 안됨
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");
	OutputDebugStringA("\r\n");

	char8_t A_ga_B[6] = { 65, 234, 176, 128, 66, 0 };

	MessageBoxA(nullptr, (LPCSTR)u8"가나다라", (LPCSTR)A_ga_B, MB_OK);
	OutputDebugStringA((LPCSTR)A_ga_B); // 출력 안됨
	
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
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{

	char* p = new char[1];

	test_utf8();


	return 0;
}
