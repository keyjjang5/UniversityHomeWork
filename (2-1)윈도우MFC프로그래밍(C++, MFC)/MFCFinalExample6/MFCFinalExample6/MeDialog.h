#pragma once
#include "afxwin.h"


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
	CEdit mainEdit;
	CEdit rEdit;
	CEdit gEdit;
	CEdit bEdit;

	CString str;
	int rp;
	int gp;
	int bp;
};
