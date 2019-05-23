
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCHw2.h"
#include "ChildView.h"

#include "CMyShape.h"
#include "CMyRect.h"
#include "CMyCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	rCheck = false;
	eCheck = false;
	numCount = 0;

	polyCheck = false;
	polyCount = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_MBUTTONDOWN()
	ON_WM_NCLBUTTONDOWN()
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

	for (int i = 0; i < numCount; i++)
	{
		shape[i]->draw(&dc);
		
	}
	
	/*dc.Ellipse(passPt.x - 25, passPt.y - 25, passPt.x + 25, passPt.y + 25);
	if (polyCheck)//보너스문제를 풀려고 했던 흔적
	{
		
		polyPt = (CPoint*)malloc(sizeof(CPoint)*polyCount);

		polyPt[polyCount] = CPoint(passPt);

		CRgn rgn;
		rgn.CreatePolygonRgn(polyPt, polyCount+1, ALTERNATE);
		CBrush polyBrush(RGB(255, 0, 0));
		dc.SelectObject(&polyBrush);
		dc.FillRgn(&rgn, &polyBrush);
	}*/


	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCapture();
	shape[numCount] = new CMyRect();
	shape[numCount]->ptS = point;
	rCheck = true;
	
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ReleaseCapture();
	shape[numCount]->ptE = point;
	rCheck = false;
	numCount++;
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (rCheck || eCheck)
	{
		shape[numCount]->ptE = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	eCheck = true;
	shape[numCount] = new CMyCircle();
	shape[numCount]->ptS = point;
	
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	eCheck = false;
	shape[numCount]->ptE = point;
	numCount++;
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	

	return 0;
}


void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	//// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//passPt = point;
	//polyCount++;
	//Invalidate();
	CWnd::OnMButtonDown(nFlags, point);
}


void CChildView::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*polyCheck = true;
	Invalidate();*/
	CWnd::OnNcLButtonDown(nHitTest, point);
}
