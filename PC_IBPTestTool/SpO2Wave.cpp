// StaticWave.cpp : implementation file
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "SpO2Wave.h"

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

// CStaticWave

IMPLEMENT_DYNAMIC(CSpO2Wave, CStatic)

CSpO2Wave::CSpO2Wave()
{
	for ( int i = 0; i < MAX_COUNT; i ++ ) 
		m_puiData[i] = DEFAULT_VALUE;

	m_uiCurrentPoint = 0;

	m_uiWidth = 1;
	m_uiHeight = 1;

	m_uiRefreshFreq = 0;

	m_iShowGain = 1;

	m_StrRESPStatus =_T("");
}

CSpO2Wave::~CSpO2Wave()
{
}


BEGIN_MESSAGE_MAP(CSpO2Wave, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStaticWave message handlers



void CSpO2Wave::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages

	DrawGrid(&dc);
	DrawWave(&dc);
	UpDataRESPStatus(&dc);

	ReleaseDC(&dc);
}

void CSpO2Wave::RcvOneData(unsigned int uiData)
{
	/*static UCHAR temp=0;

	temp++;
	if (temp>=m_uiRefreshFreq)
	{
		temp = 0;
	}
	else
		return;*/
	
	if (uiData == 0xFF)
	{
		m_puiData[m_uiCurrentPoint] = SPO2_DEFAULT_VALUE;
	}
	else
	m_puiData[m_uiCurrentPoint] = uiData*2+150;

	m_uiCurrentPoint ++;

	if ( m_uiCurrentPoint == m_uiWidth )
	{
		m_uiCurrentPoint = m_uiCurrentPoint;
	}
	
	for ( int i = 0; i < 10; i ++ ) 
	{
		unsigned int uiTemp = m_uiCurrentPoint + i;
		if ( uiTemp >= m_uiWidth )
			uiTemp = uiTemp - m_uiWidth;
		m_puiData[uiTemp] = INVALID_VALUE;
	}

	CRect cRect(m_uiCurrentPoint - 2, 0, m_uiCurrentPoint + 1,m_uiHeight);
	InvalidateRect(cRect, false);

	if ( m_uiCurrentPoint >= m_uiWidth )
		m_uiCurrentPoint = 0;

}

void CSpO2Wave::SetRegion(unsigned int uiWidth, unsigned int uiHeight)
{
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;
}

void CSpO2Wave::ResetData(void)
{
	for ( int i = 0; i < MAX_COUNT; i ++ ) 
		m_puiData[i] = DEFAULT_VALUE;

	m_uiCurrentPoint = 0;

//	m_uiRefreshFreq = 0;
}

void CSpO2Wave::DrawWave(CPaintDC * pDC)
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
		int y1 = (m_uiHeight - (((m_puiData[i] - 256) * m_iShowGain) + 256) * m_uiHeight / 512);
		int y2 = (m_uiHeight - (((m_puiData[i + 1] - 256) * m_iShowGain) + 256) * m_uiHeight / 512);
				
		pDC->MoveTo(i, y1);
		pDC->LineTo(i + 1, y2);
	}

	pDC->SelectObject(pcOldPen);
	DeleteObject(cNewPen);
}

void CSpO2Wave::SetShowGain(int iShowGain)
{
	m_iShowGain = iShowGain;
}

void CSpO2Wave::SetData(unsigned int uiLength, unsigned int * puiData)
{
	for (unsigned int i = 0; i < uiLength; i ++ ) 
	{
		m_puiData[i] = puiData[i];
	}

	Invalidate();
}

void CSpO2Wave::SetRESPStatus(CString tStrRESPStatus)
{

	if (m_StrRESPStatus == tStrRESPStatus)
	{
		return;
	}
	else
	{
		m_StrRESPStatus = tStrRESPStatus;	
		CRect cRect(m_uiWidth - 500, 0,m_uiWidth, 25);
		InvalidateRect(cRect, false);
	}
}

void CSpO2Wave::UpDataRESPStatus(CPaintDC * pDC)
{
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
	
	int a = m_StrRESPStatus.GetLength(); 

	pDC->TextOut(m_uiWidth-a*9,5,m_StrRESPStatus);
	pDC->SetTextColor(RGB(255,250, 255));
	pDC->TextOut(10,5,_T("Pulse Wave"));
}

void CSpO2Wave::DrawGrid(CPaintDC* pDC)
{
/*	int j,k;
	int x,y;
	int y_gap = m_uiHeight/40, 
		x_gap=m_uiWidth/y_gap;

	//vert
	j=0;
	while (true)
	{
		x = int(j*x_gap);
		if(x>m_uiWidth)
			break;
		k=0;
		while(true)
		{
			y = int(k*y_gap);
			if(y>m_uiHeight)
				break;
			pDC->SetPixel(x,y,RGB(150,150,150));

			k++;
		}
		j++;
	}*/
}
