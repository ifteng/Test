// DataOper.h: interface for the CFileOper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPER_H__D5DD0C26_84B0_40C0_9D6E_26824174429B__INCLUDED_)
#define AFX_FILEOPER_H__D5DD0C26_84B0_40C0_9D6E_26824174429B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <string>
#include <vector>
#include "sharememory.h"
//#include "CommonFun.h"
//#include "CommTbl.h"

/* ����ʵ���ļ����ݲ����ӿ�
	����
	д��
	��ȡ
	ɾ����¼
-------------------------------------------------------------
�ļ�ͷ��ʽ:
����			����			����
����״̬		1				'1': ���� '2' ��������(���ɼ�¼) '3' ����������(���ɲ���)
�Ƿ����¼�¼	1				'0':�� '1': ��	������Ӻ͸���
�������ݳ���	6				�������ݳ���(ASCII)	
���ݸ���		12				���ݼ�¼����(ASCII)		
����			1				\n

������¼�ļ���ʽ:
����			����			����
����״̬		1				1: �������� 0:������ 2:�����Ѹ���
��������		sizeof(T)		
����			1				\n
-------------------------------------------------------------

*/

#define FILE_HEAD_LEN 21
#define MAX_FILE_SIZE 20*1024*1024
#define INSERT_DATA 1
#define DELETE_DATA	2
#define UPDATE_DATA 3

