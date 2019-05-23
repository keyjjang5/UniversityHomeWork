
// MFCApplication8Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMFCApplication8Dlg 대화 상자
class CMFCApplication8Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication8Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION8_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	// 첫번째 체크버튼
	CButton checkButton1;
	CButton radioButton1;
	CButton radioButton2;
	afx_msg void OnBnClickedOk();
	afx_msg void pictureButton1();
	// Edit Control에서 사용
	CEdit EditTest;
	afx_msg void EditTestUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
