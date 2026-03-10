#pragma once


// CStaticIBPWave
#include "RESPPackID.h"

class CStaticIBPWave : public CStatic
{
	DECLARE_DYNAMIC(CStaticIBPWave)

public:
	CStaticIBPWave();
	virtual ~CStaticIBPWave();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	unsigned int m_puiData[3][MAX_COUNT];
	unsigned int m_uiCurrentPoint;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	unsigned int m_uiRefreshFreq;
	int m_iShowGain;

	//Íø¸ñ²¼¾Ö
	unsigned int x_topLeft ,		y_topLeft ,
						x_topRight ,		y_topRight ,
						x_bottomLeft,		y_bottomLeft,
						x_bottomRight,		y_bottomRight;

public:
	void SetRegion(unsigned int uiWidth, unsigned int uiHeight);
	afx_msg void OnPaint();
	void DrawWave(CPaintDC* pDC);
	void RcvOneData(unsigned int SpO2Data, unsigned int RespData, unsigned int PRData);
	void DrawGrid(CPaintDC* pDC);
	void RefreshWin(void);
	void ResetData(void);
	void SetScale(CPaintDC* pDC);
};


