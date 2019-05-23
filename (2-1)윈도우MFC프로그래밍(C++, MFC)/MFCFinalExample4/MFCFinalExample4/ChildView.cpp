
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCFinalExample4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, radioRectFun)
	ON_BN_CLICKED(102, radioCircleFun)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(rect);
	CDC memDC; // 가상 DC
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; // 그림을 저장할 공간 마련 
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	CPoint pt;

	pt.x = rect.Width()/2;
	pt.y = rect.Height()/2;
	CPoint width;
	width.x = rect.Width() / 10;
	width.y = rect.Height() / 10;
	if (type == 1)
	{
		memDC.Rectangle(pt.x - width.x, pt.y - width.y, pt.x + width.x, pt.y + width.y);
	}
	else if (type == 2)
	{
		memDC.Ellipse(pt.x - width.x, pt.y - width.y, pt.x + width.x, pt.y + width.y);
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	radioRect.Create(_T("사각형"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(0, 0, 80, 30), this, 101);
	radioCircle.Create(_T("원"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(80, 0, 160, 30), this, 102);
	
	return 0;
}

void CChildView::radioRectFun()
{
	type = 1;
	Invalidate();
}

void CChildView::radioCircleFun()
{
	type = 2;
	Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
