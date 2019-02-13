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
	//本地交易
	/// 验证
	TRADE_CODE_VERIFY_SIGN		= 0x01000001,   /// 签到（获取配置信息）
	TRADE_CODE_VERIFY_LOGIN		= 0x01000002,   /// 管理员登陆（BOSS）（清机）

	/// 数据
	TRADE_CODE_DATA_USER		= 0x02000001,   /// 上传用户信息

	/// 缴费、充值、冲正、清机、加卡
	TRADE_CODE_DEPOSIT			= 0x03000001,   /// 存款
	TRADE_CODE_PAY_COST			= 0x03010001,   /// 缴费
	TRADE_CODE_CANCLE			= 0x03020001,   /// 冲正
	TRADE_CODE_CLEAR_CASH		= 0x03030001,   /// 现金清机
	TRADE_CODE_CLEAR_CARD		= 0x03030002,   /// 卡片清机
	TRADE_CODE_ADD_CARD			= 0x03040001,   /// 加卡

	/// 签约
	TRADE_CODE_SIGN_FILING		= 0x04000001,   /// 发卡
	TRADE_CODE_SIGN_SELFREG		= 0x04010001,   /// 自助挂号
	TRADE_CODE_SIGN_PREREG		= 0x04010002,   /// 预约挂号
	TRADE_CODE_SIGN_UNPRE		= 0x04010003,   /// 取消预约挂号
	TRADE_CODE_SIGN_PRETAKE		= 0x04010004,   /// 预约取号

	/// 监控
	TRADE_CODE_DEV_HEART		= 0x05000001,   /// 心跳（Online & DeviceStatus & DeviceControl）（[0]无控制[1]关机[2]重启[3]交易进程重启[4]交易暂停[5]交易恢复[6]后台更新）

	//////////////////////////////////////////////////////////////////////////
	//银联交易
	/// 签到
	TRADE_CODE_BANK_SIGNIN		= 0x09000001,   /// 银联端签到

	/// 查询
	TRADE_CODE_BANK_BALANCE		= 0x09010001,   /// 银联查询余额

	/// 缴费
	TRADE_CODE_BANK_PAY_COST	= 0x09020001,	/// 银联缴费

};

enum TRADE_ATMC_CODE{
	TRADE_CODE_SWITCH_INTERFACE = 999,	/// 切换接口

	TRADE_CODE_PTR_INIT			= 1000,	/// 加载
	TRADE_CODE_PTR_STATUS		= 1001,	/// 获取设备状态
	TRADE_CODE_PTR_RESET		= 1002,	/// 存折打印机--重置
	TRADE_CODE_PTR_CTL			= 1003,	/// 存折打印机--控制
	TRADE_CODE_PTR_READ			= 1004,	/// 存折打印机--读折
	TRADE_CODE_PTR_PRINT		= 1005,	/// 存折打印机--打印
	TRADE_CODE_PTR_CANCLE		= 1006,	/// 中途退出

	TRADE_CODE_PIN_INIT			= 1100,	/// 加载
	TRADE_CODE_PIN_STATUS		= 1101,	/// 获取状态
	TRADE_CODE_PIN_GETDATA		= 1102,	/// 明码键盘
	TRADE_CODE_PIN_STOPDATA		= 1103,	/// 停止明码
	TRADE_CODE_PIN_IMPORT_KEY	= 1104,	/// 加载秘钥
	TRADE_CODE_PIN_CRPTY		= 1105,	/// 秘钥运算
	TRADE_CODE_PIN_GETPIN		= 1106,	/// 获取pin码
	TRADE_CODE_PIN_GETPINB		= 1107,	/// 获取pinblock
	TRADE_CODE_PIN_CANCLE		= 1108,	/// 中途退出

	TRADE_CODE_IDC_INIT			= 1200,	/// 加载
	TRADE_CODE_IDC_STATUS		= 1201,	/// 获取状态
	TRADE_CODE_IDC_RESET		= 1202,	/// 重置
	TRADE_CODE_IDC_RAWDATA		= 1203,	/// 发卡
	TRADE_CODE_IDC_TRACKDATA	= 1204,	/// 读卡磁条
	TRADE_CODE_IDC_EJECT		= 1205,	/// 弹卡
	TRADE_CODE_IDC_RETAIN		= 1206,	/// 吞卡
	TRADE_CODE_IDC_CANCLE		= 1207,	/// 中途退出

