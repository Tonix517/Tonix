// ImageWriterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageWriter.h"
#include "ImageWriterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageWriterDlg 对话框




CImageWriterDlg::CImageWriterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageWriterDlg::IDD, pParent)
	, m_zBooterPath(_T(""))
	, m_zLoaderPath(_T(""))
	, m_zKernelPath(_T(""))
	, m_fImageSize(0)
	, m_zImagePath(_T(""))
	, m_nLoaderStart(1)
	, m_nKernelStart(0)
	, m_nHeadNum(2)
	, m_nSptNum(0)
	, m_nCylinderNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageWriterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Booter_Path, m_zBooterPath);
	DDX_Text(pDX, IDC_EDIT_Loader_Path, m_zLoaderPath);
	DDX_Text(pDX, IDC_EDIT_Kernel_Path, m_zKernelPath);
	DDX_Text(pDX, IDC_EDIT_Image_Size, m_fImageSize);
	DDX_Text(pDX, IDC_EDIT_Image_Path, m_zImagePath);
	DDX_Text(pDX, IDC_EDIT_Loader_Start, m_nLoaderStart);
	DDX_Text(pDX, IDC_EDIT_Kernel_Start, m_nKernelStart);
	DDX_Text(pDX, IDC_EDIT_Head_Num, m_nHeadNum);
	DDX_Text(pDX, IDC_EDIT_Spt_Num, m_nSptNum);
	DDX_Text(pDX, IDC_EDIT_Cylinder_Num, m_nCylinderNum);
	DDX_Control(pDX, IDC_CHECK1, m_bFloppy);
}

BEGIN_MESSAGE_MAP(CImageWriterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BGen, &CImageWriterDlg::OnBnClickedBgen)
	ON_BN_CLICKED(IDC_BExit, &CImageWriterDlg::OnBnClickedBexit)
	ON_BN_CLICKED(IDC_BBooter_Path, &CImageWriterDlg::OnBnClickedBbooterPath)
	ON_BN_CLICKED(IDC_BLoader_Path, &CImageWriterDlg::OnBnClickedBloaderPath)
	ON_BN_CLICKED(IDC_BKernel_Path, &CImageWriterDlg::OnBnClickedBkernelPath)
	ON_BN_CLICKED(IDC_BImage_Path, &CImageWriterDlg::OnBnClickedBimagePath)
	ON_BN_CLICKED(IDC_CHECK1, &CImageWriterDlg::OnBnClickedFloppyCheck)
	ON_EN_CHANGE(IDC_EDIT_Kernel_Start, &CImageWriterDlg::OnEnChangeEditKernelStart)
	ON_EN_CHANGE(IDC_EDIT_Spt_Num, &CImageWriterDlg::OnEnChangeEditSptNum)
	ON_EN_CHANGE(IDC_EDIT_Image_Size, &CImageWriterDlg::OnEnChangeEditImageSize)
END_MESSAGE_MAP()


// CImageWriterDlg 消息处理程序

