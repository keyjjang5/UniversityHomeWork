
// MFCApplication8Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMFCApplication8Dlg ��ȭ ����
class CMFCApplication8Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCApplication8Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION8_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	// ù��° üũ��ư
	CButton checkButton1;
	CButton radioButton1;
	CButton radioButton2;
	afx_msg void OnBnClickedOk();
	afx_msg void pictureButton1();
	// Edit Control���� ���
	CEdit EditTest;
	afx_msg void EditTestUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
