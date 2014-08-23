// BmpGettorDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CBmpGettorDlg �Ի���



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


// CBmpGettorDlg ��Ϣ�������

BOOL CBmpGettorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_data = "��˫������հ״���ͼƬ\r\n[ 240 * 320 ,16bit]";
	
	UpdateData(false);
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBmpGettorDlg::OnPaint() 
{
	if(hasBmp)
	{
		CBitmap bmp;
		HBITMAP bitmap;
		bitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),fileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			bmp.Attach(bitmap);
			CDC memDC;//�ڴ��豸����			
			CRect rect;
			m_pic.GetWindowRect(&rect);
			CClientDC dc(this);
			memDC.CreateCompatibleDC (&dc);//�����ڴ��豸������
			CBitmap *oldbitmap=NULL;
			oldbitmap=memDC.SelectObject (&bmp);//��λͼѡ�뵱ǰ�豸����
			dc.BitBlt (12,16,rect.Width (),rect.Height (),&memDC,0,0,SRCCOPY);//���ڴ泡����ͼ�󿽱�����Ļ��
			memDC.SelectObject (oldbitmap);	
		
	}
	
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}



//void CBmpGettorDlg::OnEnChangeEditData()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
//	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}



// ճ�����ݵ�������
void CBmpGettorDlg::OnBnClickedButton1()
{
	if(!hasBmp)
	{
		MessageBox("δת��ͼƬ");
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
		MessageBox("�����Ѹ��Ƶ�������","���",MB_OK);
	}
	else
	{
		MessageBox("�޷��򿪼�����");
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

// ��BMPͼƬ������ת��ͼƬ
void CBmpGettorDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// === ѡ��ͼƬ === //
	CFileDialog dlg(TRUE, 
					NULL,
					NULL,
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"BMP Files (*.bmp) | *.bmp||", this);

	if(dlg.DoModal() == IDOK)
	{
		fileName = dlg.GetPathName();
		hasBmp = true;		
		
		// ====== ��BMPͼƬ ====== //
		CBitmap bmp;
		HBITMAP bitmap;
		bitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),fileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		
		if( bitmap == NULL ) 
		{
			MessageBox("ͼƬ���ش���","��ʾ",MB_OK);
			return;
		}
		else
		{		
			// === ���BMPͼƬ��ʽ��240 * 320,16��=== //
			BITMAP   bm;   
			GetObject(bitmap,sizeof(bm),&bm);			
			/*
			CString tmp;
			tmp.Format("Bits:%d, Height:%d, Width:%d",bm.bmBitsPixel,bm.bmHeight,bm.bmWidth);
			MessageBox(tmp);
			*/
			
			// ====== ����ļ� ====== //
			if( (bm.bmHeight != 320) || (bm.bmWidth != 240))
			{
				MessageBox("ͼƬ��С����240*320!");
				return;
			}
			/*
			CFile tmpFile(fileName,CFile::modeRead);
			DWORD len = tmpFile.GetLength();
			if( (len-230454) > 2 || (len-230454) < 2)
			{
				MessageBox("�ļ���С����");
				return;
			}	*/		

			// ======= ��ʾͼƬ ======= //
			bmp.Attach(bitmap);
			CDC memDC;//�ڴ��豸����			
			CRect rect;
			m_pic.GetWindowRect(&rect);
			CClientDC dc(this);
			memDC.CreateCompatibleDC (&dc);//�����ڴ��豸������
			CBitmap *oldbitmap=NULL;
			oldbitmap=memDC.SelectObject (&bmp);//��λͼѡ�뵱ǰ�豸����
			dc.BitBlt (12,16,rect.Width (),rect.Height (),&memDC,0,0,SRCCOPY);//���ڴ泡����ͼ�󿽱�����Ļ��
			memDC.SelectObject (oldbitmap);		
          
			// ====== ����ת���߳� ====== //
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

				// ���뻺�� - in no time
				fseek(fp,54,SEEK_SET);// Skip the head							
				fread(r,240*320*3,1,fp);										
				fclose(fp);
				
				// ��ʼת�� 
				for(long i = 0; i< 320*240; i++)
				{					
					r2[ 2 * i ] = to565pal(f8to8(r[i*3+2],0),
										   f8to8(r[i*3+1],1),
										   f8to8(r[i*3],2));
					pdlg->m_probar.SetPos((int)(i+1)*1.0/(320*240)*70);		
				}				
				
				// �����CString	
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
				AfxMessageBox("�޷����ļ���");
			}
	return 0;
}
