#pragma once


// CDlgInsert �Ի���

class CDlgInsert : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInsert)

public:
	CDlgInsert(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInsert();

// �Ի�������
	enum { IDD = IDD_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrEng;
	CString m_cstrCh;
	afx_msg void OnBnClickedButton_INSERT();
};
