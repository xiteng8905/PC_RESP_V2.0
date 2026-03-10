#pragma once
#include "staticwave.h"
#include "spO2wave.h"
#include "viewvalue.h"
#include "ComWatchThread.h"
#include "RESPPackID.h"
#include "TrendChartDlg.h"
#include "AnalysisDataDlg.h"
#include "CAddDataShow.h"

#ifndef IDD_SLEEPMONITOR_DIALOG

#define IDD_SLEEPMONITOR_DIALOG         136

#endif
//////////////////////////////////////////////////////////////////////////
#define RESP_WAVE_W 740
#define RESP_WAVE_H 178

#define TITLE_W 900
#define TITLE_H 100

#define SLEEP_CLIENT_W  (TITLE_W + 250)
#define SLEEP_CLIENT_H  ( RESP_WAVE_H*3 + TITLE_H)
//////////////////////////////////////////////////////////////////////////

// CSleepMonitorDlg 对话框
typedef struct
{
	UINT m_RespRate;
	UINT m_PulseRate;
	UINT m_SpO2Value;
	
	UINT m_PulseWave;
	UINT m_RespWave;

	UINT SpO2TimeConut;
	UINT RespTimeConut;
	UINT TimeConut;
}TrendShowData;

class CSleepMonitorDlg : public CDialog
{
	DECLARE_DYNAMIC(CSleepMonitorDlg)

public:
	CSleepMonitorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSleepMonitorDlg();

// 对话框数据
	enum { IDD = IDD_SLEEPMONITOR_DIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStaticWave m_RespWave;
	CSpO2Wave m_SpO2Wave;
	CViewValue m_ViewValue;
	CComWatchThread *m_pcComWatchThread;
	CTrendChartDlg *m_TrendDlg;
	TrendShowData m_TrendShowData;

	virtual BOOL OnInitDialog();
	void RcvData(WITLEAF_PACKET tWitleafPacket);
	

private:
	void RcvCaliResult(unsigned int uiPluseRate, unsigned char ucSpO2, unsigned int uiPi, unsigned char ucStatu1, unsigned char ucStatu2);
	int SleepSampleFilterHP005(unsigned char u8Index, float u32Data);
public:
	CComPort *m_pcComPort;
	void SendCmdPacket(WITLEAF_PACKET tPacket);
	void RcvConnectAck(void);
	void InitCommPortThread(void);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CMenu m_cMenu;
	afx_msg void OnSleepStart();
	void SetCurrentRESPValue(unsigned char RespRate, unsigned char RespFlag);

	afx_msg void OnSleepSavewave();
	FILE *m_pfSaveData;
	FILE* m_pfSaveSPO2Data;
	afx_msg void OnSleepSyncviewwave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	CBitmap m_SleepMainBk;
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void RefreshView(char tOnePart);
	afx_msg void OnBnClickedQuit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSleepProgramversion();
	afx_msg void OnSleepDataanalysis();
	afx_msg void OnTrendTrendhide();
	afx_msg void OnStnClickedVeiwvalue();
	CStaticWave m_RedWave;
	CAddDataShow m_AddDataShow;
};
