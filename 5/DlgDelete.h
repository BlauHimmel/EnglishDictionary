#pragma once


// CDlgDelete �Ի���

class CDlgDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDelete)

public:
	CDlgDelete(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDelete();

// �Ի�������
	enum { IDD = IDD_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrEng;
	afx_msg void OnBnClickedButton_DELETE();
};
