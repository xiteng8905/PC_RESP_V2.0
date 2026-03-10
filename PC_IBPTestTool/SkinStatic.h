/************************************************************************ 
* 程序名：    精仿QQ主界面 
* 制作人：    李克平, 2011年04月11日
* 版本号：    1.0 
************************************************************************/ 
#if !defined(AFX_SKINSTATIC_H__8008CAA3_1EE3_4F71_A6B7_976421CC0915__INCLUDED_)
#define AFX_SKINSTATIC_H__8008CAA3_1EE3_4F71_A6B7_976421CC0915__INCLUDED_

#include "EnBitmap.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinStatic window
#include "EnBitmap.h"
class CSkinStatic : public CStatic
{
// Construction
public:
	CSkinStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinStatic)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetText(CString strText,int nStart = 0,COLORREF cr = RGB(0,0,0));
	void SetExtendPoint(int nX,int nY){m_nX=nX;m_nY=nY;}
	void SetFont(CFont *pFont){m_pFont = pFont;}
	BOOL DrawText(CDC *pDC,CRect rc ,CString strText);
	void Redraw(CDC *pDC);
	CEnBitmap m_bmpStatic;
	CString m_strText;
	CFont *m_pFont;
	int m_nTextStart;
	COLORREF m_crText;
	virtual ~CSkinStatic();
	void LoadBitmap(LPCTSTR szImagePath);
	int	 Width(){return m_bmpStatic.GetWidth();}
	int	 Height(){return m_bmpStatic.GetHeight();}
	CRect GetRectInParent();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG
	int m_nX,m_nY;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSTATIC_H__8008CAA3_1EE3_4F71_A6B7_976421CC0915__INCLUDED_)
