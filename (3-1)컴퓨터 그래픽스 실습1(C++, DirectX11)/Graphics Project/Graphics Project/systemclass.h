#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

// windows.h를 최소한으로 사용하겠다는 선언
// win32를 쓸건데 라이트하게 쓸거임
#define WIN32_LEAN_AND_MEAN

//////////////
// INCLUDES //
//////////////
#include <windows.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////

// 포함 개념임, 상속은 사용 안함
#include "inputclass.h"
#include "graphicsclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
////////////////////////////////////////////////////////////////////////////////

// 윈도우 메시지와 관련된 것들을 담당
// 최상위 클래스
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
	// 초기화, 꺼질때 사용(메모리 해제 등), 메인loop
	// Initialize를 사용하는 이유 : 생성자는 내맘대로 호출하면 문제가 생길 수 있음, 그래서 값을 초기로 되돌리기 위해서 사용함
	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	// 중요
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
};
/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////

// 윈도우 메시지 받으면 처리하는 함수
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////
// GLOBALS //
/////////////

static SystemClass* ApplicationHandle = 0;
#endif