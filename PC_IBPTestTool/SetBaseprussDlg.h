#pragma once

#include"resource.h"
#include "PC_IBPTestToolDlg.h"

// CSetBaseprussDlg 对话框

class CSetBaseprussDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetBaseprussDlg)

public:
	CSetBaseprussDlg(CWnd* pParent = NULL);   // 标准构造函数
	CSetBaseprussDlg(CPC_IBPTestToolDlg *pDlg);   // 标准构造函数
	virtual ~CSetBaseprussDlg();

// 对话框数据
	enum { IDD = IDD_BASEPRUSS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
	CPC_IBPTestToolDlg *pIBPTestToolDlg;
	afx_msg void OnBnClickedNo();
};
