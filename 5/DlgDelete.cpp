// DlgDelete.cpp : 实现文件
//

#include "stdafx.h"
#include "5.h"
#include "DlgDelete.h"
#include "afxdialogex.h"


// CDlgDelete 对话框

IMPLEMENT_DYNAMIC(CDlgDelete, CDialogEx)

CDlgDelete::CDlgDelete(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDelete::IDD, pParent)
	, m_cstrEng(_T(""))
{

}

CDlgDelete::~CDlgDelete()
{
}

void CDlgDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cstrEng);
}


BEGIN_MESSAGE_MAP(CDlgDelete, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgDelete::OnBnClickedButton_DELETE)
END_MESSAGE_MAP()


// CDlgDelete 消息处理程序


void CDlgDelete::OnBnClickedButton_DELETE()	
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	char* lpszEngBuffer = CStringToChar(m_cstrEng);
	if (g_CTrie.Delete(lpszEngBuffer))
	{
		MessageBox(_T("删除成功！"), _T("提示"), MB_OK);
	}
	else
	{
		MessageBox(_T("删除失败！"), _T("提示"), MB_OK);
	}
	delete[] lpszEngBuffer;
	UpdateData(false);
	CDlgDelete::OnCancel();
}
