// CalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CalDlg.h"

// CCalDlg 对话框

IMPLEMENT_DYNAMIC(CCalDlg, CDialog)

CCalDlg::CCalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalDlg::IDD, pParent)
{
	m_Comprot = NULL;
}

CCalDlg::CCalDlg(CComPort *tComprot)
{
	m_Comprot = tComprot; 	
}

CCalDlg::~CCalDlg()
{
}

void CCalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CANCEL_CAL, &CCalDlg::OnBnClickedCancelCal)
	ON_BN_CLICKED(IDC_START_CAL, &CCalDlg::OnBnClickedStartCal)
	ON_BN_CLICKED(IDC_CONF_CAL, &CCalDlg::OnBnClickedConfCal)
END_MESSAGE_MAP()


// CCalDlg 消息处理程序

void CCalDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

void CCalDlg::OnBnClickedCancelCal()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char CalPacket[10] = {0xFA,0x0A,0x06,0x01,0x21,0x00,0x00,0x00,0x00,0x32};

	m_Comprot->Send(CalPacket,10);

// 	if(6==MessageBox(_T("确定退出？"),_T("提示："),MB_YESNO|MB_ICONQUESTION))
// 	{
		PostMessage(WM_CLOSE,0,0);
//	}
}

void CCalDlg::OnBnClickedStartCal()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char CalPacket[10] = {0xFA,0x0A,0x06,0x01,0x20,0x00,0x00,0x00,0x00,0x31};
	
	m_Comprot->Send(CalPacket,10);
}

void CCalDlg::OnBnClickedConfCal()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char CalPacket[10] = {0xFA,0x0A,0x06,0x01,0x40,0x00,0x00,0x00,0x00,0x51};

	m_Comprot->Send(CalPacket,10);
}

BOOL CCalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CFont *font1;
	font1 = new CFont;
	font1->CreateFont(20, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, TEXT("Times New Roman"));

	GetDlgItem(IDC_TITLE1)->SetFont(font1);

//	MoveWindow(0,0,145,260);
/*	CRgn m_rgn; 
	RECT rc; 
	GetWindowRect(&rc); 
	m_rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,30,30); 
	SetWindowRgn(m_rgn,FALSE); */

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
