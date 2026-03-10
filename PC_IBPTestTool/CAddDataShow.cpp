#include "stdafx.h"
#include "CAddDataShow.h"
//#include "resource.h"

CAddDataShow::CAddDataShow()
{
	FreqSPO2 = 0;
	TimeSPO2 = 0;
	IR_PAG = 0;
	RED_PGA = 0;
	LED_IR_MA = 0;
	LED_RED_MA = 0;
	State = 0;
	Mconfidence = 0;
	Freqcoef = 0;
	Sub_State = 0;
	AmbDac_Code = 0;
	Current_Ln2 = 0;
	Avg_P = 0;

	Data_Top = 60; Data_Left = 20; Data_Height = 42; 
	Data_SubTop = 20; Data_SubHeight = 38;
}

CAddDataShow::~CAddDataShow()
{
}

BEGIN_MESSAGE_MAP(CAddDataShow, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CAddDataShow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()

	//CRect rect;
	//GetClientRect(&rect);
	//// 使用系统背景色
	//dc.FillSolidRect(&rect, GetSysColor(COLOR_WINDOW));


	CFont Font_Data, Font_Data2;
	Font_Data.CreateFont(25, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("楷体"));//Data

	CPen cNewPen;  //CPen画笔是绘图的基本工具

	cNewPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//

	CPen* pcOldPen = dc.SelectObject(&cNewPen);
	CFont* pcOldFont = dc.SelectObject(&Font_Data);

	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkMode(TRANSPARENT);//

	CString tempResult;
	
    tempResult.Format(_T("FreqSPO2:   %d"), FreqSPO2);
    dc.TextOutW(Data_Left, Data_Top + Data_Height * 0, tempResult);

	tempResult.Format(_T("TimeSPO2:   %d"), TimeSPO2);
	dc.TextOutW(Data_Left, Data_Top + Data_Height * 1, tempResult);

	tempResult.Format(_T("mConfidence:%d"), Mconfidence);
	dc.TextOutW(Data_Left, Data_Top + Data_Height * 2, tempResult);

	tempResult.Format(_T("Freqcoef:   %d"), Freqcoef);
	dc.TextOutW(Data_Left, Data_Top + Data_Height * 3, tempResult);

	Font_Data2.CreateFont(23, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("楷体"));//Data

	CFont* pcOldFont2 = dc.SelectObject(&Font_Data2);
	tempResult.Format(_T("IR_PGA:     %d"), IR_PAG);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 0, tempResult);

	tempResult.Format(_T("RED_PGA:    %d"), RED_PGA);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 1, tempResult);

	tempResult.Format(_T("LED_IR_MA:  %d"), LED_IR_MA);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 2, tempResult);

	tempResult.Format(_T("LED_RED_MA: %d"), LED_RED_MA);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 3, tempResult);

	tempResult.Format(_T("State:      %d"), State);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 4, tempResult);

	tempResult.Format(_T("Sub_State:  %d"), Sub_State);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 5, tempResult);
	
	tempResult.Format(_T("AmbDac_Code:%d"), AmbDac_Code);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 6, tempResult);

	tempResult.Format(_T("Current_Ln2:%d"), Current_Ln2);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 7, tempResult);

	tempResult.Format(_T("Avg_P:      %d"), Avg_P);
	dc.TextOutW(Data_Left, Data_SubTop + Data_Top + Data_Height * 4 + Data_SubHeight * 8, tempResult);

	UpdateData();
	ReleaseDC(&dc);
}


void CAddDataShow::SetData()
{
	// TODO: 在此处添加实现代码.
}

BOOL CAddDataShow::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*m_SleepMainBk.LoadBitmap(IDB_SLEEPIMAGE_ADD);
	BITMAP bm;
	m_SleepMainBk.GetObject(sizeof(BITMAP), &bm);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMem.SelectObject(&m_SleepMainBk);

	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
		&dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
	dcMem.DeleteDC();*/

	return TRUE;

//	return TRUE;
	//return CStatic::OnEraseBkgnd(pDC);
}
