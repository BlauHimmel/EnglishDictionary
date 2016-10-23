
// 5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "5.h"
#include "5Dlg.h"
#include "LookDlg.h"
#include "DlgInsert.h"
#include "DlgDelete.h"
#include "DlgGame.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_KEYUP()
END_MESSAGE_MAP()


// CMy5Dlg 对话框



CMy5Dlg::CMy5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy5Dlg::IDD, pParent)
	, m_cstrInput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listbDisplay);
	DDX_Text(pDX, IDC_EDIT1, m_cstrInput);
	DDX_Control(pDX, IDC_LIST1, m_lisbResult);
}

BEGIN_MESSAGE_MAP(CMy5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON8, &CMy5Dlg::OnBnClickedButton_LOAD)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy5Dlg::OnBnClickedButton_LOOK)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy5Dlg::OnBnClickedButton_INSERT)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy5Dlg::OnBnClickedButton_DELETE)
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy5Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy5Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy5Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &CMy5Dlg::OnBnClickedButton9)
	ON_EN_UPDATE(IDC_EDIT1, &CMy5Dlg::OnUpdateEdit1)
END_MESSAGE_MAP()


// CMy5Dlg 消息处理程序

void CMy5Dlg::OnCancel()
{
	pSpVoice->Release();
	::CoUninitialize();
	CDialog::OnCancel();
}

BOOL CMy5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	g_CTrie.Init();
	Lock = false;
	m_listbDisplay.SetHorizontalExtent(300);

	::CoInitialize(NULL);         
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoice);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy5Dlg::OnBnClickedButton_LOAD()	//导入
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(true);	
	if (dlg.DoModal() == IDOK)
	{
		CString cstrPath = dlg.GetPathName();
		ifstream FileIn(cstrPath);
		g_CTrie.CreateDataFile(FileIn);
		MessageBox(_T("导入成功"), _T("提示"), MB_OK);
	}

}


void CMy5Dlg::OnBnClickedButton_LOOK()	//查看
{
	// TODO:  在此添加控件通知处理程序代码
	CLookDlg dlg;
	dlg.DoModal();
}


void CMy5Dlg::OnBnClickedButton_INSERT()	//插入
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgInsert dlg;
	dlg.DoModal();
}


void CMy5Dlg::OnBnClickedButton_DELETE()	//删除
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgDelete dlg;
	dlg.DoModal();
}

void CMy5Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);

}


void CMy5Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);

}


void CMy5Dlg::OnBnClickedButton1()	//查询
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	Lock = false;
	m_listbDisplay.ResetContent();
	ifstream DataFileIn("DATA.data");
	CTrieNode* pRoot = g_CTrie.GetRoot();
	m_cstrInput.MakeLower();
	for (int i = 0; i < m_cstrInput.GetLength(); i++)
	{
		if (pRoot == NULL)
		{
			return;
		}
		pRoot = pRoot->pChild[m_cstrInput[i] - 'a'];
	}
	if (pRoot == NULL)
	{
		return;
	}
	/*清晰查询*/
	if (pRoot->enumType == COMPLETE)
	{
		while (!Forward.empty())
		{
			Backward.push(Forward.top());
			Forward.pop();
		}

		char* lpszEng = new char[pRoot->pIndex->nEngLen];
		DataFileIn.seekg(pRoot->pIndex->nEngPos, ios::beg);
		DataFileIn.getline(lpszEng, pRoot->pIndex->nEngLen);

		char* lpszCh = new char[pRoot->pIndex->nChLen];
		DataFileIn.seekg(pRoot->pIndex->nChPos, ios::beg);
		DataFileIn.getline(lpszCh, pRoot->pIndex->nChLen);

		CString cstrEng(lpszEng);
		CString cstrCh(lpszCh);

		m_lisbResult.ResetContent();

		m_lisbResult.InsertString(0, cstrEng);
		m_lisbResult.InsertString(1, cstrCh);

		Backward.push(pRoot->pIndex);

		delete[] lpszEng;
		delete[] lpszCh;
		Lock = true;
	}
	/*模糊查询*/
	else
	{
		queue<CTrieNode*> Search;
		Search.push(pRoot);
		int nNum = 0;
		while (nNum < 10&&(!Search.empty()))
		{
			CTrieNode* pTemp = Search.front();
			Search.pop();
			for (int i = 0; i < MAX_SIZE; i++)
			{
				if (pTemp->pChild[i] != NULL)
				{
					Search.push(pTemp->pChild[i]);
				}
			}
			if (pTemp->enumType == COMPLETE)
			{
				char* lpszEng = new char[pTemp->pIndex->nEngLen];
				DataFileIn.seekg(pTemp->pIndex->nEngPos, ios::beg);
				DataFileIn.getline(lpszEng, pTemp->pIndex->nEngLen);

				char* lpszCh = new char[pTemp->pIndex->nChLen];
				DataFileIn.seekg(pTemp->pIndex->nChPos, ios::beg);
				DataFileIn.getline(lpszCh, pTemp->pIndex->nChLen);

				CString cstrEng(lpszEng);
				CString cstrCh(lpszCh);

				m_listbDisplay.InsertString(2*nNum, cstrEng);
				m_listbDisplay.InsertString(2*nNum + 1, cstrCh);

				delete[] lpszEng;
				delete[] lpszCh;
				nNum++;
			}
		}
	}
	DataFileIn.close();
	UpdateData(false);
}


