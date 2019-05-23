// DoModal.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication8.h"
#include "DoModal.h"
#include "afxdialogex.h"


// DoModal 대화 상자입니다.

IMPLEMENT_DYNAMIC(DoModal, CDialog)

DoModal::DoModal(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

DoModal::~DoModal()
{
}

void DoModal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DoModal, CDialog)
END_MESSAGE_MAP()


// DoModal 메시지 처리기입니다.


BOOL DoModal::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DoModal::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialog::OnOK();
}


void DoModal::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialog::OnCancel();
}
