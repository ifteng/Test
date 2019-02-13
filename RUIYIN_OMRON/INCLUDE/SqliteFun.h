#if !defined(AFX_DBSQLITEFUN_H__DC7062D9_6FF6_4E17_BBD9_87ECF348542B__INCLUDED_)
#define AFX_DBSQLITEFUN_H__DC7062D9_6FF6_4E17_BBD9_87ECF348542B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBSqliteFun.h : header file
//

#include <sqlite3.h>
#include "CommTbl.h"

/////////////////////////////////////////////////////////////////////////////
typedef int (*Sqlite3_Callback)(void*,int,char**, char**);

class CSqliteFun
{
// Construction
public:
	CSqliteFun();
	virtual ~CSqliteFun();
private:
	sqlite3* m_pSqliteDB;
	std::string	 m_strError;	//רִָ��sql����������
	
public:
	int OpenDatabase(CString strDbPath);	///����Ϊ0 ��ʾ�򿪳ɹ�
	int CloseDatabase();					///����0 ��ʾ�رճɹ�
	int ExeSqlTransaction(std::string strSql);		///ִ��sql���
	int ExeSqlTransaction(CCommTbl<std::string> vctSql, bool bRoll=true);		///ִ��sql���
	int CheckTable(const char* pTableName);		// �����Ƿ���� 1���� 0������
	CCommTbl<CCommTbl<std::string>> GetTable(const char *pSql);// ��ȡSQL���������
	std::string GetLastError() {return m_strError;}

private:
	const char* Sqlite3_errmsg() {return sqlite3_errmsg(m_pSqliteDB);}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBSQLITEFUN_H__DC7062D9_6FF6_4E17_BBD9_87ECF348542B__INCLUDED_)
