
// ������������ϵͳ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C������������ϵͳApp: 
// �йش����ʵ�֣������ ������������ϵͳ.cpp
//

class C������������ϵͳApp : public CWinApp
{
public:
	C������������ϵͳApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C������������ϵͳApp theApp;