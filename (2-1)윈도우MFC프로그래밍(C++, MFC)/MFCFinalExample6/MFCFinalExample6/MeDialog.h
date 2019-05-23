#pragma once
#include "afxwin.h"


// MeDialog 대화 상자입니다.

class MeDialog : public CDialog
{
	DECLARE_DYNAMIC(MeDialog)

public:
	MeDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MeDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
