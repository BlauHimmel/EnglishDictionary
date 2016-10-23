#pragma once


// CDlgGame 对话框

class CDlgGame : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGame)

public:
	CDlgGame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgGame();

	CIndexInfo* GetIndexRandomly();

	ISpVoice *pSpVoiceGame;
	BOOL OnInitDialog();
	
// 对话框数据
	enum { IDD = IDD_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnCancel();

	CString m_cstrCurEng;	//当前正确的英语单词
	CString m_cstrCurCh;	//当前正确的翻译
	int m_nCorrect;			//当前正确的个数	
	int m_nWrong;			//当前错误的个数

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrAnswer;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton2();
};
