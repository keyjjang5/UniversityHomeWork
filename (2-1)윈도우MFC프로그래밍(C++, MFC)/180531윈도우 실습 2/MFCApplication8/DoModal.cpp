// DoModal.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication8.h"
#include "DoModal.h"
#include "afxdialogex.h"


// DoModal ��ȭ �����Դϴ�.

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


// DoModal �޽��� ó�����Դϴ�.


BOOL DoModal::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void DoModal::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialog::OnOK();
}


void DoModal::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialog::OnCancel();
}