template<class T> class CFileOper// : public CCommTbl<T>
{
struct ONE_FILE_DATA 
{
	char cStatus;
	T    stuData;
	char cEnd;
};

public:
	CFileOper()
		:m_Mutex("FileOper")
	{
		m_sFileName="";
		fp = NULL;
	};

	virtual ~CFileOper(){};

private:
	std::string m_sFileName;
	Mutex m_Mutex;

private:
	int GetFileLength()
	{
		int len = -1;
		fseek(fp, 0, SEEK_END);
		len = ftell(fp);
		return len;
	};

	size_t Read(char* pData, int len)
	{
		return fread(pData, 1, len, fp);
	}
	size_t Write(char* pData, int len)
	{
		return fwrite(pData, 1, len, fp);
	}

	int GetItemNum()
	{
		int num = -1;
		char buf[20];
		fseek(fp, 8, SEEK_SET);
		memset(buf, 0x00, sizeof(buf));
		if(Read(buf,12)!=12)
			return -1;
		num = atoi(buf);
		return num;
	}

public:
    void SetDateFile(char* szFileName)
    {
        m_sFileName = szFileName;
    }
    
	bool ToolDataFile(char* szFileName)
	{
		bool bRet = false;
		char buf[20];
		fp = fopen(szFileName, "a+");
		if(!fp)
		{
			return false;
		}
		m_sFileName = szFileName;
		int len = GetFileLength();
		fclose(fp);
		fp = NULL;
		

		if(len < FILE_HEAD_LEN)
		{
			fp = fopen(m_sFileName.c_str(), "rb+");
			if(!fp)
				return false;
			
			fseek(fp, 0, SEEK_SET);
			if(Write("1", 1) != 1)
				goto END_WRITE_NEWHEAD_DATA;
			if(Write("0", 1) != 1)
				goto END_WRITE_NEWHEAD_DATA;
			memset(buf, 0x00, sizeof(buf));
			_itoa(sizeof(T), buf, 10);
			if(Write(buf, 6) != 6)
				goto END_WRITE_NEWHEAD_DATA;
			memset(buf, 0x00, sizeof(buf));
			buf[0]='0';
			if(Write(buf, 12) != 12)
				goto END_WRITE_NEWHEAD_DATA;
			if(Write("\n", 1) != 1)
				goto END_WRITE_NEWHEAD_DATA;

			bRet = true;
END_WRITE_NEWHEAD_DATA:
			fclose(fp);
			fp = NULL;
			return bRet;
		}
		return true;
	};

	bool UpdateHead(int iType, int num=1) // 1: ��� 2: ɾ��
	{
		bool bRet = false;
		int size;
        if(!num) return bRet;
		int len = GetFileLength();
		if(len < FILE_HEAD_LEN)
		{
			goto END_WRITE_HEAD_DATA;
		}
		char buf1[10], buf2[20];
		memset(buf1, 0x00, sizeof(buf1));
		memset(buf2, 0x00, sizeof(buf2));
		fseek(fp, 2, SEEK_SET);		
		if(Read(buf1, 6) != 6)
		{
			goto END_WRITE_HEAD_DATA;
		}
		if(Read(buf2, 12) != 12)
		{
			goto END_WRITE_HEAD_DATA;
		}
		size = atoi(buf1)*atoi(buf2);
		if(size > MAX_FILE_SIZE)
		{
			fseek(fp, 0, SEEK_SET);				
			if(Write("2", 1) != 1)
				goto END_WRITE_HEAD_DATA;
		}
		if(iType == INSERT_DATA)
		{
			fseek(fp, 1, SEEK_SET);	
			if(Write("1", 1) != 1)
				goto END_WRITE_HEAD_DATA;
		}
		size = atoi(buf2);
		if(iType == INSERT_DATA)
			size += num;
		else if(iType == DELETE_DATA)
			size -= num;
		memset(buf2, 0x00, sizeof(buf2));
		_itoa(size, buf2, 10);
		fseek(fp, 8, SEEK_SET);	
		if(Write(buf2, 12) != 12)
			goto END_WRITE_HEAD_DATA;
		return true;
END_WRITE_HEAD_DATA:
		return false;
	}
	
	bool WriteData(T* pData)
	{
		int len,nBlock;
//		long pos;
		size_t nCount, i;
		bool bRet = false;
		if(m_sFileName == "")
			return bRet;
		m_Mutex.Lock();
		fp = fopen(m_sFileName.c_str(), "rb+");
		if(!fp)
		{
			m_Mutex.UnLock();
			return bRet;
		}
		len = GetFileLength();
		if(len < FILE_HEAD_LEN)
		{
			bRet = false;
			goto END_WRITE_DATA;
		}
		fseek(fp, FILE_HEAD_LEN, SEEK_SET);
		
		nBlock = sizeof(T)+2;// ע�ⲻ��ʹ�� sizeof(ONE_FILE_DATA) != sizeof(T)+2
		nCount = (len-FILE_HEAD_LEN)/nBlock;
		for(i = 0; i < nCount; i++)
		{
			char cStatus;
			if(Read(&cStatus, 1) != 1)
			{
				bRet = false;
				goto END_WRITE_DATA;
			}
			fseek(fp, -1, SEEK_CUR);
			if(cStatus == '0') break;
			fseek(fp, nBlock, SEEK_CUR);
		}
		if(Write("0", 1) != 1)
		{
			bRet = false;
			goto END_WRITE_DATA;
		}		
		if(Write((char*)pData, sizeof(T)) != sizeof(T))
		{
			bRet = false;
			goto END_WRITE_DATA;
		}
		if( Write("\n", 1) != 1)
		{
			bRet = false;
			goto END_WRITE_DATA;
		}
//		fflush(fp);
		fseek(fp, -nBlock, SEEK_CUR);
		if(Write("1", 1) != 1)
		{
			bRet = false;
			goto END_WRITE_DATA;
		}
		bRet = UpdateHead(INSERT_DATA);

END_WRITE_DATA:
		fclose(fp);
		fp = NULL;
		m_Mutex.UnLock();
		return bRet;
	};

	int DeleteData(T* pMask, bool (*Compare)(T*,T*)=NULL)
	{
		int len,nBlock, num=-1;
		size_t nCount, i;
		ONE_FILE_DATA item;	

		if(m_sFileName == "") return -1;
		m_Mutex.Lock();
		fp = fopen(m_sFileName.c_str(), "rb+");
		if(!fp) {m_Mutex.UnLock(); return -1;}
		len = GetFileLength();
		if(len < 0)
        {
            fclose(fp);
			m_Mutex.UnLock();
            return -1;
        }

		fseek(fp, FILE_HEAD_LEN, SEEK_SET);
		
		nBlock = sizeof(T)+2;
		nCount = (len-FILE_HEAD_LEN)/nBlock;
		num = 0;
		for(i = 0; i < nCount; i++)
		{
			if(Read(&item.cStatus, 1) != 1)
			{
				break;
			}
			if(item.cStatus == '0') 
			{
				fseek(fp, nBlock-1, SEEK_CUR);
				continue;
			}
			if(Read((char*)&item.stuData, sizeof(T)) != sizeof(T))
			{
				break;
			}
			fseek(fp, 1, SEEK_CUR);
			if(Compare && (!Compare(pMask, &item.stuData))) continue;
			fseek(fp, -nBlock, SEEK_CUR);
			if(Write("0", 1) != 1)
			{
				break;
			}
			fseek(fp, nBlock-1, SEEK_CUR);
			num++;
		}
		UpdateHead(DELETE_DATA, num);

        fclose(fp);
        fp = NULL;
		m_Mutex.UnLock();
        return num;
	};

    int DeleteDataItem(int iPos)
    {
        int len, pos=0;
        size_t nBlock, nCount, i;
        ONE_FILE_DATA item;	
        
        if(m_sFileName == "") return -1;
		m_Mutex.Lock();
        fp = fopen(m_sFileName.c_str(), "rb+");
		if(!fp) {m_Mutex.UnLock(); return -1;}
        len = GetFileLength();
        if(len < 0)
        {
            fclose(fp);
			m_Mutex.UnLock();
            return -1;
        }
        
        fseek(fp, FILE_HEAD_LEN, SEEK_SET);
        
        nBlock = sizeof(T)+2;
        nCount = (len-FILE_HEAD_LEN)/nBlock;
        for(i = 0; i < nCount; i++)
        {
            if(Read(&item.cStatus, 1) != 1)
            {
                break;
            }
            if(item.cStatus == '0') 
            {
                fseek(fp, nBlock-1, SEEK_CUR);
                continue;
            }
            fseek(fp, sizeof(T)+1, SEEK_CUR);
            pos++;
            if(pos != iPos) continue;
            fseek(fp, -nBlock, SEEK_CUR);				
            if(Write("0", 1) != 1)
            {
                break;
            }
            fseek(fp, nBlock-1, SEEK_CUR);
            UpdateHead(DELETE_DATA, 1);
            fclose(fp);
			m_Mutex.UnLock();
            return 0;
        }
        
        fclose(fp);
        fp = NULL;
		m_Mutex.UnLock();
        return -1;
    };


	std::vector<T> ReadData(T* pMask, bool (*Compare)(T*,T*)=NULL)
	{
		std::vector<T> vct;
		int len, iRet = -1;;
		size_t nBlock, nCount, i;
		ONE_FILE_DATA item;		
		if(m_sFileName == "") return vct;
		fp = fopen(m_sFileName.c_str(), "rb+");
		if(!fp)
			return vct;
		len = GetFileLength();
		if(len < 0)
        {
            fclose(fp);
            return vct;
        }
/*		len = GetItemNum();
		if(len <= 0)
			goto END_READ_DATA;
*/            
		fseek(fp, FILE_HEAD_LEN, SEEK_SET);
		
		nBlock = sizeof(T)+2;
		nCount = (len-FILE_HEAD_LEN)/nBlock;
		iRet = 0;
		for(i = 0; i < nCount; i++)
		{
			if(Read(&item.cStatus, 1) != 1)
			{
				iRet = -1;
				break;
			}
			if(item.cStatus == '0') 
			{
				fseek(fp, nBlock-1, SEEK_CUR);
				continue;
			}
			if(Read((char*)&item.stuData, sizeof(T)) != sizeof(T))
			{
				iRet = -1;
				break;
			}
			fseek(fp, 1, SEEK_CUR);
			if(Compare && (!Compare(pMask, &item.stuData))) continue;
			vct.push_back(item.stuData);
		}
		fclose(fp);
		fp = NULL;		
		return vct;
	};

	int UpdateData(T* pMask, bool (*Update)(T*,T*)=NULL)
	{
		int len,num=0;
		size_t nBlock, nCount, i;
		ONE_FILE_DATA item;	
		if(m_sFileName == "") return -1;
		m_Mutex.Lock();
		fp = fopen(m_sFileName.c_str(), "rb+");
		if(!fp) {m_Mutex.UnLock(); return -1;}
		len = GetFileLength();
		if(len < 0)
        {
            fclose(fp);
			m_Mutex.UnLock();
            return -1;
        }
		
		fseek(fp, FILE_HEAD_LEN, SEEK_SET);
		nBlock = sizeof(T)+2;
		nCount = (len-FILE_HEAD_LEN)/nBlock;
		num = 0;
		for(i = 0; i < nCount; i++)
		{
			if(Read(&item.cStatus, 1) != 1)
			{
				break;
			}
			if(item.cStatus == '0') 
			{
				fseek(fp, nBlock-1, SEEK_CUR);
				continue;
			}
			if(Read((char*)&item.stuData, sizeof(T)) != sizeof(T))
			{
				break;
			}
			fseek(fp, 1, SEEK_CUR);
			if(Update && (!Update(pMask, &item.stuData))) continue;
			fseek(fp, -nBlock, SEEK_CUR);
            if(Write("2", 1) != 1)
            {
                break;
            }
            if(Write((char*)&item.stuData, sizeof(T)) != sizeof(T))
			{
				break;
			}
			fseek(fp, 1, SEEK_CUR);
			num++;
		}
		fclose(fp);
		fp = NULL;
		m_Mutex.UnLock();
		return num;
	};

    int UpdateData(int iPos, T* pData)
    {
        int len,pos=0;
        size_t nBlock, nCount, i;
        ONE_FILE_DATA item;	
        if(m_sFileName == "") return -1;
		m_Mutex.Lock();
        fp = fopen(m_sFileName.c_str(), "rb+");
		if(!fp) {m_Mutex.UnLock(); return -1;}
        len = GetFileLength();
        if(len < 0)
        {
            fclose(fp);
			m_Mutex.UnLock();
            return -1;
        }
        
        fseek(fp, FILE_HEAD_LEN, SEEK_SET);
        nBlock = sizeof(T)+2;
        nCount = (len-FILE_HEAD_LEN)/nBlock;
        for(i = 0; i < nCount; i++)
        {
            if(Read(&item.cStatus, 1) != 1)
            {
                break;
            }
            if(item.cStatus == '0') 
            {
                fseek(fp, nBlock-1, SEEK_CUR);
                continue;
            }
            if(Read((char*)&item.stuData, sizeof(T)) != sizeof(T))
            {
                break;
            }
            fseek(fp, 1, SEEK_CUR);
            pos++;
            if(iPos!=pos) continue;
            fseek(fp, -nBlock, SEEK_CUR);
            if(Write("2", 1) != 1)
            {
                break;
            }
            if(Write((char*)pData, sizeof(T)) != sizeof(T))
            {
                break;
            }
            fseek(fp, 1, SEEK_CUR);
            fclose(fp);
            return 0;
        }
        fclose(fp);
        fp = NULL;
		m_Mutex.UnLock();
        return -1;
    };

/*	
    int UpdateItemState(T* pMask, bool (*Update)(T*,T*)=NULL, char cStatus='0')
    {
        int len,num=0;
        size_t nBlock, nCount, i;
        ONE_FILE_DATA item;	
        if(m_sFileName == "") return num;
        if(!Update) return num;
        fp = fopen(m_sFileName.c_str(), "rb+");
        if(!fp) return num;
        len = GetFileLength();
        if(len < 0)
            goto END_UPDATE_DATA;
        
        fseek(fp, FILE_HEAD_LEN, SEEK_SET);
        
        nBlock = sizeof(T)+2;
        nCount = (len-FILE_HEAD_LEN)/nBlock;
        num = 0;
        for(i = 0; i < nCount; i++)
        {
            if(Read(&item.cStatus, 1) != 1)
            {
                break;
            }
            if(item.cStatus == '0') 
            {
                fseek(fp, nBlock-1, SEEK_CUR);
                continue;
            }
            if(Read((char*)&item.stuData, sizeof(T)) != sizeof(T))
            {
                break;
            }
            fseek(fp, 1, SEEK_CUR);
            if(!Update(pMask, &item.stuData)) continue;
            fseek(fp, -nBlock, SEEK_CUR);
            if(Write(cStatus, 1) != 1)
            {
                break;
            }
            fseek(fp, sizeof(T)+1, SEEK_CUR);
            num++;
        }
END_UPDATE_DATA:
        fclose(fp);
        fp = NULL;
        return num;
    };
*/
    
private:
	FILE* fp;
};

#endif // !defined(AFX_FILEOPER_H__D5DD0C26_84B0_40C0_9D6E_26824174429B__INCLUDED_)
