
// ChildView.cpp : CChildView Ŭ������ ����
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

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	

	return 0;
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu* pMenu = menu.GetSubMenu(4);
	pMenu->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());
}


void CChildView::OnColorBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = RGB(0, 255, 0);
	Invalidate();
}


void CChildView::OnColorRed()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CChildView::OnButton32778()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	/*corR = true;
	Invalidate();*/
}


void CChildView::OnButton32779()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	/*corR = false;
	Invalidate();*/
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	/*CString str;
	str.Format(_T("Mouse Position(%d, %d)"), point.x, point.y);
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->m_wndStatusBar.SetPaneText(2, str);*/

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	/*str += (TCHAR)nChar;
	Invalidate();*/
	

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnFileLoad()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
