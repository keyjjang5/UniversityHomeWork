
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCHw3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	rectDraw = false;
	circleDraw = false;
	mouseDown = false;
	onRed = false;
	onGreen = false;
	onBlue = false;
	onBlack = true;

	onEraser = false;
	onEraserMove = false;
	onRight = false;
	onLeft = false;
	onUp = false;
	onDown = false;

	move = CPoint(0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_COMMAND(ID_BUTTON32774, &CChildView::OnButton32774)
	ON_COMMAND(ID_BUTTON32775, &CChildView::OnButton32775)
	ON_UPDATE_COMMAND_UI(ID_BUTTON32774, &CChildView::OnUpdateButton32774)
	ON_UPDATE_COMMAND_UI(ID_BUTTON32775, &CChildView::OnUpdateButton32775)
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_COMMAND(ID_BUTTON32778, &CChildView::OnButton32778)
	ON_UPDATE_COMMAND_UI(ID_BUTTON32778, &CChildView::OnUpdateButton32778)
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
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
	int count = 0;

	ptPos = pt.GetHeadPosition();
	typePos = ptType.GetHeadPosition();
	colorPos = ptColor.GetHeadPosition();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.



	CRect rect;
	GetClientRect(rect);
	CDC memDC; // 가상 DC
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; // 그림을 저장할 공간 마련 
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	while (ptPos != NULL)
	{
		CPoint getPtPos = pt.GetNext(ptPos);
		int getTypePos = ptType.GetNext(typePos);

		CBrush brush = ptColor.GetNext(colorPos);
		memDC.SelectObject(&brush);
		if (getTypePos == 1)
			memDC.Rectangle(getPtPos.x - 5, getPtPos.y - 5, getPtPos.x + 5, getPtPos.y + 5);
		else if (getTypePos == 2)
			memDC.Ellipse(getPtPos.x - 5, getPtPos.y - 5, getPtPos.x + 5, getPtPos.y + 5);
		
		count++;
	}

	CBrush write = RGB(255, 255, 255);
	memDC.SelectObject(&write);
	memDC.Rectangle(eraserSPt.x, eraserSPt.y, eraserEPt.x, eraserEPt.y);

	CString num;
	num.Format(_T("출력된 점의 개수: %d"), count);
	memDC.TextOut(10, 10, num);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	pt.AddTail(point);
	Invalidate();
	mouseDown = true;
	if(rectDraw)
		ptType.AddTail(1);
	if(circleDraw)
		ptType.AddTail(2);
	if (onRed)
		ptColor.AddTail(RGB(255, 0, 0));
	if (onBlue)
		ptColor.AddTail(RGB(0, 0, 255));
	if (onGreen)
		ptColor.AddTail(RGB(0, 255, 0));
	if (onBlack)
		ptColor.AddTail(RGB(0, 0, 0));
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mouseDown = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	eraserSPt = point;
	onEraser = true;
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	eraserEPt = point;
	onEraser = false;

	if (eraserSPt.x > eraserEPt.x)
	{
		sPt.x = eraserEPt.x;
		ePt.x = eraserSPt.x;
	}
	if (eraserSPt.x < eraserEPt.x)
	{
		sPt.x = eraserSPt.x;
		ePt.x = eraserEPt.x;
	}
	if (eraserSPt.y > eraserEPt.y)
	{
		sPt.y = eraserEPt.y;
		ePt.y = eraserSPt.y;
	}
	if (eraserSPt.y < eraserEPt.y)
	{
		sPt.y = eraserSPt.y;
		ePt.y = eraserEPt.y;
	}

	POSITION pos = pt.GetHeadPosition();
	CPoint listPt;

	POSITION colorPos = ptColor.GetHeadPosition();
	POSITION typePos = ptType.GetHeadPosition();

	while (pos != NULL)
	{
		POSITION tempos = pos;
		POSITION colorTempos = colorPos;
		POSITION typeTempos = typePos;

		ptColor.GetNext(colorPos);
		ptType.GetNext(typePos);

		listPt = pt.GetNext(pos);
		if (sPt.x < listPt.x &&
			ePt.x > listPt.x && 
			sPt.y < listPt.y &&
			ePt.y > listPt.y)
		{
			pt.RemoveAt(tempos);
			ptColor.RemoveAt(colorTempos);
			ptType.RemoveAt(typeTempos);
		}
		
	}

	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (mouseDown)
	{
		pt.AddTail(point);
		if (rectDraw)
			ptType.AddTail(1);
		if (circleDraw)
			ptType.AddTail(2);
		if (onRed)
			ptColor.AddTail(RGB(255, 0, 0));
		if (onBlue)
			ptColor.AddTail(RGB(0, 0, 255));
		if (onGreen)
			ptColor.AddTail(RGB(0, 255, 0));
		if (onBlack)
			ptColor.AddTail(RGB(0, 0, 0));

		Invalidate();
	}

	if (onEraser)
	{
		eraserEPt = point;
		Invalidate();
	}

	

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	onBlue = true;
	onGreen = false;
	onRed = false;
	onBlack = false;
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	onGreen = true;
	onBlue = false;
	onRed = false;
	onBlack = false;
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기1 코드를 추가합니다.
	onRed = true;
	onBlue = false;
	onGreen = false;
	onBlack = false;
}

