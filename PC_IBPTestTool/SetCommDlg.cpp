// SetCommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "SetCommDlg.h"


// CSetCommDlg 对话框

IMPLEMENT_DYNAMIC(CSetCommDlg, CDialog)

CSetCommDlg::CSetCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetCommDlg::IDD, pParent)
{
	m_ComNum = 0;
	m_Mode = 1;
}

CSetCommDlg::~CSetCommDlg()
{
}

void CSetCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_ComNum);
	DDX_Radio(pDX, IDC_RADIO5, m_Mode);
}


BEGIN_MESSAGE_MAP(CSetCommDlg, CDialog)
END_MESSAGE_MAP()


// CSetCommDlg 消息处理程序
