// DlgInsert.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "5.h"
#include "DlgInsert.h"
#include "afxdialogex.h"


// CDlgInsert �Ի���

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


// CDlgInsert ��Ϣ�������


void CDlgInsert::OnBnClickedButton_INSERT()	//����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	char* lpszEngBuffer = CStringToChar(m_cstrEng);
	char* lpszChBuffer = CStringToChar(m_cstrCh);

	for (int i = 0; i < m_cstrEng.GetLength(); i++)
	{
		if (!((m_cstrEng[i] >= 'A'&&m_cstrEng[i] <= 'Z') || (m_cstrEng[i] >= 'a'&&m_cstrEng[i] <= 'z')))
		{
			MessageBox(_T("��������ȷ�����ݣ�"), _T("��ʾ"), MB_OK);
			delete[] lpszEngBuffer;
			delete[] lpszChBuffer;
			return;
		}
	}

	if (g_CTrie.Insert(lpszEngBuffer, lpszChBuffer))
	{
		MessageBox(_T("����ɹ���"), _T("��ʾ"), MB_OK);
	}
	else
	{
		MessageBox(_T("����ʧ�ܣ�"), _T("��ʾ"), MB_OK);
	}

	delete[] lpszEngBuffer;
	delete[] lpszChBuffer;

	UpdateData(false);
	CDlgInsert::OnCancel();
}