void CChildView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	onBlack = true;
	onRed = false;
	onBlue = false;
	onGreen = false;
	
}

void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if(onBlue)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);


}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (onGreen)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (onRed)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (onBlack)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnButton32774()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	rectDraw = true;
	circleDraw = false;
	

}


void CChildView::OnButton32775()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	rectDraw = false;
	circleDraw = true;
	

}


void CChildView::OnUpdateButton32774(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (rectDraw)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateButton32775(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (circleDraw)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnButton32778()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (onEraserMove)
	{
		onEraserMove = false;
		onRight = false;
		onLeft = false;
		onUp = false;
		onDown = false;
		return;
	}

	onEraserMove = true;

}


void CChildView::OnUpdateButton32778(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (onEraserMove)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nChar == VK_LEFT)
	{
		move.x = -10;
		move.y = 0;
	}
	if (nChar == VK_RIGHT)
	{
		move.x = 10;
		move.y = 0;
	}
	if (nChar == VK_UP)
	{
		move.x = 0;
		move.y = -10;
	}
	if (nChar == VK_DOWN)
	{
		move.x = 0;
		move.y = 10;
	}

	

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 50, NULL);

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);

	if (nIDEvent == 0)
	{
		if (onEraserMove)
		{
			if (rect.right < sPt.x || rect.left > sPt.x)
			{
				move.x = -move.x;
			}
			if (rect.top > sPt.y || rect.bottom < sPt.y)
			{
				move.y = -move.y;
			}
			sPt += move;
			ePt += move;

			eraserEPt += move;
			eraserSPt += move;

			POSITION pos = pt.GetHeadPosition();
			CPoint listPt;

			POSITION colorPos = ptColor.GetHeadPosition();
			POSITION typePos = ptType.GetHeadPosition();

			while (pos != NULL)
			{
				POSITION tempos = pos;
				POSITION colorTempos = colorPos;
				POSITION typeTempos = typePos;

				ptColor.GetNext(colorPos);
				ptType.GetNext(typePos);

				listPt = pt.GetNext(pos);
				if (sPt.x < listPt.x &&
					ePt.x > listPt.x &&
					sPt.y < listPt.y &&
					ePt.y > listPt.y)
				{
					pt.RemoveAt(tempos);
					ptColor.RemoveAt(colorTempos);
					ptType.RemoveAt(typeTempos);
				}

			}
			Invalidate();
		}
	}

	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*return CWnd::OnEraseBkgnd(pDC);*/

	return true;
}
