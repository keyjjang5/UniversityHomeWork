
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "MFCFinalExample3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32771, &CChildView::On32771)
	ON_COMMAND(ID_32772, &CChildView::On32772)
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
	POSITION typePos = ptType.GetHeadPosition();
	POSITION listPos = ptList.GetHeadPosition();
	int type;

	for (int i = 0; i < count; i++)
	{
		type = ptType.GetNext(typePos);
		if (type == 1)
		{
			CPoint pt = ptList.GetNext(listPos);
			CBrush rBrush(RGB(255, 0, 0));
			dc.SelectObject(&rBrush);
			dc.Ellipse(pt.x - 10, pt.y - 10, pt.x + 10, pt.y + 10);
		}
		else if (type == 2)
		{
			CPoint pt = ptList.GetNext(listPos);
			CBrush bBrush(RGB(0, 0, 255));
			dc.SelectObject(&bBrush);
			dc.Rectangle(pt.x - 10, pt.y - 10, pt.x + 10, pt.y + 10);
		}
	}

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ptList.AddTail(point);
	ptType.AddTail(1);
	count++;
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ptList.AddTail(point);
	ptType.AddTail(2);
	count++;
	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::On32771()//����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFile file(_T("SaveData.dat"), CFile::modeCreate | CFile::modeWrite);

	CArchive ar(&file, CArchive::store);
	ptList.Serialize(ar);
	ptType.Serialize(ar);
}


void CChildView::On32772()//����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ptList.RemoveAll();
	ptType.RemoveAll();

	CFile file;
	CFileException e;
	if (!file.Open(_T("SaveData.dat"), CFile::modeRead, &e))
	{
		e.ReportError();
		return;
	}

	CArchive ar(&file, CArchive::load);
	ptList.Serialize(ar);
	ptType.Serialize(ar);

	Invalidate();
}
