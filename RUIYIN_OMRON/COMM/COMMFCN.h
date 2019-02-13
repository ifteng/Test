#ifndef __JSRCB_DEV_DRIVE_COMM_FUNCTION_H__
#define __JSRCB_DEV_DRIVE_COMM_FUNCTION_H__

#ifdef DEBUG
#pragma comment(lib, "HsBased.lib")
#else
#pragma comment(lib, "HsBase.lib")
#endif

#include "PB_API.h"
#include "LOG2.H"
#include "CommonFun.h"
#include "tinyxml.h"
#include "RS232C.H"
#include "sharememory.h"

#include "TCPServer.h"
#include "TCPClient.h"


/************************************************************************/
/*                             ͨ�ú�����                               */
/************************************************************************/
#define LOG_JSRCB Jsrcb_log
#define LOG_LEVEL Jsrcb_level


/************************************************************************/
/*                              ��    ��                                */
/************************************************************************/
#define LOG_MSG "��Ϣ"
#define LOG_ERR "����"

#define TIMEOUT_POLLING (3000)
/************************************************************************/
/*                               P R N T                                */
/************************************************************************/
#define PRNT_CODE_FONT		"FONT"
#define FONT_BOLD_ON		"BOLD-ON"
#define FONT_BOLD_OFF		"BOLD-OFF"
#define FONT_SLANT_ON		"SLANT-ON"
#define FONT_SLANT_OFF		"SLANT-OFF"
#define FONT_SIZE_NORMAL	"SIZE-NORMAL"
#define FONT_SIZE_LARGE		"SIZE-LARGE"
#define FONT_SIZE_SMALL		"SIZE-SMALL"

#define PRNT_CODE_TEXT		"TEXT"
#define TEXT_ALIGN_LEFT		"ALIGN-LEFT"
#define TEXT_ALIGN_CENTER	"ALIGN-CENTER"
#define TEXT_ALIGN_RIGHT	"ALIGN-RIGHT"
#define TEXT_AUTOWARP_ON	"AUTOWARP-ON"
#define TEXT_AUTOWARP_OFF	"AUTOWARP-OFF"

#define PRNT_CODE_CTRL		"CTRL"
#define CTRL_CRLF			"CRLF"
#define CTRL_LT				"LT"
#define CTRL_GT				"GT"
#define CTRL_LOGO			"LOGO"
#define CTRL_INIT			"INIT"

#define PRNT_CODE_BARCODE	"BARCODE"
#define BARCODE_ON			"ON"
#define BARCODE_OFF			"OFF"

#define ERR_TRY_COUNT		(3)

/************************************************************************/
/*                               B E E R                                */
/************************************************************************/
#define BEER_NUMBER			"NUMBER"
#define BEER_WELCOME		"WELCOME"
#define BEER_PAUSE			"PAUSE"
#define BEER_TRANSACTING	"TRANSACTING"
#define BEER_TEXT			"TEXT"
#define BEER_INIT			"INIT"

#define BEER_POWER			(0x11)
#define BEER_CURR			(0x4B)

#define BEER_NUMBERSTR		"��%s��"
/************************************************************************/
/*                               C O M P                                */
/************************************************************************/
#define COMP_NUMBER			"NUMBER"
#define COMP_ADVERTISING	"ADVERTISING"
#define COMP_SETADVERTISING	"SETADVERTISING"
#define COMP_TEXT			"TEXT"

#define COMP_NUMBERSTR		"��%s��%s�Ŵ���"

/// TRADE
#define MSG_CALLNO_INFO 5006 

/************************************************************************/
/*                               I C C R                                */
/************************************************************************/
enum ICCR_INDEX
{
	PB_ICCR_IDX_ACCOUNT = 1,
	PB_ICCR_IDX_NAME = 2,
	PB_ICCR_IDX_ID_TYPE = 3,
	PB_ICCR_IDX_ID = 4
};
/************************************************************************/
/*                              ��־�ļ�                                */
/************************************************************************/
#define COMPLOG	("COMP."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define BERRLOG	("BERR."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define IDCRLOG	("IDCR."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define APPRLOG	("APPR."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define CRDRLOG	("CRDR."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define VOICLOG	("VOIC."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define PRNTLOG	("PRNT."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define CALLLOG	("CALL."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define ICCRLOG	("ICCR."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")
#define OMRONLOG ("OMRON."+(CTime::GetCurrentTime()).Format("%Y%m%d")+".LOG")

