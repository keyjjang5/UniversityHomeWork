
// ChildView.cpp : CChildView 클래스의 구현
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
	
	dc.Rectangle(m_pt.x - 50, m_pt.y - 50, m_pt.x + 50, m_pt.y + 50);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_HBar.SetWindowPos(this, 0, 0, cx - 20, 20, SWP_NOZORDER);
	m_VBar.SetWindowPos(this, cx - 20, 20, cx, cy - 20, SWP_NOZORDER);
	//cx,cy는 윈도우 사이즈

	m_HBar.SetScrollRange(20, cx - 40);
	m_VBar.SetScrollRange(40, cy - 40);
	
	m_HBar.SetScrollPos(m_pt.x);
	m_VBar.SetScrollPos(m_pt.y);



}


void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMyDialog dig;

	dig.m_str = m_str;
	dig.m_color = m_color;

	if (dig.DoModal() != IDOK)
		return;

	m_str = dig.m_str;
	m_color = dig.m_color;

	CWnd::OnLButtonDown(nFlags, point);
}
