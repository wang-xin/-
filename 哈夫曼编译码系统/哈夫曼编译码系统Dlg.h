
// ������������ϵͳDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// C������������ϵͳDlg �Ի���
class C������������ϵͳDlg : public CDialogEx
{
// ����
public:
	C������������ϵͳDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_record;
	afx_msg void OnBnClickedButton4();
	CString str;
	int lastLine;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	int m_num;
	CString m_element;
	CString m_weight;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
