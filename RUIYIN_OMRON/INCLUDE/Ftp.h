#pragma once
/*
ʵ��FTP������ Ŀ¼���ѡ�/���ָ�
�ļ�����Ϊȫ·��
*/



class CFtp
{
public:
	CFtp(CString strServer, CString strUserName, CString strUserPwd, UINT uPort=21, BOOL bPassive=FALSE);
	~CFtp(void);

	void SetParam(CString strServer, CString strUserName, CString strUserPwd, UINT uPort=21, BOOL bPassive=FALSE);
	// �ϴ��ļ�(Զ��Ŀ¼�Զ�����)
	BOOL PutFile(CString strLocalFile, CString strRemoteFile);
	// �����ļ�(���ش����ļ�ɾ��)
	BOOL GetFile(CString strRemoteFile, CString strLocalFile);
	// ���(����)Ŀ¼
	BOOL CheckDir(CString strRemotePath, BOOL bCreate=TRUE);
	// ɾ���ļ�
	BOOL DeleteFile(CString strRemoteFile);

public:
	CString m_strServer;//IP
	UINT m_uPort;//�˿�
	BOOL m_bPassive;//����ģʽ
	CString m_strUserName;//�û���
	CString m_strUserPwd;//����

};
