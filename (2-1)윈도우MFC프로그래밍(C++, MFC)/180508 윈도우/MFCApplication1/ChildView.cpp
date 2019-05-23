
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	color = RGB(255, 255, 255);
	corR = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_COMMAND(ID_BUTTON32778, &CChildView::OnButton32778)
	ON_COMMAND(ID_BUTTON32779, &CChildView::OnButton32779)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_LOAD, &CChildView::OnFileLoad)
	ON_COMMAND(ID_FILE_SAVE32780, &CChildView::OnFileSave32780)
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
	/*CPoint pt(200, 200);
	CBrush brush = color;
	dc.SelectObject(&brush);
	if (corR)
	{
		dc.Ellipse(pt.x - 25, pt.y - 25, pt.x + 25, pt.y + 25);
	}
	else if (!corR)
	{
		dc.Rectangle(pt.x - 25, pt.y - 25, pt.x + 25, pt.y + 25);
	}*/

	
	/*CStdioFile file1;
	file1.Open(_T("test1.txt"), CFile::modeRead);
	CStdioFile file2;
	file2.Open(_T("test2.txt"), CFile::modeWrite | CFile::modeCreate);
	CString str;
	while (file1.ReadString(str))
	{
		str.MakeUpper();
		file2.WriteString(str + "\n");
	}*/
	//CFile file;
	//CFileException e;
	//if (!file.Open(_T("mytest.dat"),
	//	CFile::modeReadWrite | CFile::modeCreate, &e))
	//{
	//	e.ReportError();
	//	return;
	//}
	//int a = 100;
	//int b = 200;
	///*file.Write(&a, sizeof(a));
	//file.Write(&b, sizeof(b));*/
	//CArchive ar(&file, CArchive::store);
	//ar << a << b;
	/*CRect rect;
	GetClientRect(&rect);
	dc.DrawText(str, &rect, DT_LEFT);*/
	ptPos = ptList.GetHeadPosition();
	while (ptPos != NULL)
	{
		CPoint pt = ptList.GetNext(ptPos);
		dc.Ellipse(pt.x - 50, pt.y - 50, pt.x + 50, pt.y + 50);
	}

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	

	return 0;
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu* pMenu = menu.GetSubMenu(4);
	pMenu->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(0, 255, 0);
	Invalidate();
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CChildView::OnButton32778()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	/*corR = true;
	Invalidate();*/
}


void CChildView::OnButton32779()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	/*corR = false;
	Invalidate();*/
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*CString str;
	str.Format(_T("Mouse Position(%d, %d)"), point.x, point.y);
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->m_wndStatusBar.SetPaneText(2, str);*/

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*CFile file(_T("test.dat"), CFile::modeCreate | CFile::modeWrite);
	int a = 30;
	float b = 20.0f;
	file.Write(&a, sizeof(a));
	file.Write(&b, sizeof(b));
	file.Close();*/

	ptList.AddTail(point);
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*CFile file2;
	CFileException e;
	if (!file2.Open(_T("test.dat"), CFile::modeRead, &e))
	{
		e.ReportError();
		return;
	};
	int a2;
	float b2;
	file2.Read(&a2, sizeof(a2));
	file2.Read(&b2, sizeof(b2));

	CString str;
	str.Format(_T("a=%d b=%.1f"), a2, b2);
	AfxMessageBox(str);
	file2.Close();*/

	/*CFile file;
	CFileException e;
	if (!file.Open(_T("mytest.dat"), CFile::modeRead, &e))
	{
		e.ReportError();
		return;
	}
	CArchive ar(&file, CArchive::load);
	ar >> str;*/

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*str += (TCHAR)nChar;
	Invalidate();*/
	

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnFileLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file2(_T("count.txt"), CFile::modeRead);
	int count = 0;
	file2.Read(&count, sizeof(int));
	file2.Close();
	CFile file(_T("circlePos.txt"), CFile::modeRead);
	for (int i = 0;i < count;i++)
	{
		CPoint pt;
		file.Read(&pt, sizeof(CPoint));
		ptList.AddTail(pt);
	}
	file.Close();
	Invalidate();
}


void CChildView::OnFileSave32780()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file(_T("circlePos.txt"), CFile::modeCreate | CFile::modeWrite);
	
	POSITION pos = ptList.GetHeadPosition();
	int count = 0;

	while (pos != NULL)
	{
		CPoint pt = ptList.GetNext(pos);
		file.Write(&pt, sizeof(CPoint));
		count++;
	}
	file.Close();
	
	CFile file2(_T("count.txt"), CFile::modeCreate | CFile::modeWrite);
	file2.Write(&count, sizeof(int));
	file2.Close();
}
