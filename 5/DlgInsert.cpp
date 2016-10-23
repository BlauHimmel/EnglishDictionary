// DlgInsert.cpp : 实现文件
//

#include "stdafx.h"
#include "5.h"
#include "DlgInsert.h"
#include "afxdialogex.h"


// CDlgInsert 对话框

IMPLEMENT_DYNAMIC(CDlgInsert, CDialogEx)

CDlgInsert::CDlgInsert(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInsert::IDD, pParent)
	, m_cstrEng(_T(""))
	, m_cstrCh(_T(""))
{

}

CDlgInsert::~CDlgInsert()
{
}

void CDlgInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cstrEng);
	DDX_Text(pDX, IDC_EDIT2, m_cstrCh);
}


BEGIN_MESSAGE_MAP(CDlgInsert, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInsert::OnBnClickedButton_INSERT)
END_MESSAGE_MAP()


// CDlgInsert 消息处理程序


void CDlgInsert::OnBnClickedButton_INSERT()	//插入
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	char* lpszEngBuffer = CStringToChar(m_cstrEng);
	char* lpszChBuffer = CStringToChar(m_cstrCh);

	for (int i = 0; i < m_cstrEng.GetLength(); i++)
	{
		if (!((m_cstrEng[i] >= 'A'&&m_cstrEng[i] <= 'Z') || (m_cstrEng[i] >= 'a'&&m_cstrEng[i] <= 'z')))
		{
			MessageBox(_T("请输入正确的数据！"), _T("提示"), MB_OK);
			delete[] lpszEngBuffer;
			delete[] lpszChBuffer;
			return;
		}
	}

	if (g_CTrie.Insert(lpszEngBuffer, lpszChBuffer))
	{
		MessageBox(_T("插入成功！"), _T("提示"), MB_OK);
	}
	else
	{
		MessageBox(_T("插入失败！"), _T("提示"), MB_OK);
	}

	delete[] lpszEngBuffer;
	delete[] lpszChBuffer;

	UpdateData(false);
	CDlgInsert::OnCancel();
}
