
// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "MFCFinalExample2.h"
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
	ON_COMMAND(ID_32771, &CChildView::On32771)
	ON_COMMAND(ID_32772, &CChildView::On32772)
	ON_COMMAND(ID_32773, &CChildView::On32773)
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
	POSITION ptPos = ptList.GetHeadPosition();

	while (ptPos != NULL)
	{
		CPoint pt = ptList.GetNext(ptPos);

		dc.Ellipse(pt.x - 10, pt.y - 10, pt.x + 10, pt.y + 10);
	}
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ptList.AddTail(point);
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::On32771()//���θ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ptList.RemoveAll();
	Invalidate();
}


void CChildView::On32772()//����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFile file(_T("SaveData.dat"), CFile::modeCreate | CFile::modeWrite);

	CArchive ar(&file, CArchive::store);
	ptList.Serialize(ar);

}


void CChildView::On32773()//����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
