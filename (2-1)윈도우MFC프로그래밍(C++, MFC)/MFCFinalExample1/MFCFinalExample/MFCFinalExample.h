
// MFCFinalExample.h : MFCFinalExample ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFinalExampleApp:
// �� Ŭ������ ������ ���ؼ��� MFCFinalExample.cpp�� �����Ͻʽÿ�.
//

class CMFCFinalExampleApp : public CWinApp
{
public:
	CMFCFinalExampleApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFinalExampleApp theApp;
