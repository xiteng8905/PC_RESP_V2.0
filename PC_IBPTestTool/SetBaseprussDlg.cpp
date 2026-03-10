// SetBaseprussDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SetBaseprussDlg.h"


// CSetBaseprussDlg 对话框

IMPLEMENT_DYNAMIC(CSetBaseprussDlg, CDialog)

CSetBaseprussDlg::CSetBaseprussDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetBaseprussDlg::IDD, pParent)
{

}

CSetBaseprussDlg::CSetBaseprussDlg(CPC_IBPTestToolDlg *pDlg)
{
	pIBPTestToolDlg=pDlg;
}
CSetBaseprussDlg::~CSetBaseprussDlg()
{
}

void CSetBaseprussDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetBaseprussDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSetBaseprussDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDNO, &CSetBaseprussDlg::OnBnClickedNo)
END_MESSAGE_MAP()


// CSetBaseprussDlg 消息处理程序

void CSetBaseprussDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	UCHAR prussure;
	GetDlgItemText(IDC_INTPUTVALUE,str);
	prussure = _ttoi(str);   //将字符串转换为十进制数据
	
	if ((prussure >9)&&(prussure<21))
	{
		pIBPTestToolDlg->SetBaseprussCmd(prussure);
	}
	else MessageBox(TEXT("压力设置不对！\t\r压力范围：10~20"),TEXT("警告！"),MB_ICONWARNING);
}

void CSetBaseprussDlg::OnBnClickedNo()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_CLOSE,0,0);
}
