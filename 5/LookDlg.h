#pragma once
#include "afxwin.h"


// CLookDlg 对话框

class CLookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLookDlg)

public:
	CLookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLookDlg();

// 对话框数据
	enum { IDD = IDD_LOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	void ShowAllData();
	DECLARE_MESSAGE_MAP()
public:
	// //查看单词窗口的ListBox控件
	CListBox m_listbLook;
	afx_msg void OnBnClickedButton_DISPLAY();
};
