#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
//////////////
// INCLUDES //
//////////////
#include <windows.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
// 수직동기화를 끄고 키는 것
const bool VSYNC_ENABLED = true;
// 화면 안에 얼만큼 까지 랜더링하는 것에 사용 할 것인지
const float SCREEN_DEPTH = 1000.0f;
// 얼마나 가깝게 랜더링 할 것인지						> 둘다 사용자(카메라) 기준	> 더좋은 방법은 외부 txt같은걸 읽어서 하는게 좋음
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();
};
#endif