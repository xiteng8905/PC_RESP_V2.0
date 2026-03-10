#pragma once
#include "afxwin.h"


// CSetCommDlg 对话框

class CSetCommDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetCommDlg)

public:
	CSetCommDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetCommDlg();

// 对话框数据
	enum { IDD = IDD_SETCOMM_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ComNum;
	int m_Mode;
};
