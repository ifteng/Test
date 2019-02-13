#ifndef __ATMC_DEV_TRADE_STRUCT_H__
#define __ATMC_DEV_TRADE_STRUCT_H__

#pragma pack(push,1)

#include "BasePack.h"

#define _in_
#define _out_

enum ATM_TYPE
{
	ATMC_DEV	= 0x0001,
	ATMC_UI	= 0x0002,
	ATMC_TRADE	= 0x0003,
	ATMC_PRO	= 0x0004,

	ATMP_TRADE	= 0x0101,
	ATMP_SETT	= 0x0102,
	ATMP_PRO	= 0x0103,

	AM_QM		= 0x0201,
	AM_FM		= 0x0202
};

enum TRADE_ATMP_CODE{
	//////////////////////////////////////////////////////////////////////////
	//���ؽ���
	/// ��֤
	TRADE_CODE_VERIFY_SIGN		= 0x01000001,   /// ǩ������ȡ������Ϣ��
	TRADE_CODE_VERIFY_LOGIN		= 0x01000002,   /// ����Ա��½��BOSS���������

	/// ����
	TRADE_CODE_DATA_USER		= 0x02000001,   /// �ϴ��û���Ϣ

	/// �ɷѡ���ֵ��������������ӿ�
	TRADE_CODE_DEPOSIT			= 0x03000001,   /// ���
	TRADE_CODE_PAY_COST			= 0x03010001,   /// �ɷ�
	TRADE_CODE_CANCLE			= 0x03020001,   /// ����
	TRADE_CODE_CLEAR_CASH		= 0x03030001,   /// �ֽ����
	TRADE_CODE_CLEAR_CARD		= 0x03030002,   /// ��Ƭ���
	TRADE_CODE_ADD_CARD			= 0x03040001,   /// �ӿ�

	/// ǩԼ
	TRADE_CODE_SIGN_FILING		= 0x04000001,   /// ����
	TRADE_CODE_SIGN_SELFREG		= 0x04010001,   /// �����Һ�
	TRADE_CODE_SIGN_PREREG		= 0x04010002,   /// ԤԼ�Һ�
	TRADE_CODE_SIGN_UNPRE		= 0x04010003,   /// ȡ��ԤԼ�Һ�
	TRADE_CODE_SIGN_PRETAKE		= 0x04010004,   /// ԤԼȡ��

	/// ���
	TRADE_CODE_DEV_HEART		= 0x05000001,   /// ������Online & DeviceStatus & DeviceControl����[0]�޿���[1]�ػ�[2]����[3]���׽�������[4]������ͣ[5]���׻ָ�[6]��̨���£�

	//////////////////////////////////////////////////////////////////////////
	//��������
	/// ǩ��
	TRADE_CODE_BANK_SIGNIN		= 0x09000001,   /// ������ǩ��

	/// ��ѯ
	TRADE_CODE_BANK_BALANCE		= 0x09010001,   /// ������ѯ���

	/// �ɷ�
	TRADE_CODE_BANK_PAY_COST	= 0x09020001,	/// �����ɷ�

};

enum TRADE_ATMC_CODE{
	TRADE_CODE_SWITCH_INTERFACE = 999,	/// �л��ӿ�

	TRADE_CODE_PTR_INIT			= 1000,	/// ����
	TRADE_CODE_PTR_STATUS		= 1001,	/// ��ȡ�豸״̬
	TRADE_CODE_PTR_RESET		= 1002,	/// ���۴�ӡ��--����
	TRADE_CODE_PTR_CTL			= 1003,	/// ���۴�ӡ��--����
	TRADE_CODE_PTR_READ			= 1004,	/// ���۴�ӡ��--����
	TRADE_CODE_PTR_PRINT		= 1005,	/// ���۴�ӡ��--��ӡ
	TRADE_CODE_PTR_CANCLE		= 1006,	/// ��;�˳�

	TRADE_CODE_PIN_INIT			= 1100,	/// ����
	TRADE_CODE_PIN_STATUS		= 1101,	/// ��ȡ״̬
	TRADE_CODE_PIN_GETDATA		= 1102,	/// �������
	TRADE_CODE_PIN_STOPDATA		= 1103,	/// ֹͣ����
	TRADE_CODE_PIN_IMPORT_KEY	= 1104,	/// ������Կ
	TRADE_CODE_PIN_CRPTY		= 1105,	/// ��Կ����
	TRADE_CODE_PIN_GETPIN		= 1106,	/// ��ȡpin��
	TRADE_CODE_PIN_GETPINB		= 1107,	/// ��ȡpinblock
	TRADE_CODE_PIN_CANCLE		= 1108,	/// ��;�˳�

	TRADE_CODE_IDC_INIT			= 1200,	/// ����
	TRADE_CODE_IDC_STATUS		= 1201,	/// ��ȡ״̬
	TRADE_CODE_IDC_RESET		= 1202,	/// ����
	TRADE_CODE_IDC_RAWDATA		= 1203,	/// ����
	TRADE_CODE_IDC_TRACKDATA	= 1204,	/// ��������
	TRADE_CODE_IDC_EJECT		= 1205,	/// ����
	TRADE_CODE_IDC_RETAIN		= 1206,	/// �̿�
	TRADE_CODE_IDC_CANCLE		= 1207,	/// ��;�˳�

	TRADE_CODE_SLIP_PTR_INIT	= 1300,	/// ����
	TRADE_CODE_SLIP_PTR_STATUS	= 1301,	/// ��ȡ�豸״̬
	TRADE_CODE_SLIP_PTR_RESET	= 1302,	/// ƾ����ӡ��--����
	TRADE_CODE_SLIP_PTR_CTL		= 1303,	/// ƾ����ӡ��--����
	TRADE_CODE_SLIP_PTR_PRINT	= 1304,	/// ƾ����ӡ��--��ӡ
	TRADE_CODE_SLIP_PTR_CANCLE	= 1305,	/// ��;�˳�

	TRADE_CODE_IDCR_INIT		= 1400,	/// ����
	TRADE_CODE_IDCR_STATUS		= 1401,	/// ��ȡ�豸״̬
	TRADE_CODE_IDCR_READMSG		= 1402,	/// ���֤�Ķ���--��ȡ��Ϣ
	TRADE_CODE_IDCR_CANCLE		= 1403,	/// ��;�˳�
	TRADE_CODE_IDCR_ASYNREAD	= 1404,	/// �첽��ȡ���֤��Ϣ

	TRADE_CODE_RTCR_INIT		= 1500,	/// ����
	TRADE_CODE_RTCR_STATUS		= 1501,	/// ��ȡ�豸״̬
	TRADE_CODE_RTCR_SLOTSTATUS	= 1502,	/// ����״̬
	TRADE_CODE_RTCR_ENTRY		= 1503,	/// ����
	TRADE_CODE_RTCR_STOP		= 1504,	/// ��ֹ����
	TRADE_CODE_RTCR_READ		= 1505,	/// ������IC&��������
	TRADE_CODE_RTCR_EJECT		= 1506,	/// ����
	TRADE_CODE_RTCR_RETAIN		= 1507,	/// �̿�
	TRADE_CODE_RTCR_CANCLE		= 1508,	/// ��;�˳�
	TRADE_CODE_RTCR_INSERTCARD	= 1509,	/// ��ȡ���Ƿ����

	//������
	TRADE_CODE_EJCR_INIT		= 1600,	/// ����
	TRADE_CODE_EJCR_STATUS		= 1601,	/// ��ȡ�豸״̬
	TRADE_CODE_EJCR_BOXSTATUS	= 1602,	/// ��ȡ����״̬
	TRADE_CODE_EJCR_CTRLLED		= 1603,	/// ����LED��������
	TRADE_CODE_EJCR_RESET		= 1604,	/// ���÷�����
	TRADE_CODE_EJCR_READ		= 1605,	/// �������Ӻ�˽�������ȡ�ŵ�
	TRADE_CODE_EJCR_EJECT		= 1606,	/// ����
	TRADE_CODE_EJCR_RETAIN		= 1607,	/// �̿�
	TRADE_CODE_EJCR_CANCLE		= 1608,	/// ��;�˳�


	//cash code ֽ����
	TRADE_CODE_CASH_INIT		= 1700,	/// ����
	TRADE_CODE_CASH_STATUS		= 1701,	/// ��ȡ�豸״̬
	TRADE_CODE_CASH_BEGIN		= 1702,	/// ��ʼ��ֽ��
	TRADE_CODE_CASH_GET			= 1703,	/// ��ȡֽ�ҽ��ܺͣ�
	TRADE_CODE_CASH_CANCLE		= 1704,	/// �˳�

	//������ӡ��
	TRADE_CODE_SPPT_INIT		= 1800,	/// ����
	TRADE_CODE_SPPT_STATUS		= 1801,	/// ��ȡ�豸״̬
	TRADE_CODE_SPPT_RESET		= 1802,	/// ����
	TRADE_CODE_SPPT_PRINT		= 1803,	/// ��ӡ
	TRADE_CODE_SPPT_PRINTWOSA	= 1804,	/// WOSA��ӡ
	TRADE_CODE_SPPT_CUT			= 1805,	/// ��ֽ