#define RETENTIONLOGDAYS	(30)
/************************************************************************/
/*                            ��   ��   ��                              */
/************************************************************************/
/// PRNT
typedef struct PRNT_FONT
{
	BOOL BOLD_ON;			/// �򿪴���ģʽ
	BOOL BOLD_OFF;			/// �رմ���ģʽ
	BOOL SLANT_ON;			/// ��б��ģʽ
	BOOL SLANT_OFF;			/// �ر�б��ģʽ
	BOOL SIZE_NORMAL;		/// ������С����
	BOOL SIZE_LARGE;		/// ������
	BOOL SIZE_SMALL;		/// С����
	PRNT_FONT();
	void Reset();
	BOOL operator << (LPCSTR pFont);
}*LPPRNT_FONT;
typedef struct PRNT_TEXT
{
	BOOL ALIGN_LEFT;		/// �����
	BOOL ALIGN_CENTER;		/// ���ж���
	BOOL ALIGN_RIGHT;		/// �Ҷ���
	BOOL AUTOWARP_ON;		/// ���Զ�����ģʽ
	BOOL AUTOWARP_OFF;		/// �ر��Զ�����ģʽ
	PRNT_TEXT();
	void Reset();
	BOOL operator << (LPCSTR pFont);
}*LPPRNT_TEXT;
typedef struct PRNT_CTRL
{
	BOOL CRLF;				/// �س�����      
	BOOL LT;				/// ��ӡһ��С�ں�
	BOOL GT;				/// ��ӡһ�����ں�
	BOOL LOGO;				/// ��ӡLOGO
	BOOL INIT;				/// ��ʼ�����������ģʽ
	PRNT_CTRL();
	void Reset();
	BOOL operator << (LPCSTR pFont);
}*LPPRNT_CTRL;
typedef struct PRNT_BARCODE
{
	BOOL ON;				/// ������ģʽ
	BOOL OFF;				/// �ر�����ģʽ
	PRNT_BARCODE();
	void Reset();
	BOOL operator << (LPCSTR pFont);
}*LPPRNT_BARCODE;

/// BEER
typedef struct BEER_SHOW
{
	char szMode[16];
	char szData[1024];
	UINT uDisplayMode;
	UINT uTimeSwitchtoNormal;
	UINT uWinID;
	BEER_SHOW();
	BEER_SHOW(LPCSTR pMode,LPCSTR pData);
	void Reset();
	int Set(LPCSTR pMode,LPCSTR pData,LPCSTR pStr);
}*LPBEER_SHOW;

/// COMP
enum SOCKTYPE{UDP=0,TCP=1,WEB=2};
typedef struct COMP_SHOW
{
	char szMode[16];
	char szData[1024];
	UINT uDisplayMode;
	UINT uTimeSwitchtoNormal;
	UINT uWinID;
	SOCKTYPE nSockType;
	COMP_SHOW();
	COMP_SHOW(LPCSTR pMode,LPCSTR pData);
	void Reset();
	int Set(LPCSTR pMode,LPCSTR pData,LPCSTR pStr);
}*LPCOMP_SHOW;

/// RETURN VALUE
typedef struct RETURN_VALUE
{
	BOOL bRet;
	char szData[1024];
	RETURN_VALUE();
	void Reset();
}*LPRETURN_VALUE;


/************************************************************************/
/*                            ȫ�ֺ�������                              */
/************************************************************************/
BOOL Jsrcb_log(BYTE bType, LPCTSTR strFile, LPCTSTR lpszFormat, ...);
BOOL Jsrcb_level(UINT uLevel);

RETURN_VALUE ExecuteSendAndRecv(const char* pIP,UINT uPort,LPBYTE pSend,LPBYTE* pRecv,UINT uTimeout);

#endif // __JSRCB_DEV_DRIVE_COMM_FUNCTION_H__
