
// MFCApplication8.h : MFCApplication8 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCApplication8App:
// �� Ŭ������ ������ ���ؼ��� MFCApplication8.cpp�� �����Ͻʽÿ�.
//

class CMFCApplication8App : public CWinApp
{
public:
	CMFCApplication8App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication8App theApp;
