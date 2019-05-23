
// MFCApplication7Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMFCApplication7Dlg 대화 상자
class CMFCApplication7Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication7Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION7_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 스크롤바
	CScrollBar scrollBarTest;
	afx_msg void scrollBarcont(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void editUpdate();
	CEdit editTest;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
