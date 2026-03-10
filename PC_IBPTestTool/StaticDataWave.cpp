// StaticDataWave.cpp : implementation file
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "StaticDataWave.h"


// CStaticDataWave

IMPLEMENT_DYNAMIC(CStaticDataWave, CStatic)

CStaticDataWave::CStaticDataWave()
{
	m_piDataBuf = NULL;
	m_uiDataLen = 0;

	m_iWidth = 800;
	m_iHeight = 355;
	m_iWinLeft = 0;
	m_iWinTop = 0;

	m_iRectLeft = 0;
	m_iRectTop = 0;

	m_iMapLeft = 0;

	m_iMult = 1;

	m_WaveTitle = TEXT("Wave");
	m_ViewCoef = 5;
	m_bScaleViewFlag = FALSE;

	m_Scalemin = 0;
}

CStaticDataWave::~CStaticDataWave()
{
}


BEGIN_MESSAGE_MAP(CStaticDataWave, CStatic)
	ON_WM_PAINT()
//	ON_WM_HSCROLL()
END_MESSAGE_MAP()



// CStaticDataWave message handlers



void CStaticDataWave::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	InitPaint(&dc);
	SetBKView(&dc);
	PaintWave();
	dc.BitBlt( 0, 0,m_iWidth, m_WinRect.Height()/m_iMult, &m_dcMemory, m_iMapLeft, m_iRectTop, SRCCOPY);
	m_dcMemory.DeleteDC();
	SetWaveTitle(&dc);
}

void CStaticDataWave::SetBKView(CDC* pDC)
{
	COLORREF m_BGColor = RGB(10,60,10);
	m_dcMemory.FillSolidRect(&m_WinRect, m_BGColor);
}

void CStaticDataWave::InitPaint(CDC* pDC)
{
	m_WinRect.left = 0;
	m_WinRect.top = 0;
	if (m_uiDataLen>m_iWidth-20)
	{
		m_WinRect.right = (m_uiDataLen+30)*m_iMult;
	}
	else
	{
		m_WinRect.right = m_iWidth*m_iMult;
	}

	m_WinRect.bottom = m_iHeight*m_iMult;

	if(!m_dcMemory.CreateCompatibleDC(pDC))				
	{
		MessageBox(_T("Fail to create a DC !"),NULL,MB_ICONERROR);
		::PostQuitMessage(0);
	}

	CBitmap m_Bmp;
	m_Bmp.CreateCompatibleBitmap(pDC, m_WinRect.Width(), m_WinRect.Height());
	SelectObject(m_dcMemory.GetSafeHdc(), m_Bmp);
}

void CStaticDataWave::InputWaveData(int *pDataBuf, unsigned int uiLen)
{
	m_uiDataLen = uiLen;

	m_piDataBuf = new int[m_uiDataLen];

	for (UINT i=0; i<m_uiDataLen; i++)
	{
		m_piDataBuf[i] = pDataBuf[i];
	}

	Invalidate();
}

void CStaticDataWave::PaintWave(void)
{
	COLORREF mColor =RGB(100,255,100);

	CPen cNetPen(PS_SOLID, 1, mColor);
	CPen * pcOldPen = m_dcMemory.SelectObject(&cNetPen);

	int iWaveBeg;

	if (m_piDataBuf!=NULL)
	{		
		for(int i = 0; i < m_uiDataLen;i++)
		{	
			if (m_piDataBuf[i] != INVALID_VALUE)
			{
				m_dcMemory.MoveTo(i,-m_piDataBuf[i]/m_ViewCoef+m_WinRect.bottom-5);
				m_dcMemory.LineTo(i+1,-m_piDataBuf[i+1]/m_ViewCoef+m_WinRect.bottom-5);
			}
		}
	}	
}

void CStaticDataWave::SetMapStartPoint(unsigned int ipos)
{
	m_iMapLeft = ipos;
	Invalidate(TRUE);
}

void CStaticDataWave::SetRegion(unsigned int tWidth, unsigned int tHeight)
{
	m_iHeight = tHeight;
	m_iWidth  = tWidth;
	Invalidate();
}

void CStaticDataWave::SetWaveTitle(CString str)
{
	m_WaveTitle = str;
	Invalidate();
}

void CStaticDataWave::SetWaveTitle(CPaintDC* pDC)
{
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(60,3,m_WaveTitle);
	
	if (m_bScaleViewFlag == TRUE)
	{
		CPen NewPen(PS_SOLID, 1, RGB(255,255, 0));
		CPen * pcOldPen = pDC->SelectObject(&NewPen);

		pDC->MoveTo(5,5);
		pDC->LineTo(5,m_iHeight-5);

		for (INT t = 0; t<=m_ScaleNum;t++)
		{
			pDC->MoveTo(5,t*(m_iHeight-10)/m_ScaleNum+5);
			pDC->LineTo(12,t*(m_iHeight-10)/m_ScaleNum+5);
		}
		CString str;
		str.Format(_T("%d"),m_Scalemin);
		pDC->TextOut(15,m_iHeight-15,str);
		str.Format(_T("%d"),m_Scalemax);
		pDC->TextOut(15,1,str);
	}
}

void CStaticDataWave::SetViewCoef(float fCoef)
{
	m_ViewCoef = fCoef;
	Invalidate();
}

void CStaticDataWave::ScaleViewEnale(BOOL tFlag,int Min,int Max,int num)
{
	m_bScaleViewFlag = tFlag;
	m_Scalemax = Max;
	m_Scalemin = Min;
	m_ScaleNum = num;

	Invalidate();
}