
// 5Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CMy5Dlg 对话框
class CMy5Dlg : public CDialogEx
{
// 构造
public:
	CMy5Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY5_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	bool Lock;	//控制语音的开关
	ISpVoice *pSpVoice;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButton_LOAD();
	afx_msg void OnBnClickedButton_LOOK();
	afx_msg void OnBnClickedButton_INSERT();
	afx_msg void OnBnClickedButton_DELETE();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	// //预览
	CListBox m_listbDisplay;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButton1();
	CString m_cstrInput;
	CListBox m_lisbResult;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnUpdateEdit1();
};
