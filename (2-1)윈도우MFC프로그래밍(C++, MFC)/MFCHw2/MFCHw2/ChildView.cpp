
// ChildView.cpp : CChildView Ŭ������ ����
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



// CChildView �޽��� ó����

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
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	for (int i = 0; i < numCount; i++)
	{
		shape[i]->draw(&dc);
		
	}
	
	/*dc.Ellipse(passPt.x - 25, passPt.y - 25, passPt.x + 25, passPt.y + 25);
	if (polyCheck)//���ʽ������� Ǯ���� �ߴ� ����
	{
		
		polyPt = (CPoint*)malloc(sizeof(CPoint)*polyCount);

		polyPt[polyCount] = CPoint(passPt);

		CRgn rgn;
		rgn.CreatePolygonRgn(polyPt, polyCount+1, ALTERNATE);
		CBrush polyBrush(RGB(255, 0, 0));
		dc.SelectObject(&polyBrush);
		dc.FillRgn(&rgn, &polyBrush);
	}*/


	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SetCapture();
	shape[numCount] = new CMyRect();
	shape[numCount]->ptS = point;
	rCheck = true;
	
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ReleaseCapture();
	shape[numCount]->ptE = point;
	rCheck = false;
	numCount++;
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (rCheck || eCheck)
	{
		shape[numCount]->ptE = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	eCheck = true;
	shape[numCount] = new CMyCircle();
	shape[numCount]->ptS = point;
	
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	

	return 0;
}


void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	//// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//passPt = point;
	//polyCount++;
	//Invalidate();
	CWnd::OnMButtonDown(nFlags, point);
}


void CChildView::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	/*polyCheck = true;
	Invalidate();*/
	CWnd::OnNcLButtonDown(nHitTest, point);
}
