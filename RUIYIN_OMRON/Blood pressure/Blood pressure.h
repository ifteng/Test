
// Blood pressure.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBloodpressureApp: 
// �йش����ʵ�֣������ Blood pressure.cpp
//

class CBloodpressureApp : public CWinApp
{
public:
	CBloodpressureApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBloodpressureApp theApp;