#pragma once


// DoModal 대화 상자입니다.

class DoModal : public CDialog
{
	DECLARE_DYNAMIC(DoModal)

public:
	DoModal(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~DoModal();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
