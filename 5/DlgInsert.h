#pragma once


// CDlgInsert 对话框

class CDlgInsert : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsert)

public:
	CDlgInsert(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInsert();

// 对话框数据
	enum { IDD = IDD_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrEng;
	CString m_cstrCh;
	afx_msg void OnBnClickedButton_INSERT();
};
