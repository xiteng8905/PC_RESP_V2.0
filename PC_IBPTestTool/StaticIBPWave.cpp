// StaticIBPWave.cpp : 实现文件
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "StaticIBPWave.h"


// CStaticIBPWave

IMPLEMENT_DYNAMIC(CStaticIBPWave, CStatic)

CStaticIBPWave::CStaticIBPWave()
{
	for ( int i = 0; i < MAX_COUNT; i ++ ) 
	{
		m_puiData[0][i] = DEFAULT_VALUE;	
		m_puiData[1][i] = DEFAULT_VALUE;
		m_puiData[2][i] = DEFAULT_VALUE;
	}
	m_uiCurrentPoint = 0;

	m_uiWidth = 100;
	m_uiHeight = 100;

	m_uiRefreshFreq = 0;

	m_iShowGain = 1;

}

CStaticIBPWave::~CStaticIBPWave()
{
}


BEGIN_MESSAGE_MAP(CStaticIBPWave, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStaticIBPWave 消息处理程序



void CStaticIBPWave::SetRegion(unsigned int uiWidth, unsigned int uiHeight)
{
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;

	//网格布局
	// 	m_uiWidth,m_uiHeight
		x_topLeft =80,		y_topLeft = 28,
		x_topRight = m_uiWidth-10,		y_topRight = y_topLeft,
		x_bottomLeft = x_topLeft,		y_bottomLeft = m_uiHeight - 10,
		x_bottomRight = x_topRight,		y_bottomRight = y_bottomLeft;

		m_uiCurrentPoint = 0;
}

void CStaticIBPWave::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	DrawWave(&dc);
	SetScale(&dc);
//	ReleaseDC(&dc);
}

void CStaticIBPWave::DrawWave(CPaintDC* pDC)
{
	CRect tRect(0, 0, m_uiWidth, m_uiHeight);

	CBrush NewBrush;
	NewBrush.CreateSolidBrush(RGB(0, 0, 0));
	pDC->FillRect(&tRect, &NewBrush);
	DeleteObject(NewBrush);
//////////////////////////////////////////////////////////////////////////
	CPen NewPen(PS_SOLID, 2, RGB(220,220, 220));
	CPen * pcOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(0, 0);
	pDC->LineTo(0, m_uiHeight);
	pDC->LineTo(m_uiWidth, m_uiHeight);
	pDC->LineTo(m_uiWidth, 0);
	pDC->LineTo(0, 0);
	//////////////////////////////////////////////////////////////////////////
	DrawGrid(pDC);
	//////////////////////////////////////////////////////////////////////////
	CPen cNewPen1,cNewPen2,cNewPen3,cNewPen4;
	cNewPen1.CreatePen(PS_SOLID, 1, RGB(50,255, 50 ));
	cNewPen2.CreatePen(PS_SOLID, 1, RGB(255,50, 50 ));
	cNewPen3.CreatePen(PS_SOLID, 1, RGB(255, 255,50 ));

	cNewPen4.CreatePen(PS_SOLID, 5, RGB(255, 255,50 ));

	CFont f1,f2,*pOldFont=NULL;
	f1.CreatePointFont(600, _T("System"), pDC);  
	f2.CreatePointFont(120, _T("Times New Roman"), pDC);  
	pOldFont = pDC->SelectObject(&f1);
	pDC->SetTextColor(RGB(45,45,45));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(m_uiWidth/3,m_uiHeight/3,_T("趋势显示"));
	
	pDC->SelectObject(&f2);
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(0,255,0));
	pDC->TextOut(85,8,_T("—— SpO2(%)"));
	pDC->SetTextColor(RGB(255,0,0));
	pDC->TextOut(185,8,_T("—— Resp(RR)"));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(285,8,_T("—— PR(BMP)"));

	pDC->SelectObject(pOldFont);
	pOldFont->DeleteObject();

	for ( unsigned int i = 0; i+x_topLeft < x_bottomRight-2; i ++ )
	{
		if ( (INVALID_VALUE == m_puiData[0][i]) || (INVALID_VALUE == m_puiData[0][i + 1]) )
		{
			continue;
		}

		int y1 = (m_uiHeight - (((m_puiData[0][i] - 2048) * m_iShowGain) + 2048) * m_uiHeight / 4096);
		int y2 = (m_uiHeight - (((m_puiData[0][i + 1] - 2048) * m_iShowGain) + 2048) * m_uiHeight / 4096);
		
		pDC->SelectObject(&cNewPen1);
		pDC->MoveTo(i+x_topLeft, y1);	//修改前x的坐标值可以改变其画图的步进宽度，原来为i
		pDC->LineTo(i+x_topLeft + 1, y2);
	}

	for ( unsigned int i = 0; i+x_topLeft < x_bottomRight-2; i ++ )
	{
		if ( (INVALID_VALUE == m_puiData[1][i]) || (INVALID_VALUE == m_puiData[1][i + 1]) )
		{
			continue;
		}
		int y3= (m_uiHeight - (((m_puiData[1][i] - 2048) * m_iShowGain) + 2048) * m_uiHeight / 4096);
		int y4 = (m_uiHeight - (((m_puiData[1][i + 1] - 2048) * m_iShowGain) + 2048) * m_uiHeight / 4096);

		pDC->SelectObject(&cNewPen2);
		pDC->MoveTo(i+x_topLeft, y3);
		pDC->LineTo(i +x_topLeft+ 1, y4);
	}

	for ( unsigned int i = 0; i+x_topLeft < x_bottomRight-2; i ++ )
	{
		if ( (INVALID_VALUE == m_puiData[2][i]) || (INVALID_VALUE == m_puiData[2][i + 1]) )
		{
			continue;
		}

		int y5= (m_uiHeight - (((m_puiData[2][i] - 2048) * m_iShowGain) + 2048) * m_uiHeight / 4096);
		int y6 = (m_uiHeight - (((m_puiData[2][i + 1] - 2048) * m_iShowGain) + 2048) * m_uiHeight / 4096);

		pDC->SelectObject(&cNewPen3);
		pDC->MoveTo(i+x_topLeft, y5);
		pDC->LineTo(i+x_topLeft + 1, y6);
	}

	pDC->SelectObject(pcOldPen);
	pcOldPen->DeleteObject();
	DeleteObject(cNewPen1);
	DeleteObject(cNewPen2);
	DeleteObject(cNewPen3);
}

