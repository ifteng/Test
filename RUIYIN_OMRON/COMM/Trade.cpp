#include "stdafx.h"
#include "Trade.h"
#include "TCPClient.h"
#include "CommonFun.h"

#define TRADE_LOCK Lock()
#define TRADE_UNLOCK UnLock()

CTrade::CTrade(void)
{
	m_bCon = FALSE;
}


CTrade::~CTrade(void)
{
}

BOOL CTrade::ExecuteSendAndRecv(const char* pIP,UINT uPort,LPBYTE pSend,LPBYTE* pRecv,UINT uTimeout)
{
	CTCPClient tcp;
	LPBASE_MSG_PACK pTempPack = NULL;
	tcp.SetSocketTimeOut((int)uTimeout);
	LPBASE_QUERY_MSG pQuery = (LPBASE_QUERY_MSG)((LPBASE_MSG_PACK)pSend)->pszData;
	MakeTerminalID(&pQuery);
	MakeMAC(&pQuery);
	int nResult = tcp.ExecuteSendAndRecv(pIP, uPort,(LPBASE_MSG_PACK)pSend,(LPBASE_MSG_PACK*)pRecv,USE_BASE_TYPE_HEADER);
	if (nResult)
	{
		m_strLastErr = tcp.GetLastError();
	}
	else
	{

	}
	return nResult ? FALSE:TRUE;
}

