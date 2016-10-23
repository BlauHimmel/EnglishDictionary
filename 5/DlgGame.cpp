// DlgGame.cpp : 实现文件
//

#include "stdafx.h"
#include "5.h"
#include "DlgGame.h"
#include "afxdialogex.h"


// CDlgGame 对话框

IMPLEMENT_DYNAMIC(CDlgGame, CDialogEx)

CDlgGame::CDlgGame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgGame::IDD, pParent)
	, m_cstrAnswer(_T(""))
{
	m_nCorrect = 0;
	m_nWrong = 0;
}

CDlgGame::~CDlgGame()
{
}

CIndexInfo* CDlgGame::GetIndexRandomly()
{
	srand(time(0));
	
	ifstream IndexFileIn("Index.data", ios::binary);
	IndexFileIn.seekg(0, ios::end);
	int nFileSize = IndexFileIn.tellg();
	IndexFileIn.seekg(0, ios::beg);

	int nFilePointer = (rand() % (nFileSize / (4 * sizeof(int))))*(4 * sizeof(int));

	IndexFileIn.seekg(nFilePointer, ios::beg);

	int nzBuffer[4];
	IndexFileIn.read((char*)&nzBuffer[0], sizeof(int));
	IndexFileIn.read((char*)&nzBuffer[1], sizeof(int));
	IndexFileIn.read((char*)&nzBuffer[2], sizeof(int));
	IndexFileIn.read((char*)&nzBuffer[3], sizeof(int));

	CIndexInfo* pIndex = new CIndexInfo(nzBuffer[0], nzBuffer[1], nzBuffer[2], nzBuffer[3]);

	IndexFileIn.close();
	return pIndex;
}

void CDlgGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cstrAnswer);
}

BOOL CDlgGame::OnInitDialog()
{
	CString cstrTemp;
	cstrTemp.Format(_T("正确:%d"), m_nCorrect);
	GetDlgItem(IDC_STATIC2)->SetWindowTextW(cstrTemp);
	cstrTemp.Format(_T("错误:%d"), m_nWrong);
	GetDlgItem(IDC_STATIC3)->SetWindowTextW(cstrTemp);

	CIndexInfo* pIndex = GetIndexRandomly();
	ifstream DataFileIn("DATA.data");
	
	char* lpszEngBuffer = new char[pIndex->nEngLen];
	char* lpszChBuffer = new char[pIndex->nChLen];
	
	DataFileIn.seekg(pIndex->nEngPos, ios::beg);
	DataFileIn.getline(lpszEngBuffer, pIndex->nEngLen);
	DataFileIn.seekg(pIndex->nChPos, ios::beg);
	DataFileIn.getline(lpszChBuffer, pIndex->nChLen);
	
	CString cstrCh(lpszChBuffer);
	CString cstrEng(lpszEngBuffer);

	m_cstrCurEng = cstrEng;
	m_cstrCurCh = cstrCh;

	GetDlgItem(IDC_STATIC1)->SetWindowTextW(cstrCh);
	
	::CoInitialize(NULL);
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoiceGame);

	DataFileIn.close();
	delete[] lpszChBuffer;
	delete[] lpszEngBuffer;
	delete[] pIndex;
	return TRUE;
}

void CDlgGame::OnCancel()
{
	pSpVoiceGame->Release();
	::CoUninitialize();
	CDialog::OnCancel();
}


BEGIN_MESSAGE_MAP(CDlgGame, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGame::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgGame::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgGame::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgGame 消息处理程序


void CDlgGame::OnBnClickedButton1()	//回答
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);

	/*判断正误*/
	if (m_cstrAnswer == m_cstrCurEng)
	{
		m_nCorrect++;
		CString cstrTemp;
		cstrTemp.Format(_T("正确:%d"), m_nCorrect);
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(cstrTemp);
		cstrTemp.Format(_T("错误:%d"), m_nWrong);
		GetDlgItem(IDC_STATIC3)->SetWindowTextW(cstrTemp);
		MessageBox(_T("回答正确！"), _T("提示"), MB_OK);
	}
	else
	{
		m_nWrong++;
		CString cstrTemp;
		cstrTemp.Format(_T("正确:%d"), m_nCorrect);
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(cstrTemp);
		cstrTemp.Format(_T("错误:%d"), m_nWrong);
		GetDlgItem(IDC_STATIC3)->SetWindowTextW(cstrTemp);
		
		cstrTemp = "回答错误！正确答案是:";
		cstrTemp.Append(m_cstrCurEng);

		MessageBox(cstrTemp, _T("提示"), MB_OK);
	}

	m_cstrAnswer = "";

	/*生成新词*/
	CIndexInfo* pIndex = GetIndexRandomly();
	ifstream DataFileIn("DATA.data");

	char* lpszEngBuffer = new char[pIndex->nEngLen];
	char* lpszChBuffer = new char[pIndex->nChLen];

	DataFileIn.seekg(pIndex->nEngPos, ios::beg);
	DataFileIn.getline(lpszEngBuffer, pIndex->nEngLen);
	DataFileIn.seekg(pIndex->nChPos, ios::beg);
	DataFileIn.getline(lpszChBuffer, pIndex->nChLen);

	CString cstrCh(lpszChBuffer);
	CString cstrEng(lpszEngBuffer);

	m_cstrCurEng = cstrEng;
	m_cstrCurCh = cstrCh;

	GetDlgItem(IDC_STATIC1)->SetWindowTextW(cstrCh);

	DataFileIn.close();
	delete[] lpszChBuffer;
	delete[] lpszEngBuffer;
	delete[] pIndex;

	UpdateData(false);
}


void CDlgGame::OnBnClickedButton10()	//退出
{
	// TODO:  在此添加控件通知处理程序代码
	double dAccuracy = ((double)m_nCorrect) / ((double)m_nCorrect + (double)m_nWrong);

	CString cstrTemp;
	cstrTemp.Format(_T("正确率为%lf%%,"), dAccuracy * 100);

	if (dAccuracy > 0.9)
	{
		cstrTemp.Append(_T("非常不错！"));
	}
	else if (dAccuracy > 0.8)
	{
		cstrTemp.Append(_T("还可以。"));
	}
	else if (dAccuracy > 0.6)
	{
		cstrTemp.Append(_T("一般。"));
	}
	else
	{
		cstrTemp.Append(_T("要挂科了！"));
	}
	MessageBox(cstrTemp, _T("结果"), MB_OK);

	CDlgGame::OnCancel();
}


void CDlgGame::OnBnClickedButton2()	//提示
{
	// TODO:  在此添加控件通知处理程序代码
	pSpVoiceGame->Speak(m_cstrCurEng, SPF_DEFAULT, NULL);
}
