// RUIYIN_OMRON.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "RUIYIN_OMRON.h"
#include "PB_API.h"
#include "RS232C.H"
#include "COMMFCN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL g_bIsInit = FALSE;
CRs232c g_ToolRs232;
vector<CString> strVec; //将引用层传进来的字符串解析成单个字符串装进容器里面

#define TIMEOUT 500

HANDLE g_hDevicePolling = NULL;
HANDLE	g_hDevicePollingEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
static DWORD WINAPI	PollingThreadProc(LPVOID pParam);
//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CRUIYIN_OMRONApp

BEGIN_MESSAGE_MAP(CRUIYIN_OMRONApp, CWinApp)
END_MESSAGE_MAP()


// CRUIYIN_OMRONApp 构造

CRUIYIN_OMRONApp::CRUIYIN_OMRONApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CRUIYIN_OMRONApp 对象

CRUIYIN_OMRONApp theApp;


// CRUIYIN_OMRONApp 初始化

BOOL CRUIYIN_OMRONApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
int PB_API Initialize(int Buate, int Port)
{
	DeleteLog(GetFullPath("LOG").GetBuffer(0), 15);
	LOG_LEVEL(LOGTYPE_DEBUG | LOGTYPE_ERROR | LOGTYPE_SPECIAL);
	LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[Initialize]--正在初始化...");
	g_bIsInit = FALSE;


	if (g_ToolRs232.SetOpenState(Buate, 7, EVENPARITY, ONESTOPBIT))
	{
		if (!g_ToolRs232.Open(Port))
		{
			LOG_JSRCB(LOGTYPE_ERROR, OMRONLOG, "Initialize]--打开串口[%d]失败！%d", Port, GetLastError());
			return -1;
		}
	}

	DWORD dwThreadId = NULL;
	g_hDevicePolling = CreateThread(NULL, 0, PollingThreadProc, NULL, 0, &dwThreadId);
	g_bIsInit = TRUE;
	SetEvent(g_hDevicePollingEvent);
	return 1;
}
static DWORD WINAPI	PollingThreadProc(LPVOID pParam)
{
	BOOL bRet = FALSE;
	while (TRUE)
	{
		DWORD dwResult = WaitForSingleObject(g_hDevicePollingEvent, INFINITE);
		if (dwResult == WAIT_OBJECT_0)
		{
			Sleep(TIMEOUT);
			LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[PollingThreadProc]--触发线程...");

			g_ToolRs232.ClearSR();
			if (FALSE == g_ToolRs232.IsOpen()) continue;
			UINT uLen = 0, uReadLen = 0;
			BYTE szBuff[1024] = { 0 };

			bRet = g_ToolRs232.GetString(szBuff, 40, (int*)&uReadLen, TIMEOUT * 1000);
			LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[BeginRead]--开始读，字符串是[%s]", szBuff);

			if (FALSE == bRet) continue;
			
			CString CStrTemp,CStrData;
			CStrTemp = szBuff;
			strVec = SplitString(CStrTemp, " ");
			char szSendData[1024] = { 0 };

			sprintf(szSendData,"%s，%s，%s" ,strVec[1], strVec[2], strVec[3]);
			LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[BeginRead]--开始读，截取字符串是[%s]", szSendData);
			m_pFunCBGetCardNumByTrack(szSendData);

		}
	}
	return TRUE;
}
BOOL SetCallBack(GetCardNumByTrack pFun)
{
	if (NULL == pFun)
	{
		LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "回掉函数不得为空.");
		return FALSE;
	}
	m_pFunCBGetCardNumByTrack = pFun;
	return TRUE;
}