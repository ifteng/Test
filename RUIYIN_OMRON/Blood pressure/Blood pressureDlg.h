
// Blood pressureDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CBloodpressureDlg �Ի���
class CBloodpressureDlg : public CDialogEx
{
// ����
public:
	CBloodpressureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLOODPRESSURE_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	CComboBox m_droplist;
	afx_msg void OnBnClickedStart();
	CEdit m_Buate;
};
