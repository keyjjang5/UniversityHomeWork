
// MFCApplication7Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMFCApplication7Dlg ��ȭ ����
class CMFCApplication7Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCApplication7Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION7_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��ũ�ѹ�
	CScrollBar scrollBarTest;
	afx_msg void scrollBarcont(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void editUpdate();
	CEdit editTest;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
