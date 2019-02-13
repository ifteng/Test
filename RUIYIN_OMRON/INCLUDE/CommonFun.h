#ifndef _COMMON_FUN_H_  
#define _COMMON_FUN_H_ 

#include "stdafx.h"
#include <string> 
#include <vector>
#include <afxinet.h>

using namespace std;

/************************************************************************
* WM_USER: 0x0400-0x7FFF 
************************************************************************/

typedef enum{DATE_LONG,DATE_LONG2 ,DAY_NORMAL, TIME_NORMAL, DATE_NORMAL, DAY_SHORT, DAY_LONG, TIME_LONG, TIME_SHORT1,TIME_SHORT2,MONTH_NORMAL, MONTH_LONG, BANK_NORMAL}TIME_TYPE;

std::vector<CString> SplitString(CString strInfo, CString strFlag);
std::vector<string> Splitstring(string strInfo, string strFlag);

short StrCopy(char* szDest, const char* szSrc, int nDestMaxLen);
short MemCopy(void* pDest, const void* pSrc, int nSrcLen, int nDestMaxLen);

// ת����BCD�ִ�
int ConvertBCD(BYTE* pSrc, int nLen, BYTE* pDest);
// BCD�ִ�ת��Ϊ������
int ConvertBIN(BYTE* pSrc, BYTE* pDest);

//��ȡ��ǰʱ�䴮
string GetCurTime(TIME_TYPE nType, long lSpan=0);
//���ص�ǰʱ��� 1970-1-1 00:00:00 ֮�������
unsigned long GetCurTime();
/************************************************************************\
* �Ƚ�ʱ���                                                             *
* ��Σ�%d-%d-%d %d:%d:%d                                                *
* ����ֵ��>0��ʾ����ʱ����ڱȽ�ʱ��N��/�뼴tCompareΪN��/��ǰ����       *
\************************************************************************/
int CompareDay(CTime tCompare);
int CompareSecond(CTime tCompare);
int CompareDay(CString strCompare);
int CompareSecond(CString strCompare);

//����ϵͳ
BOOL Reboot();
//�ر�ϵͳ
BOOL ShutDown();
//����ϵͳ��ǰʱ��(��ʽ����Ϊ��2012-12-01 12:00:00)
BOOL SetSysTime(char* pCurTime);

//�ر�����ָ������
BOOL KillProcess(CString  strKillProcessName);
//�ر�ָ������
BOOL KillProcess(DWORD  dwProcessID);
// ���ص�һ������ID δ�ҵ�����0 ʧ��-1
long FindProcess(CString  strProcessName);

// �������� ģ̬�����޷�����
BOOL StartProcess(CString strFile, CString strParam, UINT uShow, BOOL bBlock);
BOOL StartProcess(CString strFile, CString strParam, UINT uShow, BOOL bBlock, DWORD* dwExitCode);
// �������̣�ֱ����̨���� ȷ���������� ��Ҫ�����������������
BOOL StartProcess(CString strFile, BOOL bHide);
BOOL StartProcess2(CString strFile, BOOL bHide);

// ��ע�����Ϣ
CString ReadREG(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpName);
// дע���
BOOL WriteREG(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpName, LPCTSTR lpValue);

// ���ش���ʣ��ռ䣨��λ�ֽڣ� -1 ʧ��
ULONGLONG GetDiskSpace(char* pDir);

// ��ȡָ��Ŀ¼��С
unsigned long GetDirSize(char* pDir);
// ��ȡCPUID
CString GetCPUID();
// ��ȡMAC��ַ��ȡ������������⣨���������ߣ�MAC��
CString GetMacSum();
// ȡ GetCPUID() �� GetMacSum() ���Ľ��
CString GetHsKey();

void ConvertUtf8ToGBK(CString& strUtf8);
void ConvertGBKToUtf8(CString& strGBK);

BOOL CreateAllDirectory(LPCTSTR lpszPath);
CString GetFullPath(CString sFileName);
std::vector<CString> FindFileFullPath(CString strFoldername);
std::vector<CString> FindFileName(CString strFoldername);


char* GetExePath();
HMODULE WINAPI ModuleFromAddress(PVOID pv);
HMODULE GetCurModule();
int GetCurModulePath();
char* GetModuleDisk();
char* GetModulePath();
char* GetModuleName();
char* GetModuleNameKey();
BOOL CheckFileExist(CString strFilePath);

CString GetLastSysErr();
CString GetLocalIpaddress();

BOOL DeleteLog(LPTSTR strPath,UINT uDays);
void DeleteDirectoryForce(CString directory_path);

BYTE CharXORChar(LPBYTE pdata,int nLen);
BYTE Plus(LPBYTE pdata,int nLen,BYTE bChk);

/// ��GBK����ת���ɶ��ֽڣ�GBK���롰������BB B6��ת���ɡ�0B 0B 0B 06����
void GbkTODoubleGbk(char* pIn,LPBYTE pOut,UINT uIn,UINT& uOut);
/// ��GBK����ת���ɶ��ֽڣ�GBK���롰��1����BB B6 31��ת���ɡ�BB B6 00 31����
void GbkTOSplitGbk(char* pIn,LPBYTE pOut,UINT uIn,UINT& uOut);

BOOL InputEnglish();
BOOL InputChinese();

void CRC(LPBYTE ptrData,UINT nlen,LPBYTE ptrCRC);

int HTTP_Download(LPCTSTR pFileURLInServer, //�������ļ���URL
			 LPCTSTR pFileLocalFullPath);
int HTTP_UploadFile(LPCTSTR pURL, //��������ϴ�������ҳ���URL
			   LPCTSTR pLocalFileName);

CString GetUUID();
CTimeSpan CompareTime(CString strCompare1,CString strCompare2);


#endif;