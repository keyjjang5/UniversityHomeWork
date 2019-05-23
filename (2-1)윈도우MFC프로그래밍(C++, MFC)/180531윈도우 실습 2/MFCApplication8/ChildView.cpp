
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication8.h"
#include "ChildView.h"
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_color = 1;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
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
	
	dc.Rectangle(m_pt.x - 50, m_pt.y - 50, m_pt.x + 50, m_pt.y + 50);

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	m_HBar.Create(SBS_HORZ, CRect(0, 0, 400, 20), this, 101);
	m_VBar.Create(SBS_VERT, CRect(0, 0, 20, 400), this, 102);

	m_HBar.ShowWindow(true);
	m_VBar.ShowWindow(true);

	m_pt = CPoint(200, 200);



	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	m_HBar.SetWindowPos(this, 0, 0, cx - 20, 20, SWP_NOZORDER);
	m_VBar.SetWindowPos(this, cx - 20, 20, cx, cy - 20, SWP_NOZORDER);
	//cx,cy�� ������ ������

	m_HBar.SetScrollRange(20, cx - 40);
	m_VBar.SetScrollRange(40, cy - 40);
	
	m_HBar.SetScrollPos(m_pt.x);
	m_VBar.SetScrollPos(m_pt.y);



}


void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (pScrollBar != NULL)
	{
		if (pScrollBar->GetSafeHwnd() == m_HBar.GetSafeHwnd())
		{
			if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
			{
				pScrollBar->SetScrollPos(nPos);
				m_pt.x = nPos;
				this->Invalidate();
			}
		}
	}

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (pScrollBar != NULL)
	{
		if (pScrollBar->GetSafeHwnd() == m_VBar.GetSafeHwnd())
		{
			if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
			{
				pScrollBar->SetScrollPos(nPos);
				m_pt.y = nPos;
				this->Invalidate();
			}
		}
	}

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMyDialog dig;

	dig.m_str = m_str;
	dig.m_color = m_color;

	if (dig.DoModal() != IDOK)
		return;

	m_str = dig.m_str;
	m_color = dig.m_color;

	CWnd::OnLButtonDown(nFlags, point);
}
