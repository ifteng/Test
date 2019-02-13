/* ==++==
 * 
 *    Copyright (c) SPD BANK. All rights reserved.
 *
 *    $Author: Sun Ming(sunming@jsruiyin.com)
 *    $Id: pb_api.h
 *   
 * ==--== */

#ifndef _PB_API_H_
#define _PB_API_H_
#define PB_API_EXPORTS 

#include <windows.h>

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN  
#endif

#if defined(_UNICODE) || defined(UNICODE)
    #error must use compile switch mbcs instead of unicode.
#endif

#ifdef PB_API_EXPORTS
    #define PB_API __declspec(dllexport) WINAPI 
#else
    #define PB_API __declspec(dllimport) WINAPI 
#endif

#ifdef __cplusplus
extern "C"{
#endif 

typedef DWORD PB_RESULT;

typedef DWORD PB_STATUS;

enum LOGLEVEL
{
	LOGLEVEL_NULL   = 0,
	LOGLEVEL_ERR    = 1,
	LOGLEVEL_ENTER  = 2,
	LOGLEVEL_DETAIL = 3
};

#define PB_OK   0

/*****************************************************************************/
/*                       综合屏                                              */
/*****************************************************************************/

#define PB_COMP_PORT_OPEN_ERROR         1001
#define PB_COMP_DEVICE_INIT_ERROR       1002
#define PB_COMP_NOT_SUPPORTED           1003
#define PB_COMP_NOT_INITIALIZED         1004
#define PB_COMP_COMMUNICATION_ERROR     1005
#define PB_COMP_BUSY                    1006
#define PB_COMP_INTERNAL_ERROR          1049
#define PB_COMP_INVALID_CONFIG_XML      1051
#define PB_COMP_INVALID_ADDRESS         1052
#define PB_COMP_INVALID_COMMAND_XML     1053

PB_RESULT PB_API COMP_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API COMP_Show(IN LPCSTR lpszAddress, IN LPCSTR lpszCommandXml);
PB_RESULT PB_API COMP_GetStatus(OUT PB_STATUS *lpStatus);

/*****************************************************************************/
/*                       条屏                                                */
/*****************************************************************************/

#define PB_BERR_PORT_OPEN_ERROR         2001
#define PB_BERR_DEVICE_INIT_ERROR       2002
#define PB_BERR_NOT_SUPPORTED           2003
#define PB_BERR_NOT_INITIALIZED         2004
#define PB_BERR_COMMUNICATION_ERROR     2005
#define PB_BERR_BUSY                    2006
#define PB_BERR_INTERNAL_ERROR          2049
#define PB_BERR_INVALID_CONFIG_XML      2051
#define PB_BERR_INVALID_ADDRESS         2052
#define PB_BERR_INVALID_COMMAND_XML     2053

PB_RESULT PB_API BERR_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API BERR_Show(IN LPCSTR lpszCounterNo, IN LPCSTR lpszCommandXml);
PB_RESULT PB_API BERR_GetStatus(OUT PB_STATUS *lpStatus);

/*****************************************************************************/
/*                       二代身份证阅读器                                    */
/*****************************************************************************/

#define PB_IDCR_PORT_OPEN_ERROR         3001
#define PB_IDCR_DEVICE_INIT_ERROR       3002
#define PB_IDCR_NOT_SUPPORTED           3003 
#define PB_IDCR_NOT_INITIALIZED         3004
#define PB_IDCR_COMMUNICATION_ERROR     3005
#define PB_IDCR_BUSY                    3006
#define PB_IDCR_INVALID_OPERATION       3011
#define PB_IDCR_INTERNAL_ERROR          3049
#define PB_IDCR_INVALID_CONFIG_XML      3051
#define PB_IDCR_INVALID_INDEX           3052
#define PB_IDCR_INSUFFICIENT_BUFFER     3053

#define PB_IDCR_IDX_NAME                1
#define PB_IDCR_IDX_GENDER	            2
#define PB_IDCR_IDX_NATION              3 
#define PB_IDCR_IDX_BIRTHDAY            4
#define PB_IDCR_IDX_ADDRESS             5
#define PB_IDCR_IDX_ID                  6
#define PB_IDCR_IDX_DEPARTMENT          7
#define PB_IDCR_IDX_START_DATE          8
#define PB_IDCR_IDX_END_DATE            9
#define PB_IDCR_IDX_RESERVED            10
#define PB_IDCR_IDX_APPADDRESS1         11
#define PB_IDCR_IDX_PHOTO               12


PB_RESULT PB_API IDCR_Initialize(IN LPCSTR lpszConfigXml);
int PB_API Initialize(int Buate, int Port);
PB_RESULT PB_API IDCR_BeginRead(void);
PB_RESULT PB_API IDCR_DataAvailable(OUT BOOL *lpAvailable);
PB_RESULT PB_API IDCR_ReadData(IN DWORD dwIndex, OUT LPVOID lpBuffer, 
    IN DWORD dwBufferSize, OUT DWORD * lpNumberOfBytesRead);
PB_RESULT PB_API IDCR_CancelRead(void);
PB_RESULT PB_API IDCR_GetStatus(OUT PB_STATUS *lpStatus);


/*****************************************************************************/
/*                       评价器                                              */
/*****************************************************************************/

#define PB_APPR_PORT_OPEN_ERROR         4001
#define PB_APPR_DEVICE_INIT_ERROR       4002
#define PB_APPR_NOT_SUPPORTED           4003
#define PB_APPR_NOT_INITIALIZED         4004
#define PB_APPR_COMMUNICATION_ERROR     4005
#define PB_APPR_BUSY                    4006
#define PB_APPR_INVALID_OPERATION       4011
#define PB_APPR_INTERNAL_ERROR          4049
#define PB_APPR_INVALID_CONFIG_XML      4051
#define PB_APPR_INVALID_ADDRESS         4052
#define PB_APPR_INVALID_USER_XML        4053

#define PB_APPR_SOUND_WELCOME           1
#define PB_APPR_SOUND_APPRAISE          2
#define PB_APPR_SOUND_THANKS            3
#define PB_APPR_SOUND_GOODBYE           4

#define PB_APPR_MESSAGE_WELCOME         1
#define PB_APPR_MESSAGE_APPRAISE        2
#define PB_APPR_MESSAGE_THANKS          3
#define PB_APPR_MESSAGE_GOODBYE         4

#define PB_APPR_DISSATISFIED            1
#define PB_APPR_NEUTRAL                 2
#define PB_APPR_SATISFIED               3
#define PB_APPR_VERY_SATISFIED          4

PB_RESULT PB_API APPR_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API APPR_Login(IN LPCSTR lpszCounterNo, IN LPCSTR lpszUserXml);
PB_RESULT PB_API APPR_PlaySound(IN LPCSTR lpszCounterNo,IN DWORD dwSoundIndex);
PB_RESULT PB_API APPR_ShowMessage(IN LPCSTR lpszCounterNo,IN DWORD dwMessageIndex);
PB_RESULT PB_API APPR_BeginRead(IN LPCSTR lpszCounterNo);
PB_RESULT PB_API APPR_DataAvailable(IN LPCSTR lpszCounterNo, OUT BOOL *lpAvailable);
PB_RESULT PB_API APPR_ReadData(IN LPCSTR lpszCounterNo, OUT DWORD *lpAppraisal);
PB_RESULT PB_API APPR_CancelRead(IN LPCSTR lpszCounterNo);
PB_RESULT PB_API APPR_Logout(IN LPCSTR lpszCounterNo);
PB_RESULT PB_API APPR_GetStatus(OUT PB_STATUS *lpStatus);

/*****************************************************************************/
/*                       读卡器                                              */
/*****************************************************************************/

#define PB_CRDR_PORT_OPEN_ERROR         5001
#define PB_CRDR_DEVICE_INIT_ERROR       5002
#define PB_CRDR_NOT_SUPPORTED           5003
#define PB_CRDR_NOT_INITIALIZED         5004
#define PB_CRDR_COMMUNICATION_ERROR     5005
#define PB_CRDR_BUSY                    5006
#define PB_CRDR_INVALID_OPERATION       5011
#define PB_CRDR_INTERNAL_ERROR          5049
#define PB_CRDR_INVALID_CONFIG_XML      5051
#define PB_CRDR_INSUFFICIENT_BUFFER     5052

#define PB_CRDR_TRACK2                  2
#define PB_CRDR_TRACK3                  3
#define PB_CRDR_TRACK2_AND_TRACK3       23

PB_RESULT PB_API CRDR_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API CRDR_BeginRead(IN DWORD dwTrack);
PB_RESULT PB_API CRDR_DataAvailable(OUT BOOL *lpAvailable);
PB_RESULT PB_API CRDR_ReadData(OUT LPVOID *lpBuffer, IN DWORD dwBufferSize,
    OUT DWORD *lpNumberOfBytesRead);
PB_RESULT PB_API CRDR_CancelRead(void);
PB_RESULT PB_API CRDR_GetStatus(OUT PB_STATUS *lpStatus);

/*****************************************************************************/
/*                       语音设备                                            */
/*****************************************************************************/

#define PB_VOIC_PORT_OPEN_ERROR         6001
#define PB_VOIC_DEVICE_INIT_ERROR       6002
#define PB_VOIC_NOT_SUPPORTED           6003
#define PB_VOIC_NOT_INITIALIZED         6004
#define PB_VOIC_COMMUNICATION_ERROR     6005
#define PB_VOIC_BUSY                    6006
#define PB_VOIC_INTERNAL_ERROR          6049
#define PB_VOIC_INVALID_CONFIG_XML      6051
#define PB_VOIC_INVALID_SOUND_XML       6052

PB_RESULT PB_API VOIC_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API VOIC_PlaySound(IN LPCSTR lpszSoundXml);
PB_RESULT PB_API VOIC_GetStatus(OUT PB_STATUS *lpStatus);


/*****************************************************************************/
/*                       热敏打印机                                          */
/*****************************************************************************/

#define PB_PRNT_PORT_OPEN_ERROR         7001
#define PB_PRNT_DEVICE_INIT_ERROR       7002
#define PB_PRNT_NOT_SUPPORTED           7003
#define PB_PRNT_NOT_INITIALIZED         7004
#define PB_PRNT_COMMUNICATION_ERROR     7005
#define PB_PRNT_BUSY                    7006
#define PB_PRNT_PAPER_JAMMED            7021
#define PB_PRNT_PAPER_OUT               7022
#define PB_PRNT_HEAD_ERROR              7023
#define PB_PRNT_STACK_FULL              7024
#define PB_PRNT_CUT_ERROR               7025
#define PB_PRNT_INTERNAL_ERROR          7049
#define PB_PRNT_INVALID_CONFIG_XML      7051
#define PB_PRNT_INVALID_SETUP_XML       7052
#define PB_PRNT_DATA_FORMAT_ERROR       7053
#define PB_PRNT_LOGO_ERROR              7054

PB_RESULT PB_API PRNT_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API PRNT_Setup(IN LPCSTR lpszSetupXml);
PB_RESULT PB_API PRNT_PrintData(IN LPCSTR lpszData);
PB_RESULT PB_API PRNT_Cut(void);
PB_RESULT PB_API PRNT_GetStatus(OUT PB_STATUS *lpStatus);

/*****************************************************************************/
/*                       IC读卡器                                            */
/*****************************************************************************/

#define PB_ICCR_PORT_OPEN_ERROR         8001
#define PB_ICCR_DEVICE_INIT_ERROR       8002
#define PB_ICCR_NOT_SUPPORTED           8003
#define PB_ICCR_NOT_INITIALIZED         8004
#define PB_ICCR_COMMUNICATION_ERROR     8005
#define PB_ICCR_BUSY                    8006
#define PB_ICCR_INVALID_OPERATION       8011
#define PB_ICCR_INTERNAL_ERROR          8049
#define PB_ICCR_INVALID_CONFIG_XML      8051
#define PB_ICCR_INSUFFICIENT_BUFFER     8052



PB_RESULT PB_API ICCR_Initialize(IN LPCSTR lpszConfigXml);
PB_RESULT PB_API ICCR_BeginRead(void);
PB_RESULT PB_API ICCR_DataAvailable(OUT BOOL *lpAvailable);
PB_RESULT PB_API ICCR_ReadData(IN DWORD dwIndex, OUT LPVOID lpBuffer, IN DWORD dwBufferSize, OUT DWORD * lpNumberOfBytesRead);
PB_RESULT PB_API ICCR_CancelRead(void);

#ifdef __cplusplus
}
#endif

#endif


