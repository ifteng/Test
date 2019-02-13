// RUIYIN_OMRON.h : RUIYIN_OMRON DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CRUIYIN_OMRONApp
// 有关此类实现的信息，请参阅 RUIYIN_OMRON.cpp
//
typedef void (CALLBACK *GetCardNumByTrack)(char* pCardNum);

GetCardNumByTrack m_pFunCBGetCardNumByTrack;


class CRUIYIN_OMRONApp : public CWinApp
{
public:
	CRUIYIN_OMRONApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
