#pragma once
/************************Http: Get��Post�ķ�װ��***************/  

#include   "wininet.h"    
#include   "afxinet.h"  

/*********************�ඨ��***********************************/  
class   CHttpClient        
{    
public:    
	CHttpClient(void);
	~CHttpClient(void);

	void addParam(CString name, CString value);    
	CString doPost(CString href);    
	CString doGet(CString href);     
private:    
	CString CONTENT;    
	int CL;    
	CStringList values;    
	CStringList names;    
};   

