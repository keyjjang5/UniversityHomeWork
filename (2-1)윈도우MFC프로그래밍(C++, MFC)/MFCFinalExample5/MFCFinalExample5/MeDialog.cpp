// MeDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCFinalExample5.h"
#include "MeDialog.h"
#include "afxdialogex.h"


// MeDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(MeDialog, CDialog)

MeDialog::MeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

MeDialog::~MeDialog()
{
}

void MeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editButton);
	DDX_Text(pDX, IDC_EDIT1, str);
}


BEGIN_MESSAGE_MAP(MeDialog, CDialog)
END_MESSAGE_MAP()


// MeDialog �޽��� ó�����Դϴ�.
