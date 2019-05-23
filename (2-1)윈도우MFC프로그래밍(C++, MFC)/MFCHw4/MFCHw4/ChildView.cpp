
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCHw4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	ptList.RemoveAll();
	nowSelect = 0;
	onAni = false;
	
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, aniStartFun)
	ON_BN_CLICKED(102, aniStopFun)
	ON_BN_CLICKED(103, saveFun)
	ON_BN_CLICKED(104, loadFun)
	ON_BN_CLICKED(105, clearFun)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
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

	scroll.SetScrollRange(0, ptList.GetCount()-1);

	POSITION rectPos = ptList.GetHeadPosition();
	POSITION linePos = ptList.GetHeadPosition();

	CRect rect;
	GetClientRect(rect);
	CDC memDC; // 가상 DC
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; // 그림을 저장할 공간 마련 
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	if (!onAni)
	{
		if (ptList.GetCount() > 0)
			memDC.MoveTo(ptList.GetHead());
		for (int i = 0; i < ptList.GetCount(); i++)
		{
			CPoint pt = ptList.GetNext(linePos);
			CPen linePen(PS_SOLID, 1, RGB(0, 0, 0));
			memDC.SelectObject(&linePen);
			memDC.LineTo(pt);

		}

		for (int i = 0; i < ptList.GetCount(); i++)
		{
			CPoint pt = ptList.GetNext(rectPos);
			CPen blackPen(PS_SOLID, 2, RGB(0, 0, 0));
			CPen redPen(PS_SOLID, 2, RGB(255, 0, 0));

			if (i != nowSelect)
			{
				memDC.SelectObject(&blackPen);
			}
			else if (i == nowSelect)
			{
				memDC.SelectObject(&redPen);
			}

			memDC.Rectangle(pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
		}
	}
	else if (onAni)
	{
		if (ptList.GetCount() > 0)
			memDC.MoveTo(ptList.GetHead());
		for (int i = 0; i < ptList.GetCount(); i++)
		{
			CPoint pt = ptList.GetNext(linePos);
			CPen linePen(PS_DASH, 1, RGB(0, 0, 0));
			memDC.SelectObject(&linePen);
			memDC.LineTo(pt);
		}
		
		CPen blackPen(PS_SOLID, 2, RGB(0, 0, 0));
		memDC.SelectObject(&blackPen);
		memDC.Rectangle(boxpt.x - 20, boxpt.y - 20, boxpt.x + 20, boxpt.y + 20);
	}
	
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (!onAni)
	{
		ptList.AddTail(point);
		nowSelect = ptList.GetCount() - 1;
	}
	Invalidate();
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonUp(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	aniStart.Create(_T(">"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(0, 0, 80, 30), this, 101);
	aniStop.Create(_T("||"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(80, 0, 160, 30), this, 102);

	save.Create(_T("SAVE"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(160, 0, 240, 30), this, 103);
	load.Create(_T("LOAD"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(240, 0, 320, 30), this, 104);

	clear.Create(_T("CLEAR"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(320, 0, 400, 30), this, 105);

	scroll.Create(SBS_HORZ, CRect(400, 0, 800, 30), this, 106);
	scroll.ShowWindow(true);

	return 0;
}

void CChildView::aniStartFun() // 메시지 핸들러
{
	SetTimer(0, 44, NULL);
	SetTimer(1, 1000, NULL);

	boxpt = ptList.GetHead();

	timerPos = ptList.GetHeadPosition();
	
	nowSelect = -1;

	onAni = true;

	anipt = 0;

	Invalidate();
}

void CChildView::aniStopFun() // 메시지 핸들러
{
	KillTimer(0);
	KillTimer(1);
	onAni = false;

	nowSelect = ptList.GetCount() - 1;

	Invalidate();
}

void CChildView::saveFun() // 메시지 핸들러
{
	CFile file(_T("SaveData.dat"), CFile::modeCreate | CFile::modeWrite);

	CArchive ar(&file, CArchive::store);
	ptList.Serialize(ar);
	
}

void CChildView::loadFun() // 메시지 핸들러
{
	ptList.RemoveAll();
	CFile file;
	CFileException e;
	if (!file.Open(_T("SaveData.dat"), CFile::modeRead, &e))
	{
		e.ReportError();
		return;
	}

	CArchive ar(&file, CArchive::load);
	ptList.Serialize(ar);

	Invalidate();
}

void CChildView::clearFun() // 메시지 핸들러
{
	ptList.RemoveAll();

	Invalidate();
}

void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (pScrollBar != NULL)
	{
		if (pScrollBar->GetSafeHwnd() == scroll.GetSafeHwnd())
		{
			if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
			{
				pScrollBar->SetScrollPos(nPos);
				
				nowSelect = nPos;

				this->Invalidate();
			}
			if (nSBCode == SB_LINELEFT)
			{
				if(nowSelect != 0)
				nPos = nowSelect - 1;

				pScrollBar->SetScrollPos(nPos);

				nowSelect = nPos;

				this->Invalidate();
			}
			if (nSBCode == SB_LINERIGHT)
			{
				if (nowSelect != ptList.GetCount() - 1)
				{
					nPos = nowSelect + 1;

					pScrollBar->SetScrollPos(nPos);

					nowSelect = nPos;
				}
				this->Invalidate();
			}
		}
	}

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		boxpt += anipt;
		
		Invalidate();
	}

	if (nIDEvent == 1)
	{
		if (nowSelect == ptList.GetCount() - 2)
			aniStartFun();

		boxpt = ptList.GetAt(timerPos);
		CPoint pt1 = ptList.GetNext(timerPos);
		CPoint pt2 = ptList.GetAt(timerPos);
		anipt = pt2 - pt1;
		anipt.x /= 20;
		anipt.y /= 20;

		nowSelect++;
		scroll.SetScrollPos(nowSelect);
			
	}
	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);

	return true;
}