	//�������2����wosa������
	TRADE_CODE_PWKB_INIT		= 1900,	/// ��ʼ��
	TRADE_CODE_PWKB_SETWORK		= 1901,	/// ���ع�����Կ
	TRADE_CODE_PWKB_STATUS		= 1902,	/// ��ȡ�������״̬
	TRADE_CODE_PWKB_MASTERK		= 1903,	/// ��������Կ
	TRADE_CODE_PWKB_TBOARD		= 1904,	/// �������ģʽ
	TRADE_CODE_PWKB_GETPIN		= 1905,	/// ��ȡpin data��pin�������ģ�
	TRADE_CODE_PWKB_GETMAC		= 1906,	/// ��ȡmacֵ
	TRADE_CODE_PWKB_CANCLE		= 1907,	/// �ж�

	//BRLD LED����
	TRADE_CODE_BRLD_INIT		= 2000,	/// ����
	TRADE_CODE_BRLD_STATUS		= 2001,	/// ��ȡ״̬
	TRADE_CODE_BRLD_RESET		= 2002,	/// ����
	TRADE_CODE_BRLD_SHOW		= 2003,	/// ��ʾ

	//�籣��
	TRADE_CODE_SSCR_INIT		= 2100,	/// ����
	TRADE_CODE_SSCR_STATUS		= 2101,	/// ��ȡ�豸״̬
	TRADE_CODE_SSCR_READMSG		= 2102,	/// �籣��--��ȡ��Ϣ
	TRADE_CODE_SSCR_CANCLE		= 2103,	/// ��;�˳�

	//UPS
	TRADE_CODE_UIPS_INIT		= 2200,	/// ����
	TRADE_CODE_UIPS_STATUS		= 2201,	/// ��ȡUPS״̬
	TRADE_CODE_UIPS_OFFON		= 2202,	/// �ȹػ��󿪻�
	TRADE_CODE_UIPS_SHUT		= 2203,	/// �ػ�
	TRADE_CODE_UIPS_CANCEL		= 2204,	/// ȡ���ػ�

	//���۴�ӡ��
	TRADE_CODE_PBPT_INIT		= 2300,	/// ��ʼ�����۴�ӡ��
	TRADE_CODE_PBPT_STATUS		= 2301,	/// ��ȡ���۴�ӡ��״̬
	TRADE_CODE_PBPT_SLOTSTATUS	= 2302,	/// ��ȡ���۲�״̬
	TRADE_CODE_PBPT_INSERTBOOK	= 2303,	/// ��ȡ���۲���״̬
	TRADE_CODE_PBPT_RESET		= 2304,	/// ����
	TRADE_CODE_PBPT_READ		= 2305,	/// ��ȡ����
	TRADE_CODE_PBPT_PRINTWOSA	= 2306,	/// ��ӡ����
	TRADE_CODE_PBPT_PRINTFORM	= 2307,	/// �������ӡ
	TRADE_CODE_PBPT_EJECT		= 2308,	/// �˳�����
	TRADE_CODE_PBPT_CANCEL		= 2309,	/// ȡ����ȡ����

	//������������
	TRADE_CODE_MSCR_INIT		= 2400,	/// ��ʼ��������������
	TRADE_CODE_MSCR_STATUS		= 2401,	/// ��ȡ������������״̬
	TRADE_CODE_MSCR_READ		= 2402,	/// ��ȡ������
	TRADE_CODE_MSCR_CANCEL		= 2403,	/// ȡ����ȡ������
	TRADE_CODE_MSCR_ASYNREAD	= 2404,	/// �첽��ȡ������

	//IC��������
	TRADE_CODE_ICCR_INIT		= 2500,	/// ��ʼ��IC������
	TRADE_CODE_ICCR_STATUS		= 2501,	/// ��ȡIC������״̬
	TRADE_CODE_ICCR_READ		= 2502,	/// ��ȡIC
	TRADE_CODE_ICCR_ICORTRACK	= 2503,	/// ��Ը��϶�������ȡIC�����ߴŵ���Ϣ
	TRADE_CODE_ICCR_CANCEL		= 2504,	/// ȡ����ȡIC��
	TRADE_CODE_ICCR_ASYNREAD	= 2505,	/// �첽��ȡIC��

	//���»�
	TRADE_CODE_STPM_INIT		= 2600,	/// ��ʼ�����»�
	TRADE_CODE_STPM_STATUS		= 2601,	/// ��ȡ���»�״̬
	TRADE_CODE_STPM_RESET		= 2602,	/// ����
	TRADE_CODE_STPM_START		= 2603,	/// �������»�
	TRADE_CODE_STPM_STOP		= 2604,	/// ֹͣ���»�
	TRADE_CODE_STPM_COUNT		= 2605,	/// ��ȡ���´���

