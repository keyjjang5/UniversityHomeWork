
// MFCFinalExample2.h : MFCFinalExample2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFinalExample2App:
// �� Ŭ������ ������ ���ؼ��� MFCFinalExample2.cpp�� �����Ͻʽÿ�.
//

class CMFCFinalExample2App : public CWinApp
{
public:
	CMFCFinalExample2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFinalExample2App theApp;