BOOL CImageWriterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageWriterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		UpdateData(true);
		CDialog::OnPaint();		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CImageWriterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageWriterDlg::OnBnClickedBgen()
{
	UpdateData(true);
	
	//	Check Booter
	if(!check_booter(m_zBooterPath))
	{
		return;
	}

	//	Check Loader
	if(!check_loader(m_zLoaderPath))
	{
		return;
	}

	//	Check Kernel
	if(!check_kernel(m_zKernelPath))
	{
		return;
	}

	//	Check Image Path
	if(!check_image())
	{
		return;
	}
	
	//	Write
	FILE *fImg = fopen(m_zImagePath.GetBuffer(), "wb");
	if(fImg)
	{
		const size_t BufSize = 10*1024;

		char rBuf[BufSize] = {0};

		//	Write Booter
		FILE *fBoot = fopen(m_zBooterPath, "rb");
		if(fBoot)
		{
			size_t nRead = 0;
			while( (nRead = fread(rBuf, 1, BufSize, fBoot)) > 0)
			{
				fwrite(rBuf, nRead, 1, fImg);
			}
			fclose(fBoot);
		}
		
		fseek(fImg, m_nLoaderStart*512, SEEK_SET);

		//	Write Loader
		FILE *fLoader = fopen(m_zLoaderPath, "rb");
		if(fLoader)
		{
			size_t nRead = 0;
			while( (nRead = fread(rBuf, 1, BufSize, fLoader)) > 0)
			{
				fwrite(rBuf, nRead, 1, fImg);
			}
			fclose(fLoader);
		}

		fseek(fImg, m_nKernelStart*512, SEEK_SET);

		//	Write Kernel
		FILE *fKernel = fopen(m_zKernelPath, "rb");
		if(fKernel)
		{
			size_t nRead = 0;
			while( (nRead = fread(rBuf, 1, BufSize, fKernel)) > 0)
			{
				fwrite(rBuf, nRead, 1, fImg);
			}
			fclose(fKernel);
		}
		
		fseek(fImg, m_fImageSize*1024*1024 -1 , SEEK_SET);
		char c = 0;
		fwrite(&c, 1, 1, fImg);
		fclose(fImg);
	}
	else
	{
		::AfxMessageBox("Cannot Write to the Image file.");
		return;
	}

	//	Calculate Cynlinder
	if(m_nHeadNum == 0) m_nHeadNum = 2;	
	if(m_nSptNum == 0) m_nSptNum = 16;
	m_nCylinderNum = m_fImageSize*1024*1024/m_nHeadNum/m_nSptNum/512;
	UpdateData(false);

	::AfxMessageBox("Done!");
}

void CImageWriterDlg::OnBnClickedBexit()
{	
	OnOK();
}

