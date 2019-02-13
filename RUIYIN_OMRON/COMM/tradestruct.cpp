#include "stdafx.h"
#include "tradestruct.h"


//////////////////////////////////////////////////////////////////////////
/// 基本请求包
BASE_QUERY_MSG::BASE_QUERY_MSG()
{
	m_uDevType = 0xFF;
	memset(m_szMAC,0x00,sizeof(m_szMAC));
	memset(m_szTerminalID,0x00,sizeof(m_szTerminalID));
}

void BASE_QUERY_MSG::operator << (BASE_MSG head)
{
	m_head.uSize = head.uSize;
	m_head.uType = head.uType;
}

void BASE_QUERY_MSG::operator << (UINT type)
{
	m_uDevType = type;
}

//////////////////////////////////////////////////////////////////////////
/// 基本返回包
BASE_RETURN_MSG::BASE_RETURN_MSG()
{
	memset(m_szTerminalID,0x00,sizeof(m_szTerminalID));
	memset(szErrCode,0x00,sizeof(szErrCode));
	memset(m_szMAC,0x00,sizeof(m_szMAC));
}

void BASE_RETURN_MSG::operator << (BASE_MSG head)
{
	m_head.uSize = head.uSize;
	m_head.uType = head.uType;
}

//////////////////////////////////////////////////////////////////////////
/// 设备操作请求包
DEV_CONTROL_QUERY_MSG::DEV_CONTROL_QUERY_MSG()
{
	m_uLen = 0;
	m_pData = NULL;
}

DEV_CONTROL_QUERY_MSG::~DEV_CONTROL_QUERY_MSG()
{
	if(m_pData) delete[] m_pData;
	m_pData = NULL;
}

void DEV_CONTROL_QUERY_MSG::GetData(LPBYTE* _out_ pData,UINT  & _out_ uLen)
{
	uLen = m_uLen;
	*pData = (LPBYTE)(&m_pData);
}

//////////////////////////////////////////////////////////////////////////
/// 设备操作请求包
DEV_CONTROL_RETURN_MSG::DEV_CONTROL_RETURN_MSG()
{
	m_uLen = 0;
	m_pData = NULL;
}

DEV_CONTROL_RETURN_MSG::~DEV_CONTROL_RETURN_MSG()
{
	if(m_pData) delete[] m_pData;
	m_pData = NULL;
}

void DEV_CONTROL_RETURN_MSG::GetData(LPBYTE* _out_ pData,UINT  & _out_ uLen)
{
	uLen = m_uLen;
	*pData = (LPBYTE)(&m_pData);
}
