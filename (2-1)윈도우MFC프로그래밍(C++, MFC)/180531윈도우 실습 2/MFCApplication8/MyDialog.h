#pragma once
#include "afxwin.h"


// CMyDialog ��ȭ �����Դϴ�.

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMyDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit editTest;
	CButton radioTest[3];
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CButton buttonTest;

	CString m_str;
	int m_color;

	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
};