void CImageWriterDlg::OnBnClickedBbooterPath()
{
	CFileDialog dlg(TRUE);

	if(dlg.DoModal() == IDOK)
	{
		m_zBooterPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CImageWriterDlg::OnBnClickedBloaderPath()
{
	CFileDialog dlg(TRUE);

	if(dlg.DoModal() == IDOK)
	{
		m_zLoaderPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CImageWriterDlg::OnBnClickedBkernelPath()
{
	CFileDialog dlg(TRUE);

	if(dlg.DoModal() == IDOK)
	{
		m_zKernelPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CImageWriterDlg::OnBnClickedBimagePath()
{
	LPITEMIDLIST pidlRoot=NULL, pDirGot; 

	BROWSEINFO bi;   
	CString strDisplayName;   
	bi.hwndOwner=GetSafeHwnd();   
	bi.pidlRoot=pidlRoot;  
	bi.pszDisplayName=strDisplayName.GetBuffer(MAX_PATH+1);   
	bi.lpszTitle="Select Target Directory";  
	bi.ulFlags=BIF_DONTGOBELOWDOMAIN  | BIF_RETURNONLYFSDIRS;

	bi.lpfn=NULL; 
	bi.lParam=0; 
	bi.iImage=0;  
	pDirGot = SHBrowseForFolder(&bi);   
	
	if(pDirGot != NULL)
	{
		char lpszPath[MAX_PATH];
		if(SHGetPathFromIDList(pDirGot,lpszPath))
		{
			strDisplayName.Format(_T("%s"),lpszPath);
			strDisplayName.Append("\\Demo.img");
			m_zImagePath = strDisplayName;
			UpdateData(FALSE);
		}		
	}
	strDisplayName.ReleaseBuffer();   
}

bool CImageWriterDlg::check_booter(CString & zBooterPath)
{
	FILE *fp = fopen(zBooterPath.GetBuffer(), "rb");
	if(fp)
	{
		//	Check Size
		fseek(fp, 0, SEEK_END);
		long nFileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		if(nFileSize != 512)
		{
			::AfxMessageBox("The Booter File Size should be 512B~");
			fclose(fp);
			return false;
		}

		//	Check MBR Sign -- 0xAA55
		fseek(fp, -2, SEEK_END);
		char buf[2] = {0};
		char MBRSign[2] = { 0x55, 0xAA};
		fread(buf, 2, 1, fp);
		if(memcmp(buf, MBRSign, 2) != 0)
		{
			::AfxMessageBox("The Booter File is not a Valid Booter~\nChech the Last two bytes please.");
			fclose(fp);
			return false;
		}
		fclose(fp);
	}
	else
	{
		::AfxMessageBox("Cannot Open Booter File~!");
		return false;
	}
	return true;
}

bool CImageWriterDlg::check_loader(CString & zLoaderPath)
{
	if(zLoaderPath != "")
	{
		//	Check Start Sector
		if(m_nLoaderStart < 1)
		{
			::AfxMessageBox("Loader cannot be written to Sector 0.");
			return false;
		}

		//	Check File
		FILE *fp = fopen(zLoaderPath.GetBuffer(), "rb");
		if(!fp)
		{
			::AfxMessageBox("Cannot Open Loader File.");
			return false;
		}
		else
		{
			fclose(fp);
		}

		return true;
	}
	return true;
}

bool CImageWriterDlg::check_kernel(CString & zKernelPath)
{
	if(zKernelPath != "")
	{
		//	Check Sector
		FILE *fp0 = fopen(m_zLoaderPath.GetBuffer(), "rb");
		if(fp0 == NULL)
		{
			::AfxMessageBox("Kernel has to be loaded by a Loader.");
		}
		fseek(fp0, 0, SEEK_END);
		long nLoaderSize = ftell(fp0);
		fclose(fp0);

		UINT nBootloaderSectors = nLoaderSize / 512 + (nLoaderSize%512==0)?0:1;
		if(m_nKernelStart <= nBootloaderSectors)
		{
			::AfxMessageBox("Kernel will overwrite the loader~!");
			return false;
		}

		//	Check File
		FILE *fp = fopen(zKernelPath.GetBuffer(), "rb");
		if(!fp)
		{
			::AfxMessageBox("Cannot Open Kernel File.");
			return false;
		}
		else
		{
			fclose(fp);
		}

		return true;
	}
	return true;
}

bool CImageWriterDlg::check_image()
{

	if(m_zImagePath == "")
	{
		::AfxMessageBox("Image Path is Empty~");
		return false;
	}

	//	Check Image Size
	long nBooterSize = 0, nLoaderSize = 0, nKernelSize = 0;

	FILE *fp1 = fopen(m_zBooterPath.GetBuffer(), "rb");
	if(fp1)
	{
		fseek(fp1, 0, SEEK_END);
		nBooterSize = ftell(fp1);
		fclose(fp1);
	}

	FILE *fp2 = fopen(m_zLoaderPath.GetBuffer(), "rb");
	if(fp2)
	{
		fseek(fp2, 0, SEEK_END);
		nLoaderSize = ftell(fp2);
		fclose(fp2);
	}

	FILE *fp3 = fopen(m_zKernelPath.GetBuffer(), "rb");
	if(fp3)
	{
		fseek(fp3, 0, SEEK_END);
		nKernelSize = ftell(fp3);
		fclose(fp3);
	}

	if( m_fImageSize*1024*1024 <= (nBooterSize + nLoaderSize + nKernelSize))
	{
		::AfxMessageBox("The Image Size is too small");
		return false;
	}

	return true;
}

void CImageWriterDlg::OnBnClickedFloppyCheck()
{
	int nChecked = m_bFloppy.GetCheck();

	if(nChecked)
	{
		m_fImageSize = 1.40625;
		UpdateData(false);
	}
	else
	{
		m_fImageSize = 5;
		UpdateData(false);
	}
}

void CImageWriterDlg::OnEnChangeEditKernelStart()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(true);
}

void CImageWriterDlg::OnEnChangeEditSptNum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(true);
}

void CImageWriterDlg::OnEnChangeEditImageSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(true);
}
