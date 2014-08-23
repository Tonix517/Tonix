// ImageWriterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CImageWriterDlg 对话框
class CImageWriterDlg : public CDialog
{
// 构造
public:
	CImageWriterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGEWRITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedBgen();
public:
	afx_msg void OnBnClickedBexit();
	CString m_zBooterPath;
	CString m_zLoaderPath;
	CString m_zKernelPath;
	float m_fImageSize;
	CString m_zImagePath;
	UINT m_nLoaderStart;
	UINT m_nKernelStart;
public:
	afx_msg void OnBnClickedBbooterPath();
public:
	afx_msg void OnBnClickedBloaderPath();
public:
	afx_msg void OnBnClickedBkernelPath();
public:
	afx_msg void OnBnClickedBimagePath();
	UINT m_nHeadNum;
	UINT m_nSptNum;
	UINT m_nCylinderNum;

private:
	bool check_booter(CString & zBooterPath);
	bool check_loader(CString & zLoaderPath);
	bool check_kernel(CString & zKernelPath);
	bool check_image();
public:
	afx_msg void OnBnClickedFloppyCheck();
	CButton m_bFloppy;
	afx_msg void OnEnChangeEditKernelStart();
	afx_msg void OnEnChangeEditSptNum();
	afx_msg void OnEnChangeEditImageSize();
};
