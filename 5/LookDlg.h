#pragma once
#include "afxwin.h"


// CLookDlg �Ի���

class CLookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLookDlg)

public:
	CLookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLookDlg();

// �Ի�������
	enum { IDD = IDD_LOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	void ShowAllData();
	DECLARE_MESSAGE_MAP()
public:
	// //�鿴���ʴ��ڵ�ListBox�ؼ�
	CListBox m_listbLook;
	afx_msg void OnBnClickedButton_DISPLAY();
};