void CMy5Dlg::OnBnClickedButton2()	//回退
{
	// TODO:  在此添加控件通知处理程序代码
	ifstream DataFileIn("DATA.data");
	CIndexInfo* pIndex = NULL;
	if (Backward.empty())
	{
		return;
	}
	if (Forward.empty())
	{
		Forward.push(Backward.top());
		Backward.pop();
		if (!Backward.empty())
			pIndex = Backward.top();
		else
			return;
	}
	else
	{
		pIndex = Backward.top();
		Forward.push(pIndex);
		Backward.pop();
	}

	char* lpszEng = new char[pIndex->nEngLen];
	DataFileIn.seekg(pIndex->nEngPos, ios::beg);
	DataFileIn.getline(lpszEng, pIndex->nEngLen);

	char* lpszCh = new char[pIndex->nChLen];
	DataFileIn.seekg(pIndex->nChPos, ios::beg);
	DataFileIn.getline(lpszCh, pIndex->nChLen);

	CString cstrEng(lpszEng);
	CString cstrCh(lpszCh);

	m_lisbResult.ResetContent();
	m_lisbResult.InsertString(0, cstrEng);
	m_lisbResult.InsertString(1, cstrCh);

	delete[] lpszEng;
	delete[] lpszCh;
}


void CMy5Dlg::OnBnClickedButton3()	//前进
{
	// TODO:  在此添加控件通知处理程序代码
	ifstream DataFileIn("DATA.data");
	CIndexInfo* pIndex = NULL;
	if (Forward.empty())
	{
		return;
	}
	if (Backward.empty())
	{
		Backward.push(Forward.top());
		Forward.pop();
		if (!Forward.empty())
			pIndex = Forward.top();
		else
			return;
	}
	else
	{
		pIndex = Forward.top();
		Backward.push(pIndex);
		Forward.pop();
	}

	char* lpszEng = new char[pIndex->nEngLen];
	DataFileIn.seekg(pIndex->nEngPos, ios::beg);
	DataFileIn.getline(lpszEng, pIndex->nEngLen);

	char* lpszCh = new char[pIndex->nChLen];
	DataFileIn.seekg(pIndex->nChPos, ios::beg);
	DataFileIn.getline(lpszCh, pIndex->nChLen);

	CString cstrEng(lpszEng);
	CString cstrCh(lpszCh);

	m_lisbResult.ResetContent();
	m_lisbResult.InsertString(0, cstrEng);
	m_lisbResult.InsertString(1, cstrCh);

	delete[] lpszEng;
	delete[] lpszCh;
}


void CMy5Dlg::OnBnClickedButton4()	//发音
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (Lock)
	{
		pSpVoice->SetVolume(80);
		CString cstrVoice;
		m_lisbResult.GetText(0, cstrVoice);
		pSpVoice->Speak(cstrVoice, SPF_DEFAULT, NULL);
	}
	UpdateData(false);
}


void CMy5Dlg::OnBnClickedButton9()	//背单词
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgGame dlg;
	dlg.DoModal();
}


void CMy5Dlg::OnUpdateEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString cstrInput;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(cstrInput);
	m_listbDisplay.ResetContent();
	ifstream DataFileIn("DATA.data");
	CTrieNode* pRoot = g_CTrie.GetRoot();
	queue<CTrieNode*> Search;

	int nNum = 0;

	cstrInput.MakeLower();
	for (int i = 0; i < cstrInput.GetLength(); i++)
	{
		if (pRoot == NULL)
		{
			return;
		}
		pRoot = pRoot->pChild[cstrInput[i] - 'a'];
	}
	if (pRoot == NULL)
	{
		return;
	}

	Search.push(pRoot);
	
	while (nNum < 10 && (!Search.empty()))
	{
		CTrieNode* pTemp = Search.front();
		Search.pop();
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (pTemp->pChild[i] != NULL)
			{
				Search.push(pTemp->pChild[i]);
			}
		}
		if (pTemp->enumType == COMPLETE)
		{
			char* lpszEng = new char[pTemp->pIndex->nEngLen];
			DataFileIn.seekg(pTemp->pIndex->nEngPos, ios::beg);
			DataFileIn.getline(lpszEng, pTemp->pIndex->nEngLen);

			char* lpszCh = new char[pTemp->pIndex->nChLen];
			DataFileIn.seekg(pTemp->pIndex->nChPos, ios::beg);
			DataFileIn.getline(lpszCh, pTemp->pIndex->nChLen);

			CString cstrEng(lpszEng);
			CString cstrCh(lpszCh);

			m_listbDisplay.InsertString(2 * nNum, cstrEng);
			m_listbDisplay.InsertString(2 * nNum + 1, cstrCh);

			delete[] lpszEng;
			delete[] lpszCh;
			nNum++;
		}
	}
	DataFileIn.close();
}
