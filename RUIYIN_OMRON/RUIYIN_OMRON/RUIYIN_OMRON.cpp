// RUIYIN_OMRON.cpp : ���� DLL �ĳ�ʼ�����̡�
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
vector<CString> strVec; //�����ò㴫�������ַ��������ɵ����ַ���װ����������

#define TIMEOUT 500

HANDLE g_hDevicePolling = NULL;
HANDLE	g_hDevicePollingEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
static DWORD WINAPI	PollingThreadProc(LPVOID pParam);
//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CRUIYIN_OMRONApp

BEGIN_MESSAGE_MAP(CRUIYIN_OMRONApp, CWinApp)
END_MESSAGE_MAP()


// CRUIYIN_OMRONApp ����

CRUIYIN_OMRONApp::CRUIYIN_OMRONApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRUIYIN_OMRONApp ����

CRUIYIN_OMRONApp theApp;


// CRUIYIN_OMRONApp ��ʼ��

BOOL CRUIYIN_OMRONApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
int PB_API Initialize(int Buate, int Port)
{
	DeleteLog(GetFullPath("LOG").GetBuffer(0), 15);
	LOG_LEVEL(LOGTYPE_DEBUG | LOGTYPE_ERROR | LOGTYPE_SPECIAL);
	LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[Initialize]--���ڳ�ʼ��...");
	g_bIsInit = FALSE;


	if (g_ToolRs232.SetOpenState(Buate, 7, EVENPARITY, ONESTOPBIT))
	{
		if (!g_ToolRs232.Open(Port))
		{
			LOG_JSRCB(LOGTYPE_ERROR, OMRONLOG, "Initialize]--�򿪴���[%d]ʧ�ܣ�%d", Port, GetLastError());
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
			LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[PollingThreadProc]--�����߳�...");

			g_ToolRs232.ClearSR();
			if (FALSE == g_ToolRs232.IsOpen()) continue;
			UINT uLen = 0, uReadLen = 0;
			BYTE szBuff[1024] = { 0 };

			bRet = g_ToolRs232.GetString(szBuff, 40, (int*)&uReadLen, TIMEOUT * 1000);
			LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[BeginRead]--��ʼ�����ַ�����[%s]", szBuff);

			if (FALSE == bRet) continue;
			
			CString CStrTemp,CStrData;
			CStrTemp = szBuff;
			strVec = SplitString(CStrTemp, " ");
			char szSendData[1024] = { 0 };

			sprintf(szSendData,"%s��%s��%s" ,strVec[1], strVec[2], strVec[3]);
			LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "[BeginRead]--��ʼ������ȡ�ַ�����[%s]", szSendData);
			m_pFunCBGetCardNumByTrack(szSendData);

		}
	}
	return TRUE;
}
BOOL SetCallBack(GetCardNumByTrack pFun)
{
	if (NULL == pFun)
	{
		LOG_JSRCB(LOGTYPE_DEBUG, OMRONLOG, "�ص���������Ϊ��.");
		return FALSE;
	}
	m_pFunCBGetCardNumByTrack = pFun;
	return TRUE;
}