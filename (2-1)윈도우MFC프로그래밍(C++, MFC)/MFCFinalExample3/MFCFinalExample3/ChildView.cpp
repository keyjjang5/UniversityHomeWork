
// ChildView.cpp : CChildView 클래스의 구현
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

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ptList.AddTail(point);
	ptType.AddTail(1);
	count++;
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ptList.AddTail(point);
	ptType.AddTail(2);
	count++;
	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::On32771()//저장
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file(_T("SaveData.dat"), CFile::modeCreate | CFile::modeWrite);

	CArchive ar(&file, CArchive::store);
	ptList.Serialize(ar);
	ptType.Serialize(ar);
}


void CChildView::On32772()//열기
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
