#pragma once


// DoModal ��ȭ �����Դϴ�.

class DoModal : public CDialog
{
	DECLARE_DYNAMIC(DoModal)

public:
	DoModal(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DoModal();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
