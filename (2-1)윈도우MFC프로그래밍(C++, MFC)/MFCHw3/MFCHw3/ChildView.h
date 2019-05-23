
// ChildView.h : CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CList<CPoint> pt;
	CList<COLORREF> ptColor;
	POSITION ptPos;
	CList<int> ptType;
	POSITION typePos;
	POSITION colorPos;

	CPoint eraserSPt;
	CPoint eraserEPt;
	CPoint sPt, ePt;
	CPoint move;

	
	bool onEraser;
	bool onEraserMove;
	bool onRight;
	bool onLeft;
	bool onUp;
	bool onDown;

	bool rectDraw;
	bool circleDraw;
	bool mouseDown;

	bool onRed;
	bool onGreen;
	bool onBlue;
	bool onBlack;
// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnColorBlue();
	afx_msg void OnColorGreen();
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnButton32774();
	afx_msg void OnButton32775();
	afx_msg void OnUpdateButton32774(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButton32775(CCmdUI *pCmdUI);
	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnButton32778();
	afx_msg void OnUpdateButton32778(CCmdUI *pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

