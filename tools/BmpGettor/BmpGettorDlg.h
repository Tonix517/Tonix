// BmpGettorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CBmpGettorDlg 对话框
class CBmpGettorDlg : public CDialog
{
// 构造
public:
	CBmpGettorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BMPGETTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
// 转换后的字符数组数据
	CString m_data;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	CStatic m_pic;
//	afx_msg void OnStnDblclickPic();
//	afx_msg void OnStnDblclickPic();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CProgressCtrl m_probar;
};
