// RUIYIN_OMRON.h : RUIYIN_OMRON DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRUIYIN_OMRONApp
// �йش���ʵ�ֵ���Ϣ������� RUIYIN_OMRON.cpp
//
typedef void (CALLBACK *GetCardNumByTrack)(char* pCardNum);

GetCardNumByTrack m_pFunCBGetCardNumByTrack;


class CRUIYIN_OMRONApp : public CWinApp
{
public:
	CRUIYIN_OMRONApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
