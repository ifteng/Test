#pragma once

typedef struct IL{
	char szlID[15];  //���뷨����
	char szName[100];  //���뷨��˵������
	IL *pNext;
	IL()
	{
		memset(szlID,0x00,sizeof(szlID));
		memset(szName,0x00,sizeof(szName));
		pNext = NULL;
	}
}*LPIL;

class CInputLanguage
{
public:
	CInputLanguage(void);
	~CInputLanguage(void);
	IL *m_pILHead;
	BOOL LoadInputLanguage(void);
	BOOL SelectInputLanguage(IL *pIL);
	void Clear(void);
	IL* GetInputLanguageList(void);
};




