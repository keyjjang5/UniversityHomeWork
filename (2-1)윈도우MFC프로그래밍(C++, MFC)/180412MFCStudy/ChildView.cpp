
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication10.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	r = 255;
	g = 255;
	b = 255;
	pt = CPoint(50, 50);
	dd.x = 10;
	dd.y = 10;
	m_py = 100;
	m_ay = 0;
	m_vy = 0;
	boo = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	CBrush brush(RGB(r, g, b));
	dc.SelectObject(&brush);
	/*dc.Ellipse(pt.x, pt.y, pt.x + 50, pt.y + 50);*/
	dc.Ellipse(pt.x, m_py, pt.x + 50, m_py + 50);
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CClientDC dc(this);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 0)
	{
		/*RECT rect;
		GetClientRect(&rect);
		if (rect.right < pt.x + 50)
			dd.x = -10;
		else if (rect.left > pt.x)
			dd.x = 10;
		else if (rect.bottom < pt.y + 50)
			dd.y = -10;
		else if (rect.top > pt.y)
			dd.y = 10;

		pt.x += dd.x;
		pt.y += dd.y;*/

		RECT rect;
		GetClientRect(&rect);
		float dt = 0.03f;
		float fy = 300;
		m_ay = fy;
		m_vy = m_vy + m_ay*dt;
		m_py = m_py + m_vy*dt;
		if (m_py + 50> rect.bottom)
		{
			m_py = (float)rect.bottom - 50;
			m_vy = -m_vy * 0.8f;
		}
		
		Invalidate();
	}
	if (nIDEvent == 1)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		Invalidate();
	}
	if (nIDEvent == 2)
	{
		KillTimer(1);
		KillTimer(2);
	}
	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 10, NULL);
	
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (point.x > pt.x && point.x < pt.x + 50 && point.y > m_py && point.y < m_py + 50)
	{
		KillTimer(0);
		boo = true;
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SetTimer(1, 100, NULL);
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_py = 100;
	m_ay = 0;
	m_vy = 0;
	CWnd::OnMButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SetTimer(0, 10, NULL);
	boo = false;
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (boo)
	{
		m_py = point.y;

		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}
