#pragma once


// CViewValue
#include "RESPPackID.h"

class CViewValue : public CStatic
{
	DECLARE_DYNAMIC(CViewValue)

public:
	CViewValue();
	virtual ~CViewValue();
private:
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	unsigned int m_uiSpo2,m_uiResp,m_uiPR;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void SetSpO2Value(unsigned int nSpO2Value);
	void SetPRValue(unsigned int nPRValue);
	void SetRespValue(unsigned int nRespValue);
	void SetRegion(unsigned int uiWidth, unsigned int uiHeight);
};


