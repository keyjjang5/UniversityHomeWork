// MyDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication8.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// CMyDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editTest);
	//DDX_Control(pDX, IDC_BUTTON1, buttonTest);
	DDX_Control(pDX, IDC_RADIO1, radioTest[0]);
	DDX_Control(pDX, IDC_RADIO2, radioTest[1]);
	DDX_Control(pDX, IDC_RADIO3, radioTest[2]);
	

	DDX_Text(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_COMMAND(IDC_RADIO1, &CMyDialog::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &CMyDialog::OnRadio2)
	ON_COMMAND(IDC_RADIO3, &CMyDialog::OnRadio3)
END_MESSAGE_MAP()


// CMyDialog 메시지 처리기입니다.


BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMyDialog::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	for (int i = 0;i < 3;i++)
	{
		if (radioTest[i].GetCheck())
		{
			m_color = i;
		}
	}

	CDialog::OnOK();
}


void CMyDialog::OnRadio1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMyDialog::OnRadio2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMyDialog::OnRadio3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
