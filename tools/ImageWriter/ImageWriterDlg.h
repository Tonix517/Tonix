// ImageWriterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CImageWriterDlg �Ի���
class CImageWriterDlg : public CDialog
{
// ����
public:
	CImageWriterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IMAGEWRITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
