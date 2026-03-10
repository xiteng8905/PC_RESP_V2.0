/************************************************************************ 
* 程序名：    精仿QQ主界面 
* 制作人：    李克平, 2011年04月11日
* 版本号：    1.0 
************************************************************************/ 
// SkinStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SkinStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinStatic

CSkinStatic::CSkinStatic()
{
	m_nX=0;
	m_nY=0;
	m_strText="";
	m_pFont = NULL;
	//m_pFont.CreateFont(
	//	15,                        // nHeight
	//	0,                         // nWidth
	//	0,                         // nEscapement
	//	0,                         // nOrientation
	//	FW_BOLD,                 // nWeight
	//	FALSE,                     // bItalic
	//	FALSE,                     // bUnderline
	//	0,                         // cStrikeOut
	//	ANSI_CHARSET,              // nCharSet
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	//	DEFAULT_QUALITY,           // nQuality
	//	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	//	_T("Arial"));                 // lpszFacename
}

CSkinStatic::~CSkinStatic()
{
}


BEGIN_MESSAGE_MAP(CSkinStatic, CStatic)
	//{{AFX_MSG_MAP(CSkinStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinStatic message handlers
void CSkinStatic::LoadBitmap(LPCTSTR szImagePath)
{
	m_bmpStatic.LoadImage(szImagePath); 
}

void CSkinStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);
	if (m_bmpStatic.m_hObject !=0)
		m_bmpStatic.ExtendDraw(&dc,rcClient,m_nX,m_nY); 

	CRect rc=rcClient;
	rc.left =m_nTextStart;
	DrawText(&dc,rc,m_strText);
}

BOOL CSkinStatic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	GetParent()->SendMessage(WM_COMMAND,wParam,lParam); 	
	return CStatic::OnCommand(wParam, lParam);
}

void CSkinStatic::SetText(CString strText, int nStart,COLORREF cr)
{
	m_strText=strText;
	m_nTextStart=nStart;
	m_crText=cr;
}


BOOL CSkinStatic::DrawText(CDC *pDC,CRect rc ,CString strText)
{
	CRect r;
	CString str;
	CRect rcButton;
	if (strText.GetLength() )
	{
		if(m_pFont == NULL)
			m_pFont = GetParent()->GetFont();

		pDC->SelectObject(m_pFont);
		pDC->SetTextColor(m_crText);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText( strText, rc, DT_SINGLELINE | DT_VCENTER );
	}

	return TRUE;
}

void CSkinStatic::Redraw(CDC *pDC)
{
	CRect rc = GetRectInParent();
	if (m_bmpStatic.m_hObject !=0)
		m_bmpStatic.ExtendDraw(pDC,rc,m_nX,m_nY); 
	CRect rcText = rc;
	rcText.left += m_nTextStart;
	DrawText(pDC,rcText,m_strText);
}

CRect CSkinStatic::GetRectInParent()
{
	CRect rcWindowParent;
	GetParent()->GetWindowRect(rcWindowParent);//client
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	CRect rect;
	rect.left = rcWindow.left-rcWindowParent.left;
	rect.top = rcWindow.top-rcWindowParent.top;
	rect.right = rcWindow.right-rcWindowParent.left;
	rect.bottom = rcWindow.bottom-rcWindowParent.top;

	return rect;
}