
// MFCFinalExample4.h : MFCFinalExample4 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFinalExample4App:
// �� Ŭ������ ������ ���ؼ��� MFCFinalExample4.cpp�� �����Ͻʽÿ�.
//

class CMFCFinalExample4App : public CWinApp
{
public:
	CMFCFinalExample4App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFinalExample4App theApp;
