#pragma once


// CStaticDataWave
#include "RESPPackID.h"

class CStaticDataWave : public CStatic
{
	DECLARE_DYNAMIC(CStaticDataWave)

public:
	CStaticDataWave();
	virtual ~CStaticDataWave();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void SetBKView(CDC* pDC);
	void InitPaint(CDC* pDC);
	void InputWaveData(int *pDataBuf, unsigned int iLen);
	void PaintWave(void);

public:
	CRect m_uiClientRect;
	CRect m_WinRect;
	COLORREF m_uiBGColor;
	UINT m_uiDataLen;
	int *m_piDataBuf;
	CDC m_dcMemory;
	CString m_WaveTitle;
	float m_ViewCoef;

	int m_iWidth;
	int m_iHeight;

	int m_iMult;

	int m_iWinLeft;
	int m_iWinTop;

	int m_iRectLeft;
	int m_iRectTop;
	int m_iMapLeft;
	
	bool m_bScaleViewFlag;
	int m_Scalemin;
	int m_Scalemax;
	int m_ScaleNum;

	void SetMapStartPoint(unsigned int ipos);
	void SetRegion(unsigned int tWidth, unsigned int tHeight);
	void SetWaveTitle(CString str);
	void SetWaveTitle(CPaintDC* pDC);
	void SetViewCoef(float fCoef);
	void ScaleViewEnale(BOOL tFlag,int Min,int Max,int num);
};


