
// MFCFInalExample7.h : MFCFInalExample7 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFInalExample7App:
// �� Ŭ������ ������ ���ؼ��� MFCFInalExample7.cpp�� �����Ͻʽÿ�.
//

class CMFCFInalExample7App : public CWinApp
{
public:
	CMFCFInalExample7App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFInalExample7App theApp;
