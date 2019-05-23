
// ChildView.cpp : CChildView Ŭ������ ����
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
	CRect rect;
	GetClientRect(rect);
	CDC memDC; // ���� DC
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; // �׸��� ������ ���� ���� 
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

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	radioRect.Create(_T("�簢��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		CRect(0, 0, 80, 30), this, 101);
	radioCircle.Create(_T("��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
