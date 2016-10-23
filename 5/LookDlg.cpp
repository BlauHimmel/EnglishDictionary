// LookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "5.h"
#include "LookDlg.h"
#include "afxdialogex.h"


// CLookDlg 对话框

IMPLEMENT_DYNAMIC(CLookDlg, CDialogEx)

CLookDlg::CLookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLookDlg::IDD, pParent)
{

}

BOOL CLookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	return TRUE;
}

void CLookDlg::ShowAllData()
{
	ifstream DataFileIn("DATA.data");
	ifstream IndexFileIn("Index.data", ios::binary);

	if (!DataFileIn || !IndexFileIn)
	{
		return;
	}

	IndexFileIn.seekg(0, ios::end);
	int nFileSize = (int)IndexFileIn.tellg() - 0;
	IndexFileIn.seekg(0, ios::beg);

	if (DataFileIn&&IndexFileIn)
	{
		int i = 0;
		int* nzIndex = new int[4];
		while (true)
		{
			/*
			0 nEngPos, 1 nEngLen, 2 nChPos, 3 nChLen
			*/
			if (!IndexFileIn.read((char*)nzIndex, 4 * sizeof(int)))
			{
				return;
			}

			char* lpszEngBuffer = new char[nzIndex[1]];
			char* lpszChBuffer = new char[nzIndex[3]];

			DataFileIn.seekg(nzIndex[0], ios::beg);
			DataFileIn.getline(lpszEngBuffer, nzIndex[1]);
			DataFileIn.seekg(nzIndex[2], ios::beg);
			DataFileIn.getline(lpszChBuffer, nzIndex[3]);

			CString cstrEng(lpszEngBuffer);
			CString cstrCh(lpszChBuffer);

			m_listbLook.InsertString(i,cstrEng);
			m_listbLook.InsertString(i + 1, cstrCh);
			i += 2;

			delete[] lpszEngBuffer;
			delete[] lpszChBuffer;

			if ((int)IndexFileIn.tellg() == nFileSize)
			{
				break;
			}
		}
		delete[] nzIndex;
	}
	DataFileIn.close();
	IndexFileIn.close();
}

CLookDlg::~CLookDlg()
{
}

void CLookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbLook);
}


BEGIN_MESSAGE_MAP(CLookDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLookDlg::OnBnClickedButton_DISPLAY)
END_MESSAGE_MAP()


// CLookDlg 消息处理程序


void CLookDlg::OnBnClickedButton_DISPLAY()
{
	// TODO:  在此添加控件通知处理程序代码
	ShowAllData();
	if (m_listbLook.GetCount() == 0)
	{
		MessageBox(_T("你还没导入文件！"), _T("提示"), MB_OK);
		return;
	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	/*CString cstrSum;
	cstrSum.Format(_T("单词总数为：%d"), m_listbLook.GetCount() / 2);*/
}
