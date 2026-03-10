// TrendChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrendChartDlg.h"


// CTrendChartDlg dialog

IMPLEMENT_DYNAMIC(CTrendChartDlg, CDialog)

CTrendChartDlg::CTrendChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrendChartDlg::IDD, pParent)
{

}

CTrendChartDlg::~CTrendChartDlg()
{
}

void CTrendChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TRENDCHART, m_TrendShow);
}


BEGIN_MESSAGE_MAP(CTrendChartDlg, CDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTrendChartDlg message handlers

BOOL CTrendChartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowText(TEXT("睡眠监测趋势显示"));
	//整个大小	
	CRgn m_rgn; 
	RECT rc; 
	MoveWindow(0,0,1051,401);
	CenterWindow();
	GetClientRect(&rc); 
	m_rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,30,30); 
	SetWindowRgn(m_rgn,FALSE); 

	m_TrendShow.SetRegion(1050,400);
	GetDlgItem(IDC_STATIC_TRENDCHART)->MoveWindow(0,0,1050,420);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTrendChartDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CDialog::OnLButtonDown(nFlags, point);
}

int CTrendChartDlg::Test(void)
{
	::SetWindowPos( m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE||SWP_NOSIZE);
	::SetWindowPos( m_hWnd,HWND_NOTOPMOST,10,10,10,10,  SWP_NOMOVE|SWP_NOSIZE);
	return 0;
}