	TRADE_CODE_SLIP_PTR_INIT	= 1300,	/// 加载
	TRADE_CODE_SLIP_PTR_STATUS	= 1301,	/// 获取设备状态
	TRADE_CODE_SLIP_PTR_RESET	= 1302,	/// 凭条打印机--重置
	TRADE_CODE_SLIP_PTR_CTL		= 1303,	/// 凭条打印机--控制
	TRADE_CODE_SLIP_PTR_PRINT	= 1304,	/// 凭条打印机--打印
	TRADE_CODE_SLIP_PTR_CANCLE	= 1305,	/// 中途退出

	TRADE_CODE_IDCR_INIT		= 1400,	/// 加载
	TRADE_CODE_IDCR_STATUS		= 1401,	/// 获取设备状态
	TRADE_CODE_IDCR_READMSG		= 1402,	/// 身份证阅读器--读取信息
	TRADE_CODE_IDCR_CANCLE		= 1403,	/// 中途退出
	TRADE_CODE_IDCR_ASYNREAD	= 1404,	/// 异步读取身份证信息

	TRADE_CODE_RTCR_INIT		= 1500,	/// 加载
	TRADE_CODE_RTCR_STATUS		= 1501,	/// 获取设备状态
	TRADE_CODE_RTCR_SLOTSTATUS	= 1502,	/// 卡槽状态
	TRADE_CODE_RTCR_ENTRY		= 1503,	/// 进卡
	TRADE_CODE_RTCR_STOP		= 1504,	/// 禁止进卡
	TRADE_CODE_RTCR_READ		= 1505,	/// 读卡（IC&磁条卡）
	TRADE_CODE_RTCR_EJECT		= 1506,	/// 弹卡
	TRADE_CODE_RTCR_RETAIN		= 1507,	/// 吞卡
	TRADE_CODE_RTCR_CANCLE		= 1508,	/// 中途退出
	TRADE_CODE_RTCR_INSERTCARD	= 1509,	/// 获取卡是否插入

	//发卡器
	TRADE_CODE_EJCR_INIT		= 1600,	/// 加载
	TRADE_CODE_EJCR_STATUS		= 1601,	/// 获取设备状态
	TRADE_CODE_EJCR_BOXSTATUS	= 1602,	/// 获取卡箱状态
	TRADE_CODE_EJCR_CTRLLED		= 1603,	/// 发送LED控制命令
	TRADE_CODE_EJCR_RESET		= 1604,	/// 重置发卡器
	TRADE_CODE_EJCR_READ		= 1605,	/// 发卡器从后端进卡并读取磁道
	TRADE_CODE_EJCR_EJECT		= 1606,	/// 弹卡
	TRADE_CODE_EJCR_RETAIN		= 1607,	/// 吞卡
	TRADE_CODE_EJCR_CANCLE		= 1608,	/// 中途退出


	//cash code 纸币器
	TRADE_CODE_CASH_INIT		= 1700,	/// 加载
	TRADE_CODE_CASH_STATUS		= 1701,	/// 获取设备状态
	TRADE_CODE_CASH_BEGIN		= 1702,	/// 开始进纸币
	TRADE_CODE_CASH_GET			= 1703,	/// 获取纸币金额（总和）
	TRADE_CODE_CASH_CANCLE		= 1704,	/// 退出

	//热敏打印机
	TRADE_CODE_SPPT_INIT		= 1800,	/// 加载
	TRADE_CODE_SPPT_STATUS		= 1801,	/// 获取设备状态
	TRADE_CODE_SPPT_RESET		= 1802,	/// 重置
	TRADE_CODE_SPPT_PRINT		= 1803,	/// 打印
	TRADE_CODE_SPPT_PRINTWOSA	= 1804,	/// WOSA打印
	TRADE_CODE_SPPT_CUT			= 1805,	/// 切纸

