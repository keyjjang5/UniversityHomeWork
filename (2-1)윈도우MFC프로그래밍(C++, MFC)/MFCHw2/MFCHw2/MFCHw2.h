
// MFCHw2.h : MFCHw2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCHw2App:
// �� Ŭ������ ������ ���ؼ��� MFCHw2.cpp�� �����Ͻʽÿ�.
//

class CMFCHw2App : public CWinApp
{
public:
	CMFCHw2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCHw2App theApp;