BOOL CTrade::SingleExecuteSendAndRecv(const char* pIP,UINT uPort,LPDEV_CONTROL_QUERY_MSG pSend,LPDEV_CONTROL_RETURN_MSG pRecv,UINT uTimeout)
{
	CTCPClient client;
	BASE_MSG_PACK SendPack;
	LPBASE_MSG_PACK pRecvPack = NULL;

	SendPack.nSize = pSend->m_head.m_head.uSize;
	SendPack.pszData = (char*)pSend;

	MakeTerminalID((LPBASE_QUERY_MSG*)&pSend);
	CString strLog;
	strLog.Format("[%s:%d][>>>>]",pIP,uPort);
	client.SetSocketTimeOut(uTimeout);
	MakeMAC((LPBASE_QUERY_MSG*)&pSend);
	short nRet = client.ExecuteSendAndRecv(pIP, uPort, &SendPack, &pRecvPack, USE_BASE_TYPE_HEADER);

	if(nRet)
	{
		m_strLastErr = client.GetLastError();
		strLog.Format("[%s:%d][ERR]",pIP,uPort);
		SAFE_DELETE_PACK(pRecvPack);
		return FALSE;
	}
	if(!(pRecvPack && pRecvPack->pszData))
	{
		m_strLastErr="接收数据错误";
		strLog.Format("[%s:%d][ERR]",pIP,uPort);
		SAFE_DELETE_PACK(pRecvPack);
		return FALSE;
	}
	strLog.Format("[%s:%d][<<<<]",pIP,uPort);
	memcpy((char*)pRecv,pRecvPack->pszData,sizeof(DEV_CONTROL_RETURN_MSG)-4);
	if(pRecv->m_uLen)
	{
		pRecv->m_pData = new BYTE [pRecv->m_uLen+1];
		memset(pRecv->m_pData,0x00,pRecv->m_uLen+1);
		memcpy(pRecv->m_pData,
			pRecvPack->pszData+sizeof(DEV_CONTROL_RETURN_MSG)-4,pRecv->m_uLen);
	}

	SAFE_DELETE_PACK(pRecvPack);
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL CTrade::Connect(const char* pIP,UINT uPort,int nType)
{
	BOOL bInit = m_longconclient.Init(NULL, nType);
	if (bInit == FALSE)
	{
		m_strLastErr = m_longconclient.GetLastError();
		return FALSE;
	}

	BOOL bConnect = m_longconclient.ConnectToServer(pIP, uPort);
	if (bConnect == FALSE)
	{
		m_strLastErr = m_longconclient.GetLastError();
		return FALSE;
	}
	m_longconclient.SetSocketTimeOut(INFINITE);
	m_bCon = TRUE;
	return TRUE;
}

BOOL CTrade::ExecuteSendAndRecv_LongCon(LPDEV_CONTROL_QUERY_MSG pSend,LPDEV_CONTROL_RETURN_MSG pRecv)
{
	if(ChkConnect() == FALSE) return FALSE;

	TRADE_LOCK;

	// 发送包
	BASE_MSG_PACK SendPack;
	// 返回包
	LPBASE_MSG_PACK pRecvPack = NULL;

	SendPack.nSize = pSend->m_head.m_head.uSize;
	SendPack.pszData = (char*)pSend;

	MakeTerminalID((LPBASE_QUERY_MSG*)&pSend);
	MakeMAC((LPBASE_QUERY_MSG*)&pSend);

	if (!m_longconclient.AddSendMsg(&SendPack))
	{
		m_strLastErr = m_longconclient.GetLastError();
		goto FAIL;
	}
	pRecvPack = m_longconclient.GetMsgPack();
	if (pRecvPack == NULL)
	{
		m_strLastErr = m_longconclient.GetLastError();
		goto FAIL;
	}
	if (pRecvPack->pszData == NULL)
	{
		m_strLastErr = "返回包报文内容为‘空’";
		goto FAIL;
	}
	if (((LPBASE_MSG)pRecvPack->pszData)->uType == MSG_SOCKET_ERROR)
	{
		SAFE_DELETE_PACK(pRecvPack);
		m_strLastErr.Format("SOCKET错误:%s",m_longconclient.GetLastError());
		goto FAIL;
	}

	// 将返回包里面的内容传出函数外
	memcpy((char*)pRecv,pRecvPack->pszData,sizeof(DEV_CONTROL_RETURN_MSG)-4);
	if(pRecv->m_uLen)
	{
		pRecv->m_pData = new BYTE [pRecv->m_uLen+1];
		memset(pRecv->m_pData,0x00,pRecv->m_uLen+1);
		memcpy(pRecv->m_pData,
			pRecvPack->pszData+sizeof(DEV_CONTROL_RETURN_MSG)-4,pRecv->m_uLen);
	}

	SAFE_DELETE_PACK(pRecvPack);

	TRADE_UNLOCK;
	return TRUE;
FAIL:
	TRADE_UNLOCK;
	DisConnect();
	return FALSE;
}

BOOL CTrade::ExecuteSendAndRecv_LongCon(LPBYTE pSend, DWORD dSendlen, LPBYTE& pRecv, DWORD& dRecvLen)
{
	if (ChkConnect() == FALSE) return FALSE;

	TRADE_LOCK;

	// 发送包
	BASE_MSG_PACK SendPack;
	// 返回包
	LPBASE_MSG_PACK pRecvPack = NULL;

	SendPack.nSize = dSendlen;
	SendPack.pszData = (char*)pSend;

	if (!m_longconclient.AddSendMsg(&SendPack))
	{
		m_strLastErr = m_longconclient.GetLastError();
		goto FAIL;
	}
	pRecvPack = m_longconclient.GetMsgPack();
	if (pRecvPack == NULL)
	{
		m_strLastErr = m_longconclient.GetLastError();
		goto FAIL;
	}
	if (pRecvPack->pszData == NULL)
	{
		m_strLastErr = "返回包报文内容为‘空’";
		goto FAIL;
	}

	// 将返回包里面的内容传出函数外
	pRecv = new BYTE[pRecvPack->nSize+1];
	memset(pRecv,0x00,pRecvPack->nSize+1);
	memcpy(pRecv,pRecvPack->pszData,pRecvPack->nSize);
	dRecvLen = pRecvPack->nSize;

	SAFE_DELETE_PACK(pRecvPack);

	TRADE_UNLOCK;
	return TRUE;
FAIL:
	TRADE_UNLOCK;
	DisConnect();
	return FALSE;
}

BOOL CTrade::ChkConnect()
{
	m_strLastErr = m_bCon ? "":"长连接已断开";
	return m_bCon;
}

BOOL CTrade::DisConnect()
{
	m_longconclient.DisconnectServer();
	m_bCon = FALSE;
	return TRUE;
}

void CTrade::MakeMAC(LPBASE_QUERY_MSG* ppQuery)
{
	LPBASE_QUERY_MSG pQuery = *ppQuery;
	BYTE szCRC[2] = {0};
	CRC(((LPBYTE)pQuery)+sizeof(pQuery->m_head)+sizeof(pQuery->m_szMAC),
		pQuery->m_head.uSize-sizeof(pQuery->m_head)-sizeof(pQuery->m_szMAC),szCRC);
	BYTE szCRC1[8] = {0};
	BYTE szCRC2[8] = {0};
	for(UINT i=0;i<8;i++) pQuery->m_szMAC[i] = (szCRC[0] >> i) ^ (szCRC[1] >> i) + 0x30;
}

void CTrade::MakeMAC(LPBASE_RETURN_MSG* ppReturn)
{
	LPBASE_RETURN_MSG pReturn = *ppReturn;
	BYTE szCRC[2] = {0};
	CRC(((LPBYTE)pReturn)+sizeof(pReturn->m_head)+sizeof(pReturn->m_szMAC),
		pReturn->m_head.uSize-sizeof(pReturn->m_head)-sizeof(pReturn->m_szMAC),szCRC);
	BYTE szCRC1[8] = {0};
	BYTE szCRC2[8] = {0};
	for(UINT i=0;i<8;i++) pReturn->m_szMAC[i] = (szCRC[0] >> i) ^ (szCRC[1] >> i) + 0x30;
}

BOOL CTrade::DoCheckMAC(LPBASE_QUERY_MSG* ppRecv)
{
	LPBASE_QUERY_MSG pRecv = *ppRecv;
	BYTE szCRC[2] = {0};
	CRC(((LPBYTE)pRecv)+sizeof(pRecv->m_head)+sizeof(pRecv->m_szMAC),
		pRecv->m_head.uSize-sizeof(pRecv->m_head)-sizeof(pRecv->m_szMAC),szCRC);
	BYTE szCRCChk[8] = {0};
	BYTE szCRC1[8] = {0};
	BYTE szCRC2[8] = {0};
	for(UINT i=0;i<8;i++) szCRCChk[i] = (szCRC[0] >> i) ^ (szCRC[1] >> i) + 0x30;
	return memcmp(szCRCChk,pRecv->m_szMAC,sizeof(szCRC)) ? FALSE:TRUE;
}

void CTrade::MakeTerminalID(LPBASE_QUERY_MSG* ppQuery)
{
	LPBASE_QUERY_MSG pQuery = *ppQuery;
	strcpy(pQuery->m_szTerminalID,GetUUID());
}

void CTrade::MakeTerminalID(LPBASE_RETURN_MSG* ppReturn)
{
	LPBASE_RETURN_MSG pReturn = *ppReturn;
	strcpy(pReturn->m_szTerminalID,GetUUID());
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int CTCPClient::GetHeaderSize(int nType)	//获得包头大小，必须填写此函数
{
	if (nType == USE_BASE_TYPE_HEADER)
	{
		return sizeof(BASE_MSG);
	}
	else if (nType == USE_UNION_HEADER)
	{
		return 2;
	}
	else if (nType == USE_STRING_HEADER)
	{
		return 4;
	}
	else
	{
		return sizeof(BASE_MSG);
	}
}

UINT CTCPClient::GetPackSize(char* szHeaderPack, int nType)	//获得包的大小，包括包头长度。必须填写此函数
{
	if (nType == USE_BASE_TYPE_HEADER)
	{
		LPBASE_MSG pMsg = (LPBASE_MSG)szHeaderPack;
		return pMsg->uSize;
	}
	else if (nType == USE_UNION_HEADER)
	{
		unsigned char cH = (unsigned char)szHeaderPack[0];
		unsigned char cL = (unsigned char)szHeaderPack[1];
		return cH * 256 + cL + 2;
	}
	else if (nType == USE_STRING_HEADER)
	{
		return atoi(szHeaderPack)+4;
	}
	else
	{
		LPBASE_MSG pMsg = (LPBASE_MSG)szHeaderPack;
		return pMsg->uSize;
	}
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL CTrade::Lock()
{
	m_mutex.Lock();
	return TRUE;
}

BOOL CTrade::UnLock()
{
	m_mutex.UnLock();
	return TRUE;
}
