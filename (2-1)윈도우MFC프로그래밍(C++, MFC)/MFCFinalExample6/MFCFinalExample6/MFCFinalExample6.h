
// MFCFinalExample6.h : MFCFinalExample6 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFinalExample6App:
// �� Ŭ������ ������ ���ؼ��� MFCFinalExample6.cpp�� �����Ͻʽÿ�.
//

class CMFCFinalExample6App : public CWinApp
{
public:
	CMFCFinalExample6App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFinalExample6App theApp;
