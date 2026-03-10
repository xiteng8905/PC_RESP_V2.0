#pragma once


// SetValueView 对话框

class SetValueView : public CDialog
{
	DECLARE_DYNAMIC(SetValueView)

public:
	SetValueView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SetValueView();

// 对话框数据
	enum { IDD = IDD_PC_IBPTESTTOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void SetRegion(unsigned int uiWidth, unsigned int uiHeight);
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	void SetViewData(float Viewdata);
	CString m_ViewText;
};