	//密码键盘2（非wosa驱动）
	TRADE_CODE_PWKB_INIT		= 1900,	/// 初始化
	TRADE_CODE_PWKB_SETWORK		= 1901,	/// 下载工作密钥
	TRADE_CODE_PWKB_STATUS		= 1902,	/// 获取密码键盘状态
	TRADE_CODE_PWKB_MASTERK		= 1903,	/// 设置主密钥
	TRADE_CODE_PWKB_TBOARD		= 1904,	/// 明码键盘模式
	TRADE_CODE_PWKB_GETPIN		= 1905,	/// 获取pin data（pin加密密文）
	TRADE_CODE_PWKB_GETMAC		= 1906,	/// 获取mac值
	TRADE_CODE_PWKB_CANCLE		= 1907,	/// 中断

	//BRLD LED条灯
	TRADE_CODE_BRLD_INIT		= 2000,	/// 加载
	TRADE_CODE_BRLD_STATUS		= 2001,	/// 获取状态
	TRADE_CODE_BRLD_RESET		= 2002,	/// 重置
	TRADE_CODE_BRLD_SHOW		= 2003,	/// 显示

	//社保卡
	TRADE_CODE_SSCR_INIT		= 2100,	/// 加载
	TRADE_CODE_SSCR_STATUS		= 2101,	/// 获取设备状态
	TRADE_CODE_SSCR_READMSG		= 2102,	/// 社保卡--读取信息
	TRADE_CODE_SSCR_CANCLE		= 2103,	/// 中途退出

	//UPS
	TRADE_CODE_UIPS_INIT		= 2200,	/// 加载
	TRADE_CODE_UIPS_STATUS		= 2201,	/// 获取UPS状态
	TRADE_CODE_UIPS_OFFON		= 2202,	/// 先关机后开机
	TRADE_CODE_UIPS_SHUT		= 2203,	/// 关机
	TRADE_CODE_UIPS_CANCEL		= 2204,	/// 取消关机

	//存折打印机
	TRADE_CODE_PBPT_INIT		= 2300,	/// 初始化存折打印机
	TRADE_CODE_PBPT_STATUS		= 2301,	/// 获取存折打印机状态
	TRADE_CODE_PBPT_SLOTSTATUS	= 2302,	/// 获取存折槽状态
	TRADE_CODE_PBPT_INSERTBOOK	= 2303,	/// 获取存折插入状态
	TRADE_CODE_PBPT_RESET		= 2304,	/// 重置
	TRADE_CODE_PBPT_READ		= 2305,	/// 读取存折
	TRADE_CODE_PBPT_PRINTWOSA	= 2306,	/// 打印存折
	TRADE_CODE_PBPT_PRINTFORM	= 2307,	/// 按坐标打印
	TRADE_CODE_PBPT_EJECT		= 2308,	/// 退出存折
	TRADE_CODE_PBPT_CANCEL		= 2309,	/// 取消读取存折

	//磁条卡读卡器
	TRADE_CODE_MSCR_INIT		= 2400,	/// 初始化磁条卡读卡器
	TRADE_CODE_MSCR_STATUS		= 2401,	/// 获取磁条卡读卡器状态
	TRADE_CODE_MSCR_READ		= 2402,	/// 读取磁条卡
	TRADE_CODE_MSCR_CANCEL		= 2403,	/// 取消读取磁条卡
	TRADE_CODE_MSCR_ASYNREAD	= 2404,	/// 异步读取磁条卡

	//IC卡读卡器
	TRADE_CODE_ICCR_INIT		= 2500,	/// 初始化IC读卡器
	TRADE_CODE_ICCR_STATUS		= 2501,	/// 获取IC读卡器状态
	TRADE_CODE_ICCR_READ		= 2502,	/// 读取IC
	TRADE_CODE_ICCR_ICORTRACK	= 2503,	/// 针对复合读卡器读取IC卡或者磁道信息
	TRADE_CODE_ICCR_CANCEL		= 2504,	/// 取消读取IC卡
	TRADE_CODE_ICCR_ASYNREAD	= 2505,	/// 异步读取IC卡

	//盖章机
	TRADE_CODE_STPM_INIT		= 2600,	/// 初始化盖章机
	TRADE_CODE_STPM_STATUS		= 2601,	/// 获取盖章机状态
	TRADE_CODE_STPM_RESET		= 2602,	/// 重置
	TRADE_CODE_STPM_START		= 2603,	/// 启动盖章机
	TRADE_CODE_STPM_STOP		= 2604,	/// 停止盖章机
	TRADE_CODE_STPM_COUNT		= 2605,	/// 获取盖章次数

	//指纹仪
	TRADE_CODE_FGPT_INIT		= 2700,	/// 初始化指纹仪
	TRADE_CODE_FGPT_STATUS		= 2701,	/// 获取指纹仪状态
	TRADE_CODE_FGPT_RESET		= 2702,	/// 重置
	TRADE_CODE_FGPT_COLLECT		= 2703,	/// 采集指纹信息
	TRADE_CODE_FGPT_TEMPLATE	= 2704,	/// 获取指纹模板
	TRADE_CODE_FGPT_CHARACTER	= 2705,	/// 获取指纹特征
	TRADE_CODE_FGPT_COMPARE		= 2706,	/// 对比指纹
	TRADE_CODE_FGPT_CANCEL		= 2707,	/// 取消指纹读取

	//A4打印机
	TRADE_CODE_A4PT_INIT		= 2800,	/// 初始化A4打印机
	TRADE_CODE_A4PT_STATUS		= 2801,	/// 获取A4打印机状态
	TRADE_CODE_A4PT_RESET		= 2802,	/// 重置
	TRADE_CODE_A4PT_PRINTFILE	= 2803,	/// 打印机文件（DOC&XLS）

	//日志打印机
	TRADE_CODE_JRPT_INIT		= 2900,	/// 加载
	TRADE_CODE_JRPT_STATUS		= 2901,	/// 获取设备状态
	TRADE_CODE_JRPT_RESET		= 2902,	/// 重置
	TRADE_CODE_JRPT_PRINT		= 2903,	/// 打印
	TRADE_CODE_JRPT_PRINTWOSA	= 2904,	/// WOSA打印
	TRADE_CODE_JRPT_CUT			= 2905,	/// 切纸

	//人脸识别
	TRADE_CODE_FCRN_INIT		= 3000,	/// 初始化
	TRADE_CODE_FCRN_COMP		= 3001,	/// 比较人脸

};

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/// 基本请求包
typedef struct BASE_QUERY_MSG
{
	BASE_MSG	m_head;	/// 基本包
	BYTE	m_szMAC[8];	/// 报文校验
	char	m_szTerminalID[64];	/// 终端唯一编号
	UINT	m_uDevType;	/// 设备类型：ATM_TYPE
	BASE_QUERY_MSG();
	void operator << (BASE_MSG head);
	void operator << (UINT type);
}*LPBASE_QUERY_MSG;

//////////////////////////////////////////////////////////////////////////
/// 基本返回包
typedef struct BASE_RETURN_MSG
{
	BASE_MSG	m_head;	/// 基本包
	BYTE	m_szMAC[8];	/// 报文校验
	char	m_szTerminalID[64];	/// 终端唯一编号
	char	szErrCode[4+1];	/// 返回错误码：ERR_CODE
	BASE_RETURN_MSG();
	void operator << (BASE_MSG head);
	void operator << (UINT type);
}*LPBASE_RETURN_MSG;

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
/// 设备操作请求包
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
/// 设备操作返回包
typedef struct DEV_CONTROL_RETURN_MSG
{
	BASE_RETURN_MSG	m_head;
	UINT	m_uLen;
	LPBYTE	m_pData;
	DEV_CONTROL_RETURN_MSG();
	~DEV_CONTROL_RETURN_MSG();
	void GetData(LPBYTE* _out_ pData,UINT & _out_ uLen);
}*LPDEV_CONTROL_RETURN_MSG;




#define	LEN_BASE_QUERY_TERMINAL_SERIAL	33	//终端流水

// 业务操作请求包
typedef struct
{
	BASE_QUERY_MSG	m_head;
	char	m_szSerial[LEN_BASE_QUERY_TERMINAL_SERIAL];
	unsigned int	m_uLen;
	void*	m_pData;
}*LPQUERY_TRADE_MSG,QUERY_TRADE_MSG;


// 业务操作返回包
typedef struct 
{
	BASE_RETURN_MSG	m_head;
	unsigned int	m_uLen;
	void*	m_pData;
}*LPRETURN_TRADE_MSG,RETURN_TRADE_MSG;






#pragma pack(pop)

#endif