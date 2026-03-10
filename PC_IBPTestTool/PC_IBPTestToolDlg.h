// PC_IBPTestToolDlg.h : 头文件
//

#pragma once
#include "StaticWave.h"

#define WAVE_W 930
#define WAVE_H 445

#define TITLE_W 1000
#define TITLE_H 100

#define CLIENT_W 1100//(WAVE_W+0)
#define CLIENT_H 600//(TITLE_H+WAVE_H)

#include "ComWatchThread.h"
#include "ComPort.h"
#include "SetCommDlg.h"

#include "BtnST.h"

#include"resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "setvalueview.h"
#include "SkinStatic.h"
#include "EnBitmap.h"

#include "SleepMonitorDlg.h"


extern "C"
{
#include "WitleafRespLib.h"
}

// CPC_IBPTestToolDlg 对话框
class CPC_IBPTestToolDlg : public CDialog
{
// 构造
public:
	CPC_IBPTestToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PC_IBPTESTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStaticWave m_CStaticWave;
	float m_fPrussure;
//	CSleepMonitorDlg *pSleepMonitorDlg;
	//数据存储初始化
	FILE *m_pfSaveData;
	int i32perSecCount;
	void RcvData(WITLEAF_PACKET tPacket);

	CComPort *m_pcComPort;
	CComWatchThread *m_pcComWatchThread;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetCurrentPRValue(float tValue);
	void SetCurrentRESPValue(UCHAR RespRate,UCHAR RespFlag);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	void DrawBackground(CDC* pDC);
	CMenu m_cMenu;
public:
	afx_msg void OnStnClickedStaticWave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CButtonST m_ButtonQuit;
	afx_msg void OnBnClickedTopquit();
//	SetValueView m_PRViewValue;
//	CSkinStatic m_PrussureView;
	void InitAlgorithm(void);
	afx_msg void OnBnClickedSavedata();
	bool StartWitleaf_CmdHandler(WITLEAF_PACKET tPacket);
	afx_msg void OnBnClickedCalibration();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuQueryInfo();
	afx_msg void OnMenuCheckLeakage();
	afx_msg void OnMenuResetModule();
	afx_msg void OnMenuSetBasePress();
	afx_msg void OnSetAdultMode();
	afx_msg void OnSetChildMode();
	afx_msg void OnSetNewbornMode();
	void SendCmdPacket(WITLEAF_PACKET tPacket);
	int SampleFilterHP005(unsigned char u8Index, int u32Data);
	void SetBaseprussCmd(unsigned char t);
	afx_msg void OnBnClickedButton1();
	int FilterHighPass0_15(int iData);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnScan500();
	afx_msg void OnScan250();
	afx_msg void OnScan125();
	afx_msg void OnScan100();
	afx_msg void OnScan50();
	afx_msg void OnSetviewx1();
	afx_msg void OnSetviewx2();
	afx_msg void OnSetviewx3();
	afx_msg void OnMenuRebrush();
	afx_msg void OnBnClickedSetmode();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnModulestop();
	afx_msg void OnModulestart();
	afx_msg void OnSensitivty1();
	afx_msg void OnSensitivty2();
	afx_msg void OnSensitivty3();
	afx_msg void OnSensitivty4();
	afx_msg void OnSensitivty5();
};
