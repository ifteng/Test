#pragma once

#include "tradestruct.h"
#include "TCPClient.h"
#include "sharememory.h"

class CTrade
{
public:
	CTrade(void);
	~CTrade(void);

private:
	CString m_strLastErr;
	CTCPClient m_longconclient; // 长连接
	BOOL m_bCon; // 检测长连接是否已经断开
	Mutex m_mutex;

public:
	CString GetLastError() {return m_strLastErr;}

	// 短连接-通用
	BOOL ExecuteSendAndRecv(const char* pIP,UINT uPort,LPBYTE pSend,LPBYTE* pRecv,UINT uTimeout);
	// 短连接-简化
	BOOL SingleExecuteSendAndRecv(const char* pIP,UINT uPort,LPDEV_CONTROL_QUERY_MSG pSend,LPDEV_CONTROL_RETURN_MSG pRecv,UINT uTimeout);
	// 长连接
	BOOL Connect(const char* pIP,UINT uPort,int nType = USE_BASE_TYPE_HEADER);
	BOOL ChkConnect();
	//////////////////////////////////////////////////////////////////////////
	/// ExecuteSendAndRecv_LongCon 
	/// LPBYTE pSend：入参，需要发送的数据
	/// DWORD dSendlen：入参，需要发送数据的长度
	/// LPBYTE pRecv：出参，接受的数据
	///        注意:需要释放
	/// DWORD& dRecvLen：入参，接受数据的长度
	//////////////////////////////////////////////////////////////////////////
	BOOL ExecuteSendAndRecv_LongCon(LPBYTE pSend, DWORD dSendlen, LPBYTE& pRecv, DWORD& dRecvLen);
	//////////////////////////////////////////////////////////////////////////
	/// ExecuteSendAndRecv_LongCon 
	/// LPDEV_CONTROL_QUERY_MSG pSend：入参，需要发送的数据
	/// LPDEV_CONTROL_RETURN_MSG pRecv：出参，接受的数据
	///        注意:不需要释放
	//////////////////////////////////////////////////////////////////////////
	BOOL ExecuteSendAndRecv_LongCon(LPDEV_CONTROL_QUERY_MSG pSend, LPDEV_CONTROL_RETURN_MSG pRecv);
	BOOL DisConnect();

public:
	void MakeMAC(LPBASE_QUERY_MSG* ppQuery);
	void MakeMAC(LPBASE_RETURN_MSG* ppReturn);

	void MakeTerminalID(LPBASE_QUERY_MSG* ppQuery);
	void MakeTerminalID(LPBASE_RETURN_MSG* ppReturn);

	BOOL DoCheckMAC(LPBASE_QUERY_MSG* ppRecv);

private:
	BOOL Lock();
	BOOL UnLock();
};

