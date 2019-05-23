// MeDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCFInalExample7.h"
#include "MeDialog.h"
#include "afxdialogex.h"
#include "ChildView.h"


// MeDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(MeDialog, CDialog)

MeDialog::MeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{
	
	i = 0;
	count = 0;
}

MeDialog::~MeDialog()
{
	
}

void MeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, oneButton);
	DDX_Control(pDX, IDC_BUTTON2, twoButton);
	DDX_Control(pDX, IDC_BUTTON3, ThreeButton);
	DDX_Control(pDX, IDC_BUTTON4, plusButton);
	DDX_Control(pDX, IDC_BUTTON5, minusButton);
	DDX_Control(pDX, IDC_BUTTON6, eqaulButton);
	DDX_Control(pDX, IDC_BUTTON7, clearButton);
}


BEGIN_MESSAGE_MAP(MeDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MeDialog::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MeDialog::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MeDialog::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MeDialog::OnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &MeDialog::OnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &MeDialog::OnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &MeDialog::OnClickedButton7)
	ON_BN_CLICKED(IDOK, &MeDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// MeDialog 메시지 처리기입니다.


void MeDialog::OnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	i = i * 10 + 1;
	
	str[count].Format(_T("%d"), i);

	pass.Empty();
	for (int k = 0; k < count + 1; k++)
	{
		pass += str[k];
	}
	view->str = pass;

	view->Invalidate();
}


void MeDialog::OnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	i = i * 10 + 2;
	str[count].Format(_T("%d"), i);

	pass.Empty();
	for (int k = 0; k < count + 1; k++)
	{
		pass += str[k];
	}
	view->str = pass;
	view->Invalidate();
}


void MeDialog::OnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	i = i * 10 + 3;
	str[count].Format(_T("%d"), i);

	pass.Empty();
	for (int k = 0; k < count + 1; k++)
	{
		pass += str[k];
	}
	view->str = pass;
	view->Invalidate();
}


void MeDialog::OnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	count++;
	str[count] = '+';

	pass.Empty();
	for (int k = 0; k < count + 1; k++)
	{
		pass += str[k];
	}
	view->str = pass;

	i = 0;

	count++;
	view->Invalidate();
}


void MeDialog::OnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	count++;
	str[count] = '-';

	pass.Empty();
	for (int k = 0; k < count + 1; k++)
	{
		pass += str[k];
	}
	view->str = pass;

	i = 0;

	count++;
	view->Invalidate();
}


void MeDialog::OnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	count++;
	str[count] = '=';

	pass.Empty();
	for (int k = 0; k < count + 1; k++)
	{
		pass += str[k];
	}
	

	i = 0;
	int sum = 0;
	int k = 0;

	sum = _ttoi(str[0]);
	while (1)
	{
		if (str[k] == '+')
		{
			sum += _ttoi(str[k+1]);
		}
		else if (str[k] == '-')
		{
			sum -= _ttoi(str[k+1]);
		}
		else if (str[k] == '=')
		{
			sumpass.Format(_T("%d"), sum);
			view->str = pass + sumpass;
			
			break;
		}
		
		k++;
	}
	count++;
	view->Invalidate();
}


void MeDialog::OnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	view->str.Empty();
	for (int k = 0; k < 100; k++)
	{
		str[k].Empty();
	}
	i = 0;
	count = 0;
	view->Invalidate();
}


void MeDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();

	CDialog::OnOK();
}
