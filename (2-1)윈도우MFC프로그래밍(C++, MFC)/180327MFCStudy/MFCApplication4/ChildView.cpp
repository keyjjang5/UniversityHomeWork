
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication4.h"
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
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
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
	
	/*for (int i = 0; i < 10; i++)
	{
		dc.Rectangle((200+i*10), (200+i*10), (400-i*10), (400-i*10));
	}*/
	//180319
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	/*dc.SetPixel(100, 100, RGB(0,0,100));
	dc.SetPixelV(100, 200, 0x000000FF);*/

	/*int r = 127;
	for (int x = 0; x < 256; x++)
	{
		for (int y = 0; y < 256; y++)
		{
			if ((x - r)*(x - r) + (y - r)*(y - r) < r*r)
			{
				dc.SetPixel(x, y, RGB(0, x, y));
			}
		}
	}*/

	/*CRect rect;
	GetClientRect(rect);
	dc.Ellipse(rect);*/
	//180327

	//dc.MoveTo(100, 100);
	//dc.LineTo(200, 200);
	//dc.LineTo(300, 400);
	//dc.MoveTo(500, 500);
	//dc.LineTo(400, 400);

	//dc.SetTextColor(RGB(255, 0, 0));
	//dc.SetBkColor(RGB(0, 255, 0));
	//dc.SetTextAlign(TA_CENTER);
	//dc.TextOutW(300, 200, _T("Hello MFC"));

	//CRect rect;
	//GetClientRect(rect);
	//dc.SetTextColor(RGB(0, 255, 0));
	//dc.SetBkColor(RGB(255, 0, 0));
	//dc.TextOutW(rect.Width()/2, rect.Height()/2, _T("hi MFC"));

	//dc.Rectangle(0, 0, 500, 500);
	//dc.SetMapMode(MM_LOMETRIC);//mm������ �ٲ�
	//dc.Rectangle(0, 0, 500, -500);
	//POINT p;
	//p.x = 500; p.y = -500;
	//dc.LPtoDP(&p);
	//dc.SetMapMode(MM_TEXT);
	//dc.Rectangle(0, 0, p.x / 2, p.y / 2);

	//CPen pen(PS_SOLID, 2, RGB(255, 0, 0));

	//dc.SelectObject(&pen);
	//dc.Rectangle(50, 50, 150, 150);
	//dc.Ellipse(50, 50, 150, 150);
	//
	//CPen pen2(PS_SOLID, 1, RGB(0, 0, 255));
	//CPen *pOldPen = dc.SelectObject(&pen2);
	//dc.Rectangle(200, 50, 300, 150);
	//dc.SelectObject(pOldPen);
	//dc.Ellipse(200, 50, 300, 150);

	//CBrush brush(RGB(0, 0, 255));
	//dc.SelectObject(&brush);
	//dc.Rectangle(150, 150, 250, 250);
	//dc.Ellipse(150, 150, 250, 250);

	//CBrush brush2(RGB(255, 0, 0));
	//CBrush *pOldBrush = dc.SelectObject(&brush2);
	//dc.Rectangle(250, 250, 350, 350);
	//dc.SelectObject(pOldBrush);
	//dc.Ellipse(250, 250, 350, 350);

	//CFont font;
	//font.CreatePointFont(200, _T("�ü�"));
	//dc.SelectObject(&font);
	//dc.TextOutW(50, 500, _T("���̿�"));

	//CPoint pt1;
	//pt1.x = 100;
	//pt1.y = 200;
	//CPoint pt2(300, 200);
	//CPoint pt3;
	//pt3 = pt2;
	//CPoint pt4(pt1);

	//CRgn rgn;
	//CPoint ptVertex[5];
	//ptVertex[0] = CPoint(180, 80);
	//ptVertex[1] = CPoint(100, 160);
	//ptVertex[2] = CPoint(120, 260);
	//ptVertex[3] = CPoint(240, 260);
	//ptVertex[4] = CPoint(260, 160);

	//rgn.CreatePolygonRgn(ptVertex, 5, ALTERNATE);
	//CBrush brush3(RGB(0, 0, 255));
	//dc.SelectObject(&brush3);
	//dc.PaintRgn(&rgn);
	////���� ���ٰ� �Ʒ������� ���� �ǹ�
	////dc.FillRgn(&rgn, &brush);

	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP1);
	//CBrush brush5(&bitmap);
	//dc.SelectObject(&brush5);
	//dc.Rectangle(0, 0, 200, 200);
	//180329

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	/*for (int i = 0; i < 10; i++)
	{
		dc.Ellipse((300 + i * 10), (300 + i * 10), (500 - i * 10), (500 - i * 10));
	}*/
	//180322
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);

	/*dc.Rectangle(point.x + 50, point.y - 50, point.x - 50, point.y + 50);*/
	//180327

	CWnd::OnRButtonDown(nFlags, point);
}
