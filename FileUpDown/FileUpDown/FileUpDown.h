
// FileUpDown.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileUpDownApp: 
// �йش����ʵ�֣������ FileUpDown.cpp
//

class CFileUpDownApp : public CWinApp
{
public:
	CFileUpDownApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileUpDownApp theApp;