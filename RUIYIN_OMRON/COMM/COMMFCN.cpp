#include "stdafx.h"
#include "COMMFCN.h"

UINT g_bLogType = LOGTYPE_DEBUG;
#define MAX_BUFF 1024
BOOL Jsrcb_log(BYTE bType, LPCTSTR strFile, LPCTSTR lpszFormat, ...)
{
	char* pBuf = (char*)malloc(MAX_BUFF+1);
	if(!pBuf) return FALSE;
	memset(pBuf, 0x00, MAX_BUFF+1);

	va_list argList;
	va_start(argList, lpszFormat);
	int iRet = _vsnprintf(pBuf, MAX_BUFF, lpszFormat, argList);
	if(iRet==-1)
	{
		char* pBuf2 = (char*)realloc(pBuf, 50*MAX_BUFF+1);
		memset(pBuf2, 0x00, 50*MAX_BUFF+1);
		if(pBuf2)
		{
			pBuf = pBuf2;
			_vsnprintf(pBuf, 50*MAX_BUFF, lpszFormat, argList);
		}
	}
	va_end(argList);

	BOOL bRet = FALSE;
	switch(g_bLogType & bType){
	case LOGTYPE_DEBUG:
		{
			CString strContent = "";
			strContent.Format("<<%s#%s>>	%s",GetCurTime(TIME_LONG,NULL).c_str(),LOG_MSG,pBuf);
			bRet = WriteFileEx(FILE_IMPORTANT, 
				GetPathLogFile(strFile,"").GetBuffer(0), strContent.GetBuffer(0), NULL);
		}
		break;
	case LOGTYPE_ERROR:
		{
			CString strContent = "";
			strContent.Format("<<%s#%s>>	%s",GetCurTime(TIME_LONG,NULL).c_str(),LOG_ERR,pBuf);
			bRet = WriteFileEx(FILE_IMPORTANT, 
				GetPathLogFile(strFile,"").GetBuffer(0), strContent.GetBuffer(0), NULL);
		}
		break;
	case LOGTYPE_SPECIAL:
		{
			CString strContent = "";
			strContent.Format("<<%s#%s>>	%s",GetCurTime(TIME_LONG,NULL).c_str(),LOG_MSG,pBuf);
			bRet = WriteFileEx(FILE_IMPORTANT, 
				GetPathLogFile(strFile,"").GetBuffer(0), strContent.GetBuffer(0), NULL);
		}
		break;
	default:
		break;
	}

	free(pBuf);
	return bRet;
}

BOOL Jsrcb_level(UINT uLevel)
{
	g_bLogType = uLevel;
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/// PRNT_FONT
//////////////////////////////////////////////////////////////////////////
PRNT_FONT::PRNT_FONT()
{
	Reset();
}
void PRNT_FONT::Reset()
{
	memset(this,0x00,sizeof(PRNT_FONT));
}
BOOL PRNT_FONT::operator << (LPCSTR pFont)
{
	SIZE_SMALL = TRUE;
	BOLD_OFF = TRUE;
	SLANT_OFF = TRUE;
	std::vector<CString> vct = SplitString(pFont,":");
	if(vct.size() < 2 || vct[0].Compare(PRNT_CODE_FONT)) return FALSE;
	Reset();
	std::vector<CString> vctEle = SplitString(vct[1],";");
	for (UINT i=0;i<vctEle.size();i++)
	{
		vctEle[i].MakeUpper();
		if(vctEle[i].Compare(FONT_BOLD_ON) == 0) BOLD_ON = TRUE;
		if(vctEle[i].Compare(FONT_BOLD_OFF) == 0) BOLD_OFF = TRUE;
		if(vctEle[i].Compare(FONT_SLANT_ON) == 0) SLANT_ON = TRUE;
		if(vctEle[i].Compare(FONT_SLANT_OFF) == 0) SLANT_OFF = TRUE;
		if(vctEle[i].Compare(FONT_SIZE_NORMAL) == 0) SIZE_NORMAL = TRUE;
		if(vctEle[i].Compare(FONT_SIZE_LARGE) == 0) SIZE_LARGE = TRUE;
		if(vctEle[i].Compare(FONT_SIZE_SMALL) == 0) SIZE_SMALL = TRUE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/// PRNT_TEXT
//////////////////////////////////////////////////////////////////////////
PRNT_TEXT::PRNT_TEXT()
{
	Reset();
}
void PRNT_TEXT::Reset()
{
	memset(this,0x00,sizeof(PRNT_TEXT));
}
BOOL PRNT_TEXT::operator << (LPCSTR pFont)
{
	std::vector<CString> vct = SplitString(pFont,":");
	if(vct.size() < 2 || vct[0].Compare(PRNT_CODE_TEXT)) return FALSE;
	Reset();
	std::vector<CString> vctEle = SplitString(vct[1],";");
	for (UINT i=0;i<vctEle.size();i++)
	{
		vctEle[i].MakeUpper();
		if(vctEle[i].Compare(TEXT_ALIGN_LEFT) == 0) ALIGN_LEFT = TRUE;
		if(vctEle[i].Compare(TEXT_ALIGN_CENTER) == 0) ALIGN_CENTER = TRUE;
		if(vctEle[i].Compare(TEXT_ALIGN_RIGHT) == 0) ALIGN_RIGHT = TRUE;
		if(vctEle[i].Compare(TEXT_AUTOWARP_ON) == 0) AUTOWARP_ON = TRUE;
		if(vctEle[i].Compare(TEXT_AUTOWARP_OFF) == 0) AUTOWARP_OFF = TRUE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/// PRNT_CTRL
//////////////////////////////////////////////////////////////////////////
PRNT_CTRL::PRNT_CTRL()
{
	Reset();
}
void PRNT_CTRL::Reset()
{
	memset(this,0x00,sizeof(PRNT_CTRL));
}
BOOL PRNT_CTRL::operator << (LPCSTR pFont)
{
	std::vector<CString> vct = SplitString(pFont,":");
	if(vct.size() < 2 || vct[0].Compare(PRNT_CODE_CTRL)) return FALSE;
	Reset();
	std::vector<CString> vctEle = SplitString(vct[1],";");
	for (UINT i=0;i<vctEle.size();i++)
	{
		vctEle[i].MakeUpper();
		if(vctEle[i].Compare(CTRL_CRLF) == 0) CRLF = TRUE;
		if(vctEle[i].Compare(CTRL_LT) == 0) LT = TRUE;
		if(vctEle[i].Compare(CTRL_GT) == 0) GT = TRUE;
		if(vctEle[i].Compare(CTRL_LOGO) == 0) LOGO = TRUE;
		if(vctEle[i].Compare(CTRL_INIT) == 0) INIT = TRUE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/// PRNT_BARCODE
//////////////////////////////////////////////////////////////////////////
PRNT_BARCODE::PRNT_BARCODE()
{
	Reset();
}
void PRNT_BARCODE::Reset()
{
	memset(this,0x00,sizeof(PRNT_BARCODE));
}
BOOL PRNT_BARCODE::operator << (LPCSTR pFont)
{
	std::vector<CString> vct = SplitString(pFont,":");
	if(vct.size() < 2 || vct[0].Compare(PRNT_CODE_BARCODE)) return FALSE;
	Reset();
	std::vector<CString> vctEle = SplitString(vct[1],";");
	for (UINT i=0;i<vctEle.size();i++)
	{
		vctEle[i].MakeUpper();
		if(vctEle[i].Compare(BARCODE_ON) == 0) ON = TRUE;
		if(vctEle[i].Compare(BARCODE_OFF) == 0) OFF = TRUE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/// BEER_SHOW
//////////////////////////////////////////////////////////////////////////
BEER_SHOW::BEER_SHOW()
{
	Reset();
}
BEER_SHOW::BEER_SHOW(LPCSTR pMode,LPCSTR pData)
{
	Reset();
	Set(pMode,pData,BEER_NUMBERSTR);
}
void BEER_SHOW::Reset()
{
	memset(this,0x00,sizeof(BEER_SHOW));
}
int BEER_SHOW::Set(LPCSTR pMode,LPCSTR pData,LPCSTR pStr)
{
	memset(szMode,0x00,sizeof(szMode));
	memset(szData,0x00,sizeof(szData));
	if(strcmp(pMode,BEER_NUMBER) == 0)
	{
		std::vector<CString> vct = SplitString(pData,"|");
		if(vct.size() < 2) return PB_BERR_INVALID_COMMAND_XML;
		sprintf(szData,pStr,vct[0]);
		uWinID = atoi(vct[1]);
	}
	else if(strcmp(pMode,BEER_WELCOME) == 0)
	{
		strcpy(szData,"»¶Ó­¹âÁÙ");
	}
	else if(strcmp(pMode,BEER_PAUSE) == 0)
	{
		strcpy(szData,"ÔÝÍ£·þÎñ");
	}
	else if(strcmp(pMode,BEER_TRANSACTING) == 0)
	{
		strcpy(szData,"ÕýÔÚ°ìÀí");
	}
	else if(strcmp(pMode,BEER_TEXT) == 0)
	{
		strcpy(szData,pData);
	}
	else if(strcmp(pMode,BEER_INIT) == 0)
	{
		strcpy(szData,pData);
	}
	else
	{
		return PB_BERR_INVALID_COMMAND_XML;
	}
	return PB_OK;
}

//////////////////////////////////////////////////////////////////////////
/// COMP_SHOW
//////////////////////////////////////////////////////////////////////////
COMP_SHOW::COMP_SHOW()
{
	Reset();
}
COMP_SHOW::COMP_SHOW(LPCSTR pMode,LPCSTR pData)
{
	Reset();
	Set(pMode,pData,COMP_NUMBERSTR);
}
void COMP_SHOW::Reset()
{
	memset(this,0x00,sizeof(BEER_SHOW));
}
int COMP_SHOW::Set(LPCSTR pMode,LPCSTR pData,LPCSTR pStr)
{
	memset(szMode,0x00,sizeof(szMode));
	memset(szData,0x00,sizeof(szData));
	if(strcmp(pMode,COMP_NUMBER) == 0)
	{
		std::vector<CString> vct = SplitString(pData,"|");
		if(vct.size() < 2) return PB_BERR_INVALID_COMMAND_XML;
		sprintf(szData,pStr,vct[0],vct[1]);
		uWinID = atoi(vct[1]);
	}
	else if(strcmp(pMode,COMP_ADVERTISING) == 0)
	{
		strcpy(szData,
			"»¶Ó­¹âÁÙ»¶Ó­¹âÁÙ"
			"»¶Ó­¹âÁÙ»¶Ó­¹âÁÙ"
			"»¶Ó­¹âÁÙ»¶Ó­¹âÁÙ"
			"»¶Ó­¹âÁÙ»¶Ó­¹âÁÙ");
	}
	else if(strcmp(pMode,COMP_SETADVERTISING) == 0)
	{
		std::vector<CString> vct = SplitString(pData,"#");
		for (UINT i=0;i<vct.size();i++) strcat(szData,vct[i].GetBuffer(0));
	}
	else if(strcmp(pMode,COMP_TEXT) == 0)
	{
		strcpy(szData,pData);
	}
	else
	{
		return PB_BERR_INVALID_COMMAND_XML;
	}
	return PB_OK;
}

//////////////////////////////////////////////////////////////////////////
/// RETURN_VALUE
//////////////////////////////////////////////////////////////////////////
RETURN_VALUE::RETURN_VALUE()
{
	Reset();
}

void RETURN_VALUE::Reset()
{
	bRet = TRUE;
	memset(szData,0x00,sizeof(szData));
}