void CStaticIBPWave::RcvOneData(unsigned int SpO2Data, unsigned int RespData, unsigned int PRData)
{
	if (SpO2Data == INVALID_VALUE)
	{
		m_puiData[0][m_uiCurrentPoint] = INVALID_VALUE;//加一个数是为了基线
	}
	else
		m_puiData[0][m_uiCurrentPoint] = SpO2Data*35.2 +300;//加一个数是为了基线

	if (RespData == INVALID_VALUE)
	{
		m_puiData[1][m_uiCurrentPoint] = INVALID_VALUE;
	}
	else
	m_puiData[1][m_uiCurrentPoint] = RespData*17.6 + 300;

	if (PRData == INVALID_VALUE)
	{
		m_puiData[2][m_uiCurrentPoint] = INVALID_VALUE;
	}
	else
		m_puiData[2][m_uiCurrentPoint] = PRData*15.7 + 300;

	m_uiCurrentPoint ++;

	for ( int i = 0; i < 5; i ++ ) 
	{
		unsigned int uiTemp = m_uiCurrentPoint + i;
		if ( uiTemp >= x_bottomRight - x_bottomLeft )
			uiTemp = uiTemp - (x_bottomRight-x_bottomLeft);

		m_puiData[0][uiTemp] = INVALID_VALUE;
		m_puiData[1][uiTemp] = INVALID_VALUE;
		m_puiData[2][uiTemp] = INVALID_VALUE;
	}

	if ( m_uiCurrentPoint % 2 == 0 ) 
	{
		CRect cRect(m_uiCurrentPoint - 3+x_bottomLeft, 2, m_uiCurrentPoint +2+x_bottomLeft,m_uiHeight-2);
		InvalidateRect(cRect, false);
	}

	if ( m_uiCurrentPoint >= x_bottomRight - x_bottomLeft)
		m_uiCurrentPoint = 0;
}

void CStaticIBPWave::DrawGrid(CPaintDC* pDC)
{
	UINT j,k;
	UINT x,y;
	CPen pen(PS_SOLID,1,RGB(100,0,100)),*poldpen;
	CPen penGrid(PS_SOLID,2,RGB(150,150,150)),*poldpenG;

	int y_gap = (y_bottomRight - y_topRight)/40,
		x_gap = y_gap*(x_topRight - x_topLeft)/(x_topRight - x_topLeft);

	poldpen=pDC->SelectObject (&pen);

	//vert
	j=0;
	while (true)
	{
		x = int(j*x_gap+x_topLeft);
		if(x>x_bottomRight)
			break;

		poldpenG=poldpen=pDC->SelectObject (&penGrid);
		k=0;
		while(true)
		{
			y = UINT(k*y_gap+y_topLeft);
			if(y>y_bottomRight)
				break;
			pDC->SetPixel(x,y,RGB(150,150,150));

			k++;
		}
		pDC->SelectObject (poldpenG);
		j++;
	}	

	//horize
	j=0;
	while(true)
	{
		y = int(j*y_gap+y_topLeft);
		if(y>y_bottomRight)
			break;
		if(j%5==0)
		{
			pDC->MoveTo (x_topLeft,y);
			pDC->LineTo (x_bottomRight,y);
		}
		j++;		
	}

	//画作图区域边框
	poldpen=pDC->SelectObject (&penGrid);

	pDC->MoveTo(x_topLeft, y_topLeft);
	pDC->LineTo(x_topRight, y_topRight);
	pDC->LineTo(x_bottomRight, y_bottomRight);
	pDC->LineTo(x_bottomLeft, y_bottomRight);
	pDC->LineTo(x_topLeft, y_topLeft);

	pDC->SelectObject (poldpen);

	//释放画笔资源
	pen.DeleteObject();
	penGrid.DeleteObject();	
}

