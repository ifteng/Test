
// Blood pressureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Blood pressure.h"
#include "Blood pressureDlg.h"
#include "afxdialogex.h"
#include "PB_API.h"
#include "RS232C.H"
#include "COMMFCN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HMODULE hDll_NTPRx;

typedef void (CALLBACK *GetCardNumBy)(char* pCardNum);
GetCardNumBy pFunCBGetCardNumBy;

void CALLBACK GetBloodPressInfo(char* pCardNum);

typedef int(*lpInitialize)(int, int);
typedef BOOL(*lpSetCallBack)(GetCardNumBy);

lpInitialize InitializeTEST;
lpSetCallBack SetCallBack;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBloodpressureDlg �Ի���



CBloodpressureDlg::CBloodpressureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BLOODPRESSURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBloodpressureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_droplist);
	DDX_Control(pDX, IDC_EDIT1, m_Buate);
}

BEGIN_MESSAGE_MAP(CBloodpressureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, &CBloodpressureDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CBloodpressureDlg ��Ϣ�������

BOOL CBloodpressureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	m_droplist.AddString("COM1");
	m_droplist.AddString("COM2");
	m_droplist.AddString("COM3");
	m_droplist.AddString("COM4");
	m_droplist.AddString("COM5");
	m_droplist.AddString("COM6");
	m_droplist.AddString("COM7");
	m_droplist.AddString("COM8");

	m_droplist.SetCurSel(0);

	SetDlgItemText(IDC_EDIT1, "9600");
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	hDll_NTPRx = LoadLibraryEx(GetFullPath("RUIYIN_OMRON.dll"), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (!hDll_NTPRx)
	{
		AfxMessageBox("����RUIYIN_OMRON.dllʧ��");
		return FALSE;
	}

	InitializeTEST = (lpInitialize)GetProcAddress(hDll_NTPRx, "Initialize");
	if (NULL == InitializeTEST) { AfxMessageBox("�Ҳ���Initialize����"); return FALSE; }

	SetCallBack = (lpSetCallBack)GetProcAddress(hDll_NTPRx, "SetCallBack");
	if (NULL == SetCallBack) { AfxMessageBox("�Ҳ���SetCallBack����"); return FALSE; }

	SetCallBack(GetBloodPressInfo);

	int nRet = InitializeTEST(2400, 5);
	if (nRet != 1)
	{
		AfxMessageBox("��ʼ��ʧ��");
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBloodpressureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBloodpressureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBloodpressureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CALLBACK GetBloodPressInfo(char* pCardNum)
{
	MessageBox(NULL, pCardNum, "TISHI", MB_OK);
}

void CBloodpressureDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_droplist.GetCurSel();
	CString mesg;
	mesg.Format("%d",i);
//	AfxMessageBox(mesg);
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1); 
	CString str = "2400";
	pBoxOne->GetWindowText(str);
	int Baute = atoi(str);
	int nRet = InitializeTEST(Baute, i+1);
	if (nRet != 1)
	{
		AfxMessageBox("��ʼ��ʧ��");
	}
}
