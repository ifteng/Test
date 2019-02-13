#ifndef __SHARE_MEMERY_H__
#define __SHARE_MEMERY_H__


// ʵ���̼߳以����
class ThreadMutex {
private:
	CRITICAL_SECTION m_cs;
public:
	ThreadMutex();
	virtual ~ThreadMutex();
	void Lock();
	void UnLock();
};

// ʵ�ֽ��̻����ࣨ�߳�����Ч��
class Mutex {
private:
	HANDLE m_h;
public:
//	Mutex();
	Mutex(char* szName=NULL);
	virtual ~Mutex();
	void Lock();
	void UnLock();
};


// �����ڴ���
class CShareMemery
{
public:
    CShareMemery();    
	CShareMemery(char* name, int size);
	~CShareMemery();
	
	BOOL CreateSHM(char* name, int size);
	void DestroySHM();
	char* GetShMEM();

private:
	HANDLE m_SHM;
	char* m_MEM;
};

#endif //__SHARE_MEMERY_H__