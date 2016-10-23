// DlgDelete.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "5.h"
#include "DlgDelete.h"
#include "afxdialogex.h"


// CDlgDelete �Ի���

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


// CDlgDelete ��Ϣ�������


void CDlgDelete::OnBnClickedButton_DELETE()	
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	char* lpszEngBuffer = CStringToChar(m_cstrEng);
	if (g_CTrie.Delete(lpszEngBuffer))
	{
		MessageBox(_T("ɾ���ɹ���"), _T("��ʾ"), MB_OK);
	}
	else
	{
		MessageBox(_T("ɾ��ʧ�ܣ�"), _T("��ʾ"), MB_OK);
	}
	delete[] lpszEngBuffer;
	UpdateData(false);
	CDlgDelete::OnCancel();
}
