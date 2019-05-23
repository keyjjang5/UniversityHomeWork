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
// ��������ȭ�� ���� Ű�� ��
const bool VSYNC_ENABLED = true;
// ȭ�� �ȿ� ��ŭ ���� �������ϴ� �Ϳ� ��� �� ������
const float SCREEN_DEPTH = 1000.0f;
// �󸶳� ������ ������ �� ������						> �Ѵ� �����(ī�޶�) ����	> ������ ����� �ܺ� txt������ �о �ϴ°� ����
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