
// MFCHw3.h : MFCHw3 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCHw3App:
// �� Ŭ������ ������ ���ؼ��� MFCHw3.cpp�� �����Ͻʽÿ�.
//

class CMFCHw3App : public CWinApp
{
public:
	CMFCHw3App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCHw3App theApp;
