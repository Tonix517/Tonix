// BmpGettor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CBmpGettorApp:
// �йش����ʵ�֣������ BmpGettor.cpp
//

class CBmpGettorApp : public CWinApp
{
public:
	CBmpGettorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBmpGettorApp theApp;
