// CMainDialog.cpp: 实现文件
//

#include "pch.h"
#include "MfcDll.h"
#include "afxdialogex.h"
#include "CMainDialog.h"


// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

CMainDialog::CMainDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMainDialog 消息处理程序


void CMainDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMainDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}
