// BmpGettorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CBmpGettorDlg �Ի���
class CBmpGettorDlg : public CDialog
{
// ����
public:
	CBmpGettorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BMPGETTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
// ת������ַ���������
	CString m_data;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	CStatic m_pic;
//	afx_msg void OnStnDblclickPic();
//	afx_msg void OnStnDblclickPic();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CProgressCtrl m_probar;
};
