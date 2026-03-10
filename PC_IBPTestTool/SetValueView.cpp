// SetValueView.cpp : 实现文件
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "SetValueView.h"


// SetValueView 对话框

IMPLEMENT_DYNAMIC(SetValueView, CDialog)

SetValueView::SetValueView(CWnd* pParent /*=NULL*/)
	: CDialog(SetValueView::IDD, pParent)
{
	m_ViewText = TEXT("---.-");
}

SetValueView::~SetValueView()
{
}

void SetValueView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SetValueView, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// SetValueView 消息处理程序

void SetValueView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
//	CRect tRect(0, 0, m_uiWidth, m_uiHeight);
	CFont tFont;

	tFont.CreateFont(
		60,			//height
		0,			//average character width
		0,			//angle of escapement
		0,			//base-line orientation angle
		FW_BOLD,	//font weight
		0,			//italic attribute option
		0,			//underline attribute option
		0,			//strikeout attribute option
		DEFAULT_CHARSET,	//character set identifier
		OUT_DEFAULT_PRECIS,	//output precision
		CLIP_DEFAULT_PRECIS,//clipping precision
		DEFAULT_QUALITY,	//output quality
		DEFAULT_PITCH,		//pitch and family
		_T("Times New Roman")			//typeface name宋体
		);

	CFont * pcOldFont = dc.SelectObject(&tFont);
	dc.SetTextColor(RGB(255,50, 255));

	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW(15, 5, m_ViewText);
}

void SetValueView::SetRegion(unsigned int uiWidth, unsigned int uiHeight)
{
}

void SetValueView::SetViewData(float ViewData)
{
	m_ViewText.Format(TEXT("%3.1f"),ViewData);
	Invalidate();
}
