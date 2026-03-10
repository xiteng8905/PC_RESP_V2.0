#pragma once

// CStaticWave
#include "RESPPackID.h"

#ifndef SCAN_SPEED
#define SCAN_SPEED
typedef enum _SCAN_SPEED_MODE {
SCAN_SPEED_125,
SCAN_SPEED_62_5,
SCAN_SPEED_40,
SCAN_SPEED_25,
SCAN_SPEED_12_5
} SCAN_SPEED_MODE;
#endif

class CStaticWave : public CStatic
{
DECLARE_DYNAMIC(CStaticWave)

public:
CStaticWave();
virtual ~CStaticWave();

protected:
DECLARE_MESSAGE_MAP()
public:
afx_msg void OnPaint();
protected:
unsigned int m_puiData[MAX_COUNT];
BOOL m_pbPeakPoint[MAX_COUNT];
int m_iLastPeakIndex;
int m_iLastValleyIndex;
BOOL m_bValleyArmed;
unsigned int m_uiCurrentPoint;
unsigned int m_uiWidth;
unsigned int m_uiHeight;
unsigned int m_uiRefreshFreq;
void UpdatePeakFlag(unsigned int uiIndex);
int NormalizeWaveY(unsigned int uiData) const;
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
void SetScanSpeed(SCAN_SPEED_MODE tScanSpeed);

// Enable/disable peak marking for this wave control (only mark peaks when enabled)
void SetPeakMarkingEnabled(BOOL bEnable);

protected:
BOOL m_bPeakMarking;
};
