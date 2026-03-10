#pragma once

#include "RESPPackID.h"


// CStaticWave


class CSpO2Wave : public CStatic
{
	DECLARE_DYNAMIC(CSpO2Wave)

public:
	CSpO2Wave();
	virtual ~CSpO2Wave();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	unsigned int m_puiData[MAX_COUNT];
	unsigned int m_uiCurrentPoint;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	unsigned int m_uiRefreshFreq;
public:
	void RcvOneData(unsigned int uiData);
	void SetRegion(unsigned int uiWidth, unsigned int uiHeight);
	void ResetData(void);
	void DrawWave(CPaintDC * pDC);
protected:
	int m_iShowGain;
public:
	void SetShowGain(int iShowGain);
	void SetData(unsigned int uiLength, unsigned int * puiData);
	void SetRESPStatus(CString tStrRESPStatus);
	CString m_StrRESPStatus;
	void UpDataRESPStatus(CPaintDC * pDC);
	void DrawGrid(CPaintDC* pDC);
};


