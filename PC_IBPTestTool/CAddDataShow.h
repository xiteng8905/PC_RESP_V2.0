#pragma once
#include <afxwin.h>
class CAddDataShow :
    public CStatic
{
public:
	CAddDataShow();
	virtual ~CAddDataShow();
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    void SetData();
public:
	unsigned int State;
	unsigned int FreqSPO2;
	unsigned int TimeSPO2;
	unsigned int IR_PAG;
	unsigned int RED_PGA;
	unsigned int LED_IR_MA;
	unsigned int LED_RED_MA;

	unsigned int Sub_State;
	unsigned int AmbDac_Code;
	unsigned int Current_Ln2;
	unsigned int Avg_P;
	unsigned int Mconfidence;
	unsigned int Freqcoef;

	int Data_Top, Data_Left, Data_SubTop;
	int Data_Height, Data_Weight, Data_SubHeight;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

