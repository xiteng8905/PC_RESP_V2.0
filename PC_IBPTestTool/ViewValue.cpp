// ViewValue.cpp : 实现文件
//

#include "stdafx.h"
#include "ViewValue.h"


// CViewValue

IMPLEMENT_DYNAMIC(CViewValue, CStatic)

CViewValue::CViewValue()
{
	m_uiHeight=400;
	m_uiWidth=210;
	m_uiPR = INVALID_VALUE;
	m_uiResp = INVALID_VALUE;
	m_uiSpo2 = INVALID_VALUE;
}

CViewValue::~CViewValue()
{
}


BEGIN_MESSAGE_MAP(CViewValue, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CViewValue 消息处理程序



void CViewValue::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
//////////////////////////////////////////////////////////////////////////
	CString strSpO2,strPR,strRESP;

	if(m_uiSpo2 == INVALID_VALUE)
	{
		strSpO2.Format(_T("---"));
	}else strSpO2.Format(_T("%d"), m_uiSpo2);

	if(m_uiPR == INVALID_VALUE)
	{
		strPR.Format(_T("---"));
	}else strPR.Format(_T("%d"), m_uiPR);

	if(m_uiResp == INVALID_VALUE)
	{
		strRESP.Format(_T("---"));
	}else strRESP.Format(_T("%.2f"), m_uiResp/1000.0);

	CFont tFont;
	tFont.CreateFont(
		100,			//height
		0,			//average character width
		0,			//angle of escapement
		0,			//base-line orientation angle
		FW_BOLD,	//font weight
		1,			//italic attribute option
		0,			//underline attribute option
		0,			//strikeout attribute option
		DEFAULT_CHARSET,	//character set identifier
		OUT_DEFAULT_PRECIS,	//output precision
		CLIP_DEFAULT_PRECIS,//clipping precision
		DEFAULT_QUALITY,	//output quality
		DEFAULT_PITCH,		//pitch and family
		_T("Times New Roman")			//typeface name
		);

	CFont * pcOldFont = dc.SelectObject(&tFont);
	dc.SetTextColor(RGB(220, 80, 80));
	CSize tSize = dc.GetTextExtent(strSpO2);

	int iLeft = (m_uiWidth - tSize.cx) / 2;
	int iTop = (m_uiHeight  - tSize.cy) / 6-30;
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW(iLeft, iTop, strSpO2);

	dc.SetTextColor(RGB(128, 0, 128));
	tSize = dc.GetTextExtent(strPR);

	iLeft = (m_uiWidth - tSize.cx) / 2;
	iTop = (m_uiHeight*3 - tSize.cy) / 6-35;
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW(iLeft, iTop, strPR);

	dc.SetTextColor(RGB(150, 50, 150));
	tSize = dc.GetTextExtent(strRESP);

	iLeft = (m_uiWidth - tSize.cx) / 2;
	iTop = (m_uiHeight*5 - tSize.cy) / 6-30;
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW(iLeft, iTop, strRESP);

	dc.SelectObject(pcOldFont);
	ReleaseDC(&dc);

}

void CViewValue::SetSpO2Value(unsigned int nSpO2Value)
{
	m_uiSpo2 = nSpO2Value;

	CRect cRect(0, 0, m_uiWidth,m_uiHeight/3);
	InvalidateRect(cRect, false);
}

void CViewValue::SetPRValue(unsigned int nPRValue)
{
	m_uiPR = nPRValue;

	CRect cRect(0, m_uiHeight/3, m_uiWidth,m_uiHeight*2/3);
	InvalidateRect(cRect, false);
}

void CViewValue::SetRespValue(unsigned int nRespValue)
{
	m_uiResp = nRespValue;

	CRect cRect(0, m_uiHeight*2/3, m_uiWidth,m_uiHeight);
	InvalidateRect(cRect, false);
}

void CViewValue::SetRegion(unsigned int uiWidth, unsigned int uiHeight)
{
	m_uiWidth  = uiWidth;
	m_uiHeight = uiHeight;
}
