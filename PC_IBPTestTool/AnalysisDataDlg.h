#pragma once

#include"Resource.h"
#include "staticdatawave.h"
#include "afxwin.h"
#include "afxcmn.h"

#define SCALSE_COEF_NUM 10
typedef struct  
{
	float m_coef[SCALSE_COEF_NUM];
	UINT m_ScaleMax[SCALSE_COEF_NUM];
	UINT m_ScaleMin[SCALSE_COEF_NUM];
	UCHAR m_ScaleNum[SCALSE_COEF_NUM];
}SetScaleCoef;

// CAnalysisDataDlg dialog
typedef struct  
{
	UCHAR m_SpO2Limit;
	UCHAR m_RespLimit;
	UCHAR m_PRLimit;
}SetLimit;
class CAnalysisDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnalysisDataDlg)

public:
	CAnalysisDataDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAnalysisDataDlg();

// Dialog Data
	enum { IDD = IDD_DATAANALYSIS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetLayout(void);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonOpenfile();
	void AnalyseFile(CString strFileName);
	void AnalyseResult();

public:
	UINT m_nWidth;
	UINT m_nHeight;
	CStaticDataWave m_ReDataSpO2Wave;
	CStaticDataWave m_ReDataPlsWave;
	CStaticDataWave m_ReDataRespWave;
	CStaticDataWave m_ReDataRRWave;
	CStaticDataWave m_ReDataPRWave;
	CScrollBar m_ScrollBarCtrl;
	INT *m_pReadData[5];
	bool m_bFileOpen;
	UINT	 m_nDataCount;  //存储每条曲线的数据点个数
	UINT	 m_nItemCount;  //曲线的条数
	CString  *m_strTitle;	//存储每条曲线的名称
	CArray<int, int> m_checedIndex;  //存储被选中曲线的索引

	SetScaleCoef SpO2Scale;
	/*SetScaleCoef RRScale;*/
	SetScaleCoef PRScale;

	int m_maxValue[5];
	int m_maxValue2[5];
	int m_minValue[5];
	afx_msg void OnBnClickedButtonSetup();
	CComboBox m_ComboSpO2;
	CComboBox m_ComboResp;
	CComboBox m_ComboPR;
	SetLimit m_SetLimit;
	afx_msg void OnBnClickedButtonPulsep();
	afx_msg void OnBnClickedButtonPulsem();
	afx_msg void OnBnClickedButtonSpo2p();
	afx_msg void OnBnClickedButtonSpo2m();
	afx_msg void OnBnClickedButtonRespwavep();
	afx_msg void OnBnClickedButtonRespwavem();
	afx_msg void OnBnClickedButtonRrp();
	afx_msg void OnBnClickedButtonRrm();
	afx_msg void OnBnClickedButtonPrp();
	afx_msg void OnBnClickedButtonPrm();
	afx_msg void OnBnClickedButtonMin();
	afx_msg void OnBnClickedButtonViewrestore();
	CListCtrl m_CListCtrlMessage;
private:
	void InsertMessageToList(CString str);
	float SampleFilterHP005(unsigned char u8Index, float u32Data);
public:
	afx_msg void OnPaint();
};