void CStaticIBPWave::RefreshWin(void)
{
	ResetData();
	Invalidate();
}

void CStaticIBPWave::ResetData(void)
{
	for ( int i = 0; i < MAX_COUNT; i ++ ) 
	{	
		m_puiData[0][i] = INVALID_VALUE;
		m_puiData[1][i] = INVALID_VALUE;
		m_puiData[2][i] = INVALID_VALUE;
	}
	m_uiCurrentPoint = 0;
	m_uiRefreshFreq  = 0;

}

void CStaticIBPWave::SetScale(CPaintDC* pDC)
{
	CPen NewPen(PS_SOLID, 2, RGB(220,220, 220));
	CPen NewPen1(PS_SOLID, 1, RGB(220,220, 220));
	CPen * pcOldPen = pDC->SelectObject(&NewPen);
	
	char tlength = 0;
	pDC->MoveTo(x_topLeft-tlength,y_topLeft);
	pDC->LineTo(x_topLeft-tlength,y_bottomLeft);
	
	//y
	CString str;
	UINT x1,x2,x3,y;
	double UnitScale1,UnitScale2;
	UnitScale1 = float(y_bottomLeft-y_topLeft)/8.0;
	UnitScale2 = float(y_bottomLeft-y_topLeft)/40.0;

	x1=x_topLeft-75;
	x2=x_topLeft-50;
	x3=x_topLeft-25;

	CFont f1,*pOldFont=NULL;
	f1.CreatePointFont(90, _T("Times New Roman"), pDC);  
	pOldFont = pDC->SelectObject(&f1);
	pDC->SetBkMode(TRANSPARENT);

	pDC->SelectObject(&NewPen);
	for(int i = 0; i <= 8; i ++)
	{
		pDC ->MoveTo(x_topLeft-tlength, y_bottomLeft - i*UnitScale1);//(y_bottomLeft-y_topLeft)/8.0);
		pDC ->LineTo(x_topLeft-tlength+12, y_bottomLeft - i*UnitScale1);//(y_bottomLeft-y_topLeft)/8.0);
		
		y = y_bottomLeft - i*(y_bottomLeft-y_topLeft)/8.0-8; 

		str.Format(_T("%d"),i*5+60);
		pDC->SetTextColor(RGB(0,255,0));
		pDC->TextOut(x1,y,str);

		str.Format(_T("%d"),i*25);
		pDC->SetTextColor(RGB(255,0,0));
		pDC->TextOut(x2,y,str);

		str.Format(_T("%d"),i*25+25);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->TextOut(x3,y,str);
	}
	pDC->SelectObject(&NewPen1);
	for(int i = 0; i <= 40; i ++)
	{
		pDC ->MoveTo(x_topLeft-tlength, y_bottomLeft - i*UnitScale2);//(y_bottomLeft-y_topLeft)/40.0);
		pDC ->LineTo(x_topLeft-tlength+7, y_bottomLeft - i*UnitScale2);//(y_bottomLeft-y_topLeft)/40.0);
	}

	//X
	pDC->MoveTo(x_bottomLeft,y_bottomLeft);
	pDC->LineTo(x_bottomRight,y_bottomRight);
	int x=0;
	double XScale = (x_bottomRight-x_bottomLeft)/16.0;
	double XScale2 = (x_bottomRight-x_bottomLeft)/16.0/5.0;
	pDC->SelectObject(&NewPen);
	for(int i = 0; x<x_bottomRight; i ++)
	{
		x = XScale*i+x_bottomLeft;
		pDC ->MoveTo(x, y_bottomLeft);
		pDC ->LineTo(x, y_bottomLeft-9);
	}
	
	pDC ->MoveTo(m_uiWidth-XScale-70, y_topRight-15);
	pDC ->LineTo(m_uiWidth-XScale-70, y_topRight-10);

	pDC ->MoveTo(m_uiWidth-XScale-70, y_topRight-10);
	pDC ->LineTo(m_uiWidth-70, y_topRight-10);

	pDC ->MoveTo(m_uiWidth-70, y_topRight-15);
	pDC ->LineTo(m_uiWidth-70, y_topRight-10);
	pDC->TextOut(m_uiWidth-60,y_topRight-20,_T("1 Min"));

	x=0;
	pDC->SelectObject(&NewPen1);
	for(int i = 0; x<x_bottomRight; i ++)
	{
		x = XScale2*i+x_bottomLeft;
		pDC ->MoveTo(x, y_bottomLeft);
		pDC ->LineTo(x, y_bottomLeft-5);
	}
	
	pDC->SelectObject(pcOldPen);
	pcOldPen->DeleteObject();
	pDC->SelectObject(pOldFont);
	pOldFont->DeleteObject();
}
