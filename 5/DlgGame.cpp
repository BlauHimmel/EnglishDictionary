// DlgGame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "5.h"
#include "DlgGame.h"
#include "afxdialogex.h"


// CDlgGame �Ի���

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
	cstrTemp.Format(_T("��ȷ:%d"), m_nCorrect);
	GetDlgItem(IDC_STATIC2)->SetWindowTextW(cstrTemp);
	cstrTemp.Format(_T("����:%d"), m_nWrong);
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


// CDlgGame ��Ϣ�������


void CDlgGame::OnBnClickedButton1()	//�ش�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	/*�ж�����*/
	if (m_cstrAnswer == m_cstrCurEng)
	{
		m_nCorrect++;
		CString cstrTemp;
		cstrTemp.Format(_T("��ȷ:%d"), m_nCorrect);
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(cstrTemp);
		cstrTemp.Format(_T("����:%d"), m_nWrong);
		GetDlgItem(IDC_STATIC3)->SetWindowTextW(cstrTemp);
		MessageBox(_T("�ش���ȷ��"), _T("��ʾ"), MB_OK);
	}
	else
	{
		m_nWrong++;
		CString cstrTemp;
		cstrTemp.Format(_T("��ȷ:%d"), m_nCorrect);
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(cstrTemp);
		cstrTemp.Format(_T("����:%d"), m_nWrong);
		GetDlgItem(IDC_STATIC3)->SetWindowTextW(cstrTemp);
		
		cstrTemp = "�ش������ȷ����:";
		cstrTemp.Append(m_cstrCurEng);

		MessageBox(cstrTemp, _T("��ʾ"), MB_OK);
	}

	m_cstrAnswer = "";

	/*�����´�*/
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


void CDlgGame::OnBnClickedButton10()	//�˳�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	double dAccuracy = ((double)m_nCorrect) / ((double)m_nCorrect + (double)m_nWrong);

	CString cstrTemp;
	cstrTemp.Format(_T("��ȷ��Ϊ%lf%%,"), dAccuracy * 100);

	if (dAccuracy > 0.9)
	{
		cstrTemp.Append(_T("�ǳ�����"));
	}
	else if (dAccuracy > 0.8)
	{
		cstrTemp.Append(_T("�����ԡ�"));
	}
	else if (dAccuracy > 0.6)
	{
		cstrTemp.Append(_T("һ�㡣"));
	}
	else
	{
		cstrTemp.Append(_T("Ҫ�ҿ��ˣ�"));
	}
	MessageBox(cstrTemp, _T("���"), MB_OK);

	CDlgGame::OnCancel();
}


void CDlgGame::OnBnClickedButton2()	//��ʾ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	pSpVoiceGame->Speak(m_cstrCurEng, SPF_DEFAULT, NULL);
}
