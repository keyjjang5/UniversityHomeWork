#pragma once
#include "afxwin.h"

class CChildView;

// MeDialog ��ȭ �����Դϴ�.

class MeDialog : public CDialog
{
	DECLARE_DYNAMIC(MeDialog)

public:
	MeDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MeDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton oneButton;
	CButton twoButton;
	CButton ThreeButton;
	CButton plusButton;
	CButton minusButton;
	CButton eqaulButton;
	CButton clearButton;

	CChildView *view;
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	afx_msg void OnClickedButton5();
	afx_msg void OnClickedButton6();
	afx_msg void OnClickedButton7();
	afx_msg void OnBnClickedOk();

	CString str[100];
	CString pass;
	CString sumpass;
	int i;
	int count;
};
