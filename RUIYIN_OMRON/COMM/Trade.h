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
	CTCPClient m_longconclient; // ������
	BOOL m_bCon; // ��ⳤ�����Ƿ��Ѿ��Ͽ�
	Mutex m_mutex;

public:
	CString GetLastError() {return m_strLastErr;}

	// ������-ͨ��
	BOOL ExecuteSendAndRecv(const char* pIP,UINT uPort,LPBYTE pSend,LPBYTE* pRecv,UINT uTimeout);
	// ������-��
	BOOL SingleExecuteSendAndRecv(const char* pIP,UINT uPort,LPDEV_CONTROL_QUERY_MSG pSend,LPDEV_CONTROL_RETURN_MSG pRecv,UINT uTimeout);
	// ������
	BOOL Connect(const char* pIP,UINT uPort,int nType = USE_BASE_TYPE_HEADER);
	BOOL ChkConnect();
	//////////////////////////////////////////////////////////////////////////
	/// ExecuteSendAndRecv_LongCon 
	/// LPBYTE pSend����Σ���Ҫ���͵�����
	/// DWORD dSendlen����Σ���Ҫ�������ݵĳ���
	/// LPBYTE pRecv�����Σ����ܵ�����
	///        ע��:��Ҫ�ͷ�
	/// DWORD& dRecvLen����Σ��������ݵĳ���
	//////////////////////////////////////////////////////////////////////////
	BOOL ExecuteSendAndRecv_LongCon(LPBYTE pSend, DWORD dSendlen, LPBYTE& pRecv, DWORD& dRecvLen);
	//////////////////////////////////////////////////////////////////////////
	/// ExecuteSendAndRecv_LongCon 
	/// LPDEV_CONTROL_QUERY_MSG pSend����Σ���Ҫ���͵�����
	/// LPDEV_CONTROL_RETURN_MSG pRecv�����Σ����ܵ�����
	///        ע��:����Ҫ�ͷ�
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

