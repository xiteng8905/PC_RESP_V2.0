#pragma once
#include "resource.h"
#include "ComPort.h"

// CCalDlg 对话框

class CCalDlg : public CDialog
{
	DECLARE_DYNAMIC(CCalDlg)

public:
	CCalDlg(CWnd* pParent = NULL);   // 标准构造函数
	CCalDlg(CComPort *tComprot);
	virtual ~CCalDlg();

// 对话框数据
	enum { IDD = IDD_CALDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancelCal();

	CComPort *m_Comprot;
	afx_msg void OnBnClickedStartCal();
	afx_msg void OnBnClickedConfCal();
	virtual BOOL OnInitDialog();
};
