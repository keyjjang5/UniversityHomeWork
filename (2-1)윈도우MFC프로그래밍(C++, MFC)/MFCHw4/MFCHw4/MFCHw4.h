
// MFCHw4.h : MFCHw4 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCHw4App:
// �� Ŭ������ ������ ���ؼ��� MFCHw4.cpp�� �����Ͻʽÿ�.
//

class CMFCHw4App : public CWinApp
{
public:
	CMFCHw4App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCHw4App theApp;