	//ָ����
	TRADE_CODE_FGPT_INIT		= 2700,	/// ��ʼ��ָ����
	TRADE_CODE_FGPT_STATUS		= 2701,	/// ��ȡָ����״̬
	TRADE_CODE_FGPT_RESET		= 2702,	/// ����
	TRADE_CODE_FGPT_COLLECT		= 2703,	/// �ɼ�ָ����Ϣ
	TRADE_CODE_FGPT_TEMPLATE	= 2704,	/// ��ȡָ��ģ��
	TRADE_CODE_FGPT_CHARACTER	= 2705,	/// ��ȡָ������
	TRADE_CODE_FGPT_COMPARE		= 2706,	/// �Ա�ָ��
	TRADE_CODE_FGPT_CANCEL		= 2707,	/// ȡ��ָ�ƶ�ȡ

	//A4��ӡ��
	TRADE_CODE_A4PT_INIT		= 2800,	/// ��ʼ��A4��ӡ��
	TRADE_CODE_A4PT_STATUS		= 2801,	/// ��ȡA4��ӡ��״̬
	TRADE_CODE_A4PT_RESET		= 2802,	/// ����
	TRADE_CODE_A4PT_PRINTFILE	= 2803,	/// ��ӡ���ļ���DOC&XLS��

	//��־��ӡ��
	TRADE_CODE_JRPT_INIT		= 2900,	/// ����
	TRADE_CODE_JRPT_STATUS		= 2901,	/// ��ȡ�豸״̬
	TRADE_CODE_JRPT_RESET		= 2902,	/// ����
	TRADE_CODE_JRPT_PRINT		= 2903,	/// ��ӡ
	TRADE_CODE_JRPT_PRINTWOSA	= 2904,	/// WOSA��ӡ
	TRADE_CODE_JRPT_CUT			= 2905,	/// ��ֽ

	//����ʶ��
	TRADE_CODE_FCRN_INIT		= 3000,	/// ��ʼ��
	TRADE_CODE_FCRN_COMP		= 3001,	/// �Ƚ�����

};

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/// ���������
typedef struct BASE_QUERY_MSG
{
	BASE_MSG	m_head;	/// ������
	BYTE	m_szMAC[8];	/// ����У��
	char	m_szTerminalID[64];	/// �ն�Ψһ���
	UINT	m_uDevType;	/// �豸���ͣ�ATM_TYPE
	BASE_QUERY_MSG();
	void operator << (BASE_MSG head);
	void operator << (UINT type);
}*LPBASE_QUERY_MSG;

//////////////////////////////////////////////////////////////////////////
/// �������ذ�
typedef struct BASE_RETURN_MSG
{
	BASE_MSG	m_head;	/// ������
	BYTE	m_szMAC[8];	/// ����У��
	char	m_szTerminalID[64];	/// �ն�Ψһ���
	char	szErrCode[4+1];	/// ���ش����룺ERR_CODE
	BASE_RETURN_MSG();
	void operator << (BASE_MSG head);
	void operator << (UINT type);
}*LPBASE_RETURN_MSG;

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/// �豸���������
typedef struct DEV_CONTROL_QUERY_MSG
{
	BASE_QUERY_MSG	m_head;
	UINT	m_uLen;
	LPBYTE	m_pData;
	DEV_CONTROL_QUERY_MSG();
	~DEV_CONTROL_QUERY_MSG();
	void GetData(LPBYTE* _out_ pData,UINT & _out_ uLen);
}*LPDEV_CONTROL_QUERY_MSG;
 
//////////////////////////////////////////////////////////////////////////
/// �豸�������ذ�
typedef struct DEV_CONTROL_RETURN_MSG
{
	BASE_RETURN_MSG	m_head;
	UINT	m_uLen;
	LPBYTE	m_pData;
	DEV_CONTROL_RETURN_MSG();
	~DEV_CONTROL_RETURN_MSG();
	void GetData(LPBYTE* _out_ pData,UINT & _out_ uLen);
}*LPDEV_CONTROL_RETURN_MSG;




#define	LEN_BASE_QUERY_TERMINAL_SERIAL	33	//�ն���ˮ

// ҵ����������
typedef struct
{
	BASE_QUERY_MSG	m_head;
	char	m_szSerial[LEN_BASE_QUERY_TERMINAL_SERIAL];
	unsigned int	m_uLen;
	void*	m_pData;
}*LPQUERY_TRADE_MSG,QUERY_TRADE_MSG;


// ҵ��������ذ�
typedef struct 
{
	BASE_RETURN_MSG	m_head;
	unsigned int	m_uLen;
	void*	m_pData;
}*LPRETURN_TRADE_MSG,RETURN_TRADE_MSG;






#pragma pack(pop)

#endif