// BmpGettorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpGettor.h"
#include "BmpGettorDlg.h"
#include ".\bmpgettordlg.h"
#include "convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ========= Global Variables ========== //
CString fileName;
bool hasBmp = false;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBmpGettorDlg 对话框



CBmpGettorDlg::CBmpGettorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpGettorDlg::IDD, pParent)
	, m_data(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBmpGettorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_PROGRESS1, m_probar);
}

BEGIN_MESSAGE_MAP(CBmpGettorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_EN_CHANGE(IDC_EDIT_DATA, OnEnChangeEditData)
ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
ON_WM_CLOSE()
//ON_STN_DBLCLK(IDC_PIC, OnStnDblclickPic)
//ON_STN_DBLCLK(IDC_PIC, OnStnDblclickPic)
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CBmpGettorDlg 消息处理程序

BOOL CBmpGettorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_data = "请双击窗体空白处打开图片\r\n[ 240 * 320 ,16bit]";
	
	UpdateData(false);
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CBmpGettorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBmpGettorDlg::OnPaint() 
{
	if(hasBmp)
	{
		CBitmap bmp;
		HBITMAP bitmap;
		bitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),fileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			bmp.Attach(bitmap);
			CDC memDC;//内存设备场景			
			CRect rect;
			m_pic.GetWindowRect(&rect);
			CClientDC dc(this);
			memDC.CreateCompatibleDC (&dc);//创建内存设备上下文
			CBitmap *oldbitmap=NULL;
			oldbitmap=memDC.SelectObject (&bmp);//将位图选入当前设备场景
			dc.BitBlt (12,16,rect.Width (),rect.Height (),&memDC,0,0,SRCCOPY);//将内存场景的图象拷贝到屏幕上
			memDC.SelectObject (oldbitmap);	
		
	}
	
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
		CDialog::OnPaint();
	}
}



//void CBmpGettorDlg::OnEnChangeEditData()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
//	// 发送该通知，除非重写 CDialog::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}



// 粘贴数据到剪贴板
void CBmpGettorDlg::OnBnClickedButton1()
{
	if(!hasBmp)
	{
		MessageBox("未转换图片");
		return;
	}
	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, m_data.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(m_data));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
		MessageBox("数据已复制到剪贴板","完成",MB_OK);
	}
	else
	{
		MessageBox("无法打开剪贴板");
		return;
	}
}

void CBmpGettorDlg::OnClose()
{
	// Exit
	ExitProcess(0);
}

// Worker Thread
UINT convert(LPVOID lparam);

// 打开BMP图片　＆　转换图片
void CBmpGettorDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// === 选择图片 === //
	CFileDialog dlg(TRUE, 
					NULL,
					NULL,
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"BMP Files (*.bmp) | *.bmp||", this);

	if(dlg.DoModal() == IDOK)
	{
		fileName = dlg.GetPathName();
		hasBmp = true;		
		
		// ====== 打开BMP图片 ====== //
		CBitmap bmp;
		HBITMAP bitmap;
		bitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),fileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		
		if( bitmap == NULL ) 
		{
			MessageBox("图片加载错误","提示",MB_OK);
			return;
		}
		else
		{		
			// === 检查BMP图片格式（240 * 320,16）=== //
			BITMAP   bm;   
			GetObject(bitmap,sizeof(bm),&bm);			
			/*
			CString tmp;
			tmp.Format("Bits:%d, Height:%d, Width:%d",bm.bmBitsPixel,bm.bmHeight,bm.bmWidth);
			MessageBox(tmp);
			*/
			
			// ====== 检查文件 ====== //
			if( (bm.bmHeight != 320) || (bm.bmWidth != 240))
			{
				MessageBox("图片大小不是240*320!");
				return;
			}
			/*
			CFile tmpFile(fileName,CFile::modeRead);
			DWORD len = tmpFile.GetLength();
			if( (len-230454) > 2 || (len-230454) < 2)
			{
				MessageBox("文件大小有误");
				return;
			}	*/		

			// ======= 显示图片 ======= //
			bmp.Attach(bitmap);
			CDC memDC;//内存设备场景			
			CRect rect;
			m_pic.GetWindowRect(&rect);
			CClientDC dc(this);
			memDC.CreateCompatibleDC (&dc);//创建内存设备上下文
			CBitmap *oldbitmap=NULL;
			oldbitmap=memDC.SelectObject (&bmp);//将位图选入当前设备场景
			dc.BitBlt (12,16,rect.Width (),rect.Height (),&memDC,0,0,SRCCOPY);//将内存场景的图象拷贝到屏幕上
			memDC.SelectObject (oldbitmap);		
          
			// ====== 开启转换线程 ====== //
			AfxBeginThread(convert,this,0,0,NULL);

		} // if(bmp != null)

	}// DoModal == OK	

}

// ====== Converter Thread ========= //
UINT convert(LPVOID lparam)
{
	CBmpGettorDlg *pdlg = (CBmpGettorDlg *)lparam;	
	
			FILE *fp;
			fp = fopen(fileName.GetBuffer(), "r"); 

			if(fp != NULL)
			{
				// Buffer
				unsigned char   r[320*240*3];
				unsigned short r2[320*240*2];

				// 读入缓冲 - in no time
				fseek(fp,54,SEEK_SET);// Skip the head							
				fread(r,240*320*3,1,fp);										
				fclose(fp);
				
				// 开始转换 
				for(long i = 0; i< 320*240; i++)
				{					
					r2[ 2 * i ] = to565pal(f8to8(r[i*3+2],0),
										   f8to8(r[i*3+1],1),
										   f8to8(r[i*3],2));
					pdlg->m_probar.SetPos((int)(i+1)*1.0/(320*240)*70);		
				}				
				
				// 输出到CString	
				pdlg -> m_data = "";
				for(int i = 320-1; i > -1; i--)				
				{
					for(int j = 0; j <240; j++)
					{
						pdlg->m_data.AppendFormat("0x%x,",(unsigned short)r2[(i*240+j)*2]);
						if( (j+1) % 6 == 0)
						{
							pdlg->m_data.Append("\r\n");												
						}
					}
					
					// if it's in the j loop, it'll make conflicts to m_data
					pdlg->m_probar.SetPos((int)(320-i-1)*1.0/320*30+70);

				}//for				
				
			}//if
			else
			{
				AfxMessageBox("无法打开文件！");
			}
	return 0;
}
