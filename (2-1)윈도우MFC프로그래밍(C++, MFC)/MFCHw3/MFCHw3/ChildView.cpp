
// ChildView.cpp : CChildView Ŭ������ ����
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
	int count = 0;

	ptPos = pt.GetHeadPosition();
	typePos = ptType.GetHeadPosition();
	colorPos = ptColor.GetHeadPosition();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.



	CRect rect;
	GetClientRect(rect);
	CDC memDC; // ���� DC
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; // �׸��� ������ ���� ���� 
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
	num.Format(_T("��µ� ���� ����: %d"), count);
	memDC.TextOut(10, 10, num);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	mouseDown = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	eraserSPt = point;
	onEraser = true;
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	onBlue = true;
	onGreen = false;
	onRed = false;
	onBlack = false;
}


void CChildView::OnColorGreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	onGreen = true;
	onBlue = false;
	onRed = false;
	onBlack = false;
}


void CChildView::OnColorRed()
{
	// TODO: ���⿡ ��� ó����1 �ڵ带 �߰��մϴ�.
	onRed = true;
	onBlue = false;
	onGreen = false;
	onBlack = false;
}

void CChildView::OnColorBlack()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	onBlack = true;
	onRed = false;
	onBlue = false;
	onGreen = false;
	
}

void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if(onBlue)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);


}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (onGreen)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (onRed)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (onBlack)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnButton32774()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	rectDraw = true;
	circleDraw = false;
	

}


void CChildView::OnButton32775()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	rectDraw = false;
	circleDraw = true;
	

}


void CChildView::OnUpdateButton32774(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (rectDraw)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateButton32775(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (circleDraw)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnButton32778()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (onEraserMove)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	/*return CWnd::OnEraseBkgnd(pDC);*/

	return true;
}
