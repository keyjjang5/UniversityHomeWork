// MeDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCFinalExample6.h"
#include "MeDialog.h"
#include "afxdialogex.h"


// MeDialog 대화 상자입니다.

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
	DDX_Control(pDX, IDC_EDIT2, mainEdit);
	DDX_Control(pDX, IDC_EDIT1, rEdit);
	DDX_Control(pDX, IDC_EDIT3, gEdit);
	DDX_Control(pDX, IDC_EDIT4, bEdit);
	DDX_Text(pDX, IDC_EDIT2, str);
	DDX_Text(pDX, IDC_EDIT1, rp);
	DDX_Text(pDX, IDC_EDIT3, gp);
	DDX_Text(pDX, IDC_EDIT4, bp);
}


BEGIN_MESSAGE_MAP(MeDialog, CDialog)
END_MESSAGE_MAP()


// MeDialog 메시지 처리기입니다.
