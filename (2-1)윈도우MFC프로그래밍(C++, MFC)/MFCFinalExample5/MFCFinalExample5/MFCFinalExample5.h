
// MFCFinalExample5.h : MFCFinalExample5 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCFinalExample5App:
// �� Ŭ������ ������ ���ؼ��� MFCFinalExample5.cpp�� �����Ͻʽÿ�.
//

class CMFCFinalExample5App : public CWinApp
{
public:
	CMFCFinalExample5App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFinalExample5App theApp;
