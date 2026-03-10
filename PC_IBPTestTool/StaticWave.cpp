// StaticWave.cpp : implementation file
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "StaticWave.h"
#include "SrchPulse.h"


// CStaticWave

IMPLEMENT_DYNAMIC(CStaticWave, CStatic)

CStaticWave::CStaticWave()
{
	for ( int i = 0; i < MAX_COUNT; i ++ ) 
	{
		m_puiData[i] = DEFAULT_VALUE;
		m_pbPeakPoint[i] = FALSE;
	}

	m_iLastPeakIndex = -1;
	m_iLastValleyIndex = -1;
	m_bValleyArmed = FALSE;
	m_uiCurrentPoint = 0;

	m_uiWidth = 1;
	m_uiHeight = 1;

	m_uiRefreshFreq = 0;

	m_iShowGain = 1;

	m_StrRESPStatus =_T("");
	ResetSrchPulse();

	m_bPeakMarking = TRUE; // default: mark peaks
}

CStaticWave::~CStaticWave()
{
}


BEGIN_MESSAGE_MAP(CStaticWave, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStaticWave message handlers



void CStaticWave::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages

	DrawWave(&dc);
	UpDataRESPStatus(&dc);

	ReleaseDC(&dc);
}

void CStaticWave::RcvOneData(unsigned int uiData)
{
	int iPrevPeakIndex = m_iLastPeakIndex;

	if ((uiData == 0xFF)||(uiData == 127))
	{
		m_puiData[m_uiCurrentPoint] = SPO2_DEFAULT_VALUE;
	}
	else
	{
		m_puiData[m_uiCurrentPoint] =  uiData*2+100;
	}

	m_pbPeakPoint[m_uiCurrentPoint] = FALSE;
	// only update peak flags if peak marking is enabled for this control
	if (m_bPeakMarking)
	{
		UpdatePeakFlag(m_uiCurrentPoint);
	}

	int iNewPeakIndex = m_iLastPeakIndex;

	m_uiCurrentPoint ++;

	if ( m_uiCurrentPoint == m_uiWidth )
	{
		m_uiCurrentPoint = 0;
	}
	
	for ( int i = 0; i < 15; i ++ ) 
	{
		unsigned int uiTemp = m_uiCurrentPoint + i;
		if ( uiTemp >= m_uiWidth )
			uiTemp = uiTemp - m_uiWidth;
		m_puiData[uiTemp] = INVALID_VALUE;
		m_pbPeakPoint[uiTemp] = FALSE;
	}

	CRect cRectScan(max(0, (int)m_uiCurrentPoint - 20), 0, min((int)m_uiWidth, (int)m_uiCurrentPoint + 20), m_uiHeight);
	InvalidateRect(cRectScan, false);

	if (iPrevPeakIndex >= 0)
	{
		CRect cRectPeakOld(max(0, iPrevPeakIndex - 8), 0, min((int)m_uiWidth, iPrevPeakIndex + 8), m_uiHeight);
		InvalidateRect(cRectPeakOld, false);
	}
	if (iNewPeakIndex >= 0)
	{
		CRect cRectPeakNew(max(0, iNewPeakIndex - 8), 0, min((int)m_uiWidth, iNewPeakIndex + 8), m_uiHeight);
		InvalidateRect(cRectPeakNew, false);
	}
}

void CStaticWave::SetRegion(unsigned int uiWidth, unsigned int uiHeight)
{
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;
}

void CStaticWave::ResetData(void)
{
	for ( int i = 0; i < MAX_COUNT; i ++ ) 
	{
		m_puiData[i] = DEFAULT_VALUE;
		m_pbPeakPoint[i] = FALSE;
	}

	m_iLastPeakIndex = -1;
	m_iLastValleyIndex = -1;
	m_bValleyArmed = FALSE;
	m_uiCurrentPoint = 0;
	ResetSrchPulse();
}

void CStaticWave::DrawWave(CPaintDC * pDC)
{

	CRect tRect(0, 0, m_uiWidth, m_uiHeight);

	CBrush cNewBrush;
	cNewBrush.CreateSolidBrush(RGB(50, 50, 50));
	pDC->FillRect(&tRect, &cNewBrush);
	DeleteObject(cNewBrush);
	CPen cNewPen,cNewPen1;
	cNewPen.CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
	cNewPen1.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	CPen * pcOldPen = pDC->SelectObject(&cNewPen);
	
	for ( unsigned int i = 0; i < m_uiWidth - 1; i ++ ) 
	{
		if ( (INVALID_VALUE == m_puiData[i]) || (INVALID_VALUE == m_puiData[i + 1]) ) 
		{
			continue;
		}
		int y1 = NormalizeWaveY(m_puiData[i]);
		int y2 = NormalizeWaveY(m_puiData[i + 1]);

		if(y2<48)
		{
			pDC->SelectObject(&cNewPen1);
		}
		else
		{
			pDC->SelectObject(&cNewPen);
		}
		
		pDC->MoveTo(i, y1);
		pDC->LineTo(i + 1, y2);
	}

	CPen cPeakPen;
	cPeakPen.CreatePen(PS_SOLID, 1, RGB(255, 80, 80));
	CBrush cPeakBrush;
	cPeakBrush.CreateSolidBrush(RGB(255, 80, 80));
	CPen* pOldPeakPen = pDC->SelectObject(&cPeakPen);
	CBrush* pOldPeakBrush = pDC->SelectObject(&cPeakBrush);
	for (unsigned int i = 0; i < m_uiWidth; i++)
	{
		if (!m_pbPeakPoint[i] || m_puiData[i] == INVALID_VALUE)
		{
			continue;
		}

		int y = NormalizeWaveY(m_puiData[i]);
		pDC->Ellipse(i - 3, y - 3, i + 3, y + 3);
	}
	pDC->SelectObject(pOldPeakBrush);
	pDC->SelectObject(pOldPeakPen);

	pDC->SelectObject(pcOldPen);
	DeleteObject(cNewPen);

	/*CRect tRect(0, 0, m_uiWidth, m_uiHeight);

	CBrush cNewBrush;
	cNewBrush.CreateSolidBrush(RGB(40, 40, 40));
	pDC->FillRect(&tRect, &cNewBrush);
	DeleteObject(cNewBrush);
	CPen cNewPen,cNewPen1;
	cNewPen.CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
	cNewPen1.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	CPen * pcOldPen = pDC->SelectObject(&cNewPen);
	
	for ( unsigned int i = 0; i < m_uiWidth - 1; i ++ ) 
	{
		if ( (INVALID_VALUE == m_puiData[i]) || (INVALID_VALUE == m_puiData[i + 1]) ) 
		{
			continue;
		}
		int y1 = (m_uiHeight - (((m_puiData[i] - 256) * m_iShowGain) + 256) * m_uiHeight / 512);
		int y2 = (m_uiHeight - (((m_puiData[i + 1] - 256) * m_iShowGain) + 256) * m_uiHeight / 512);
			
		if(y2<48)
		{
			pDC->SelectObject(&cNewPen1);
		}
		else
		{
			pDC->SelectObject(&cNewPen);
		}
		
		if (y1>m_uiHeight - 10)
		{
			y1 = m_uiHeight - 10;
		}
		else if (y1<20)
		{
			y1= 20;
		}

		if (y2>m_uiHeight - 10)
		{
			y2=m_uiHeight - 10;
		}
		else if (y2<20)
		{
			y2= 20;
		}
		pDC->MoveTo(i, y1);
		pDC->LineTo(i + 1, y2);
	}

	pDC->SelectObject(pcOldPen);
	DeleteObject(cNewPen);*/
}

void CStaticWave::SetShowGain(int iShowGain)
{
	m_iShowGain = iShowGain;
}

void CStaticWave::SetData(unsigned int uiLength, unsigned int * puiData)
{
	for (unsigned int i = 0; i < uiLength; i ++ ) 
	{
		m_puiData[i] = puiData[i];
	}

	Invalidate();
}

void CStaticWave::SetRESPStatus(CString tStrRESPStatus)
{

	if (m_StrRESPStatus == tStrRESPStatus)
	{
		return;
	}
	else
	{
		m_StrRESPStatus = tStrRESPStatus;	
		CRect cRect(m_uiWidth - 160, 0,m_uiWidth, 25);
		InvalidateRect(cRect, false);
	}
}

void CStaticWave::UpDataRESPStatus(CPaintDC * pDC)
{
	//CFont tFont;

	//tFont.CreateFont(
	//	20,			//height
	//	0,			//average character width
	//	0,			//angle of escapement
	//	0,			//base-line orientation angle
	//	FW_NORMAL,	//font weight
	//	0,			//italic attribute option
	//	0,			//underline attribute option
	//	0,			//strikeout attribute option
	//	DEFAULT_CHARSET,	//character set identifier
	//	OUT_DEFAULT_PRECIS,	//output precision
	//	CLIP_DEFAULT_PRECIS,//clipping precision
	//	DEFAULT_QUALITY,	//output quality
	//	DEFAULT_PITCH,		//pitch and family
	//	_T("Times New Roman")			//typeface nameËÎÌå
	//	);

	CFont tFont;

	tFont.CreateFont(
		20,			//height
		0,			//average character width
		0,			//angle of escapement
		0,			//base-line orientation angle
		FW_NORMAL,	//font weight
		0,			//italic attribute option
		0,			//underline attribute option
		0,			//strikeout attribute option
		DEFAULT_CHARSET,	//character set identifier
		OUT_DEFAULT_PRECIS,	//output precision
		CLIP_DEFAULT_PRECIS,//clipping precision
		DEFAULT_QUALITY,	//output quality
		DEFAULT_PITCH,		//pitch and family
		_T("Times New Roman")			//typeface nameËÎÌå
		);

	CFont * pcOldFont = pDC->SelectObject(&tFont);
	pDC->SetTextColor(RGB(255,50, 255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(10,5,m_StrRESPStatus);

}

void CStaticWave::SetScanSpeed(SCAN_SPEED_MODE tScanSpeed)
{
	UCHAR count = 1;
	switch (tScanSpeed)
	{
	case SCAN_SPEED_125:
		count = 1;
		break;
	case SCAN_SPEED_62_5:
		count = 2;
		break;
	case SCAN_SPEED_40:
		count = 3;
		break;
	case SCAN_SPEED_25:
		count = 5;
		break;
	case SCAN_SPEED_12_5:
		count = 10;
		break;

	default:
		count = 1;
		break;
	}

	m_uiRefreshFreq = count; 

	Invalidate();
}

int CStaticWave::NormalizeWaveY(unsigned int uiData) const
{
	int y = (m_uiHeight - (((uiData - 256) * m_iShowGain) + 256) * m_uiHeight / 512);
	if (y > (int)m_uiHeight - 10)
	{
		y = m_uiHeight - 10;
	}
	else if (y < 20)
	{
		y = 20;
	}
	return y;
}

void CStaticWave::UpdatePeakFlag(unsigned int uiIndex)
{
	UNREFERENCED_PARAMETER(uiIndex);

	if (m_uiWidth == 0)
	{
		return;
	}

	const unsigned int uiValue = m_puiData[m_uiCurrentPoint];
	if (uiValue == INVALID_VALUE)
	{
		return;
	}

	SrchPulse((INT32)uiValue);

	if (PulPeakTag == 0xFF)
	{
		return;
	}

	unsigned int uiTag = (unsigned int)PulPeakTag;
	if (uiTag >= m_uiWidth)
	{
		return;
	}

	unsigned int uiPeakIndex = (m_uiCurrentPoint + m_uiWidth - uiTag) % m_uiWidth;
	if (m_puiData[uiPeakIndex] == INVALID_VALUE)
	{
		return;
	}

	m_pbPeakPoint[uiPeakIndex] = TRUE;
	m_iLastPeakIndex = (int)uiPeakIndex;

	if (PulValyTag != 0xFF)
	{
		m_iLastValleyIndex = (int)((m_uiCurrentPoint + m_uiWidth - (unsigned int)PulValyTag) % m_uiWidth);
	}
}

void CStaticWave::SetPeakMarkingEnabled(BOOL bEnable)
{
    m_bPeakMarking = bEnable ? TRUE : FALSE;
}
