#pragma once


// CDlgDelete 对话框

class CDlgDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDelete)

public:
	CDlgDelete(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDelete();

// 对话框数据
	enum { IDD = IDD_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrEng;
	afx_msg void OnBnClickedButton_DELETE();
};
