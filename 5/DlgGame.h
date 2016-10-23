#pragma once


// CDlgGame �Ի���

class CDlgGame : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGame)

public:
	CDlgGame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgGame();

	CIndexInfo* GetIndexRandomly();

	ISpVoice *pSpVoiceGame;
	BOOL OnInitDialog();
	
// �Ի�������
	enum { IDD = IDD_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnCancel();

	CString m_cstrCurEng;	//��ǰ��ȷ��Ӣ�ﵥ��
	CString m_cstrCurCh;	//��ǰ��ȷ�ķ���
	int m_nCorrect;			//��ǰ��ȷ�ĸ���	
	int m_nWrong;			//��ǰ����ĸ���

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrAnswer;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton2();
};
