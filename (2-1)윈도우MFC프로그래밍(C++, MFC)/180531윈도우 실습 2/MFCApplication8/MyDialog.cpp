// MyDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication8.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// CMyDialog ��ȭ �����Դϴ�.

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


// CMyDialog �޽��� ó�����Դϴ�.


BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMyDialog::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMyDialog::OnRadio2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMyDialog::OnRadio3()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
