#pragma once
#include"Resource.h"
#include "staticibpwave.h"

// CTrendChartDlg dialog

class CTrendChartDlg : public CDialog
{
	DECLARE_DYNAMIC(CTrendChartDlg)

public:
	CTrendChartDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrendChartDlg();

// Dialog Data
	enum { IDD = IDD_TREND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStaticIBPWave m_TrendShow;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	int Test(void);
};
