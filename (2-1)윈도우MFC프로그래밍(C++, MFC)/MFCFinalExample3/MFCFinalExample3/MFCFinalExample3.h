
// MFCFinalExample3.h : MFCFinalExample3 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFinalExample3App:
// �� Ŭ������ ������ ���ؼ��� MFCFinalExample3.cpp�� �����Ͻʽÿ�.
//

class CMFCFinalExample3App : public CWinApp
{
public:
	CMFCFinalExample3App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFinalExample3App theApp;
