// AnalysisDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnalysisDataDlg.h"


// CAnalysisDataDlg dialog

IMPLEMENT_DYNAMIC(CAnalysisDataDlg, CDialog)

CAnalysisDataDlg::CAnalysisDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalysisDataDlg::IDD, pParent)
{

}

CAnalysisDataDlg::~CAnalysisDataDlg()
{
}

void CAnalysisDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SPO2WAVE, m_ReDataSpO2Wave);
	DDX_Control(pDX, IDC_STATIC_PULSEWAVE, m_ReDataPlsWave);
	DDX_Control(pDX, IDC_STATIC_RESPWAVE, m_ReDataRespWave);
	DDX_Control(pDX, IDC_STATIC_RESPRATE, m_ReDataRRWave);
	DDX_Control(pDX, IDC_STATIC_PR, m_ReDataPRWave);
	DDX_Control(pDX, IDC_MYSCROLLBAR, m_ScrollBarCtrl);
	DDX_Control(pDX, IDC_COMBO_SPO2, m_ComboSpO2);
	DDX_Control(pDX, IDC_COMBO_PR, m_ComboResp);
	DDX_Control(pDX, IDC_COMBO_RR, m_ComboPR);
	DDX_Control(pDX, IDC_LIST_MEASSAGE, m_CListCtrlMessage);
}


BEGIN_MESSAGE_MAP(CAnalysisDataDlg, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CAnalysisDataDlg::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, &CAnalysisDataDlg::OnBnClickedButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_PULSEP, &CAnalysisDataDlg::OnBnClickedButtonPulsep)
	ON_BN_CLICKED(IDC_BUTTON_PULSEM, &CAnalysisDataDlg::OnBnClickedButtonPulsem)
	ON_BN_CLICKED(IDC_BUTTON_SPO2P, &CAnalysisDataDlg::OnBnClickedButtonSpo2p)
	ON_BN_CLICKED(IDC_BUTTON_SPO2M, &CAnalysisDataDlg::OnBnClickedButtonSpo2m)
	ON_BN_CLICKED(IDC_BUTTON_RESPWAVEP, &CAnalysisDataDlg::OnBnClickedButtonRespwavep)
	ON_BN_CLICKED(IDC_BUTTON_RESPWAVEM, &CAnalysisDataDlg::OnBnClickedButtonRespwavem)
	ON_BN_CLICKED(IDC_BUTTON_RRP, &CAnalysisDataDlg::OnBnClickedButtonRrp)
	ON_BN_CLICKED(IDC_BUTTON_RRM, &CAnalysisDataDlg::OnBnClickedButtonRrm)
	ON_BN_CLICKED(IDC_BUTTON_PRP, &CAnalysisDataDlg::OnBnClickedButtonPrp)
	ON_BN_CLICKED(IDC_BUTTON_PRM, &CAnalysisDataDlg::OnBnClickedButtonPrm)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CAnalysisDataDlg::OnBnClickedButtonMin)
	ON_BN_CLICKED(IDC_BUTTON_VIEWRESTORE, &CAnalysisDataDlg::OnBnClickedButtonViewrestore)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAnalysisDataDlg message handlers
BOOL CAnalysisDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetLayout();
	SetWindowText(TEXT("睡眠监测数据回放分析平台"));
	
	SCROLLINFO si;
	m_ScrollBarCtrl.GetScrollInfo(&si);
	si.nMax = 100;
	si.nMin = 1;
	si.nPos = 10;
	si.cbSize = sizeof(SCROLLINFO);
	si.nMin = 1;
	si.nMax = 100;
	si.nPage = -1;       //我把它赋值为 -1 ，开始没有那么多内容不显示 滚动条SetScrollInfo(SB_VERT,&si);
	m_ScrollBarCtrl.SetScrollInfo(&si);
					
	m_ComboSpO2.AddString(_T("95"));
	m_ComboSpO2.AddString(_T("90"));
	m_ComboSpO2.AddString(_T("85"));
	m_ComboSpO2.AddString(_T("80"));
	m_ComboSpO2.AddString(_T("75"));
	m_ComboSpO2.SetCurSel(4);

	m_ComboPR.AddString(_T("100"));
	m_ComboPR.AddString(_T("110"));
	m_ComboPR.AddString(_T("120"));
	m_ComboPR.AddString(_T("130"));
	m_ComboPR.AddString(_T("140"));
	m_ComboPR.AddString(_T("150"));
	m_ComboPR.AddString(_T("160"));
	m_ComboPR.SetCurSel(0);

	m_ComboResp.AddString(_T("30"));
	m_ComboResp.AddString(_T("40"));
	m_ComboResp.AddString(_T("50"));
	m_ComboResp.AddString(_T("60"));
	m_ComboResp.AddString(_T("80"));
	m_ComboResp.AddString(_T("120"));
	m_ComboResp.AddString(_T("140"));
	m_ComboResp.SetCurSel(2);

	m_ComboResp.ShowWindow(SW_HIDE);
	CFont *tfont;
	tfont = new CFont;
	tfont->CreateFont(5,0,0,0,FW_THIN,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("System"));
	GetDlgItem(IDC_EDIT_FILEPATH)->SetFont(tfont);
	GetDlgItem(IDC_BUTTON_VIEWRESTORE)->SetFont(tfont);
	delete tfont;
	
	//标尺参数初始化
	SpO2Scale.m_coef[0] = 0.254;
	SpO2Scale.m_ScaleMax[0] = 100;
	SpO2Scale.m_ScaleMin[0] = 60;
	SpO2Scale.m_ScaleNum[0] = 8;
	SpO2Scale.m_coef[1] = 0.25915;
	SpO2Scale.m_ScaleMax[1] = 100;
	SpO2Scale.m_ScaleMin[1] = 70;
	SpO2Scale.m_ScaleNum[1] = 6;
	SpO2Scale.m_coef[2] = 0.25915;
	SpO2Scale.m_ScaleMax[2] = 100;
	SpO2Scale.m_ScaleMin[2] = 80;
	SpO2Scale.m_ScaleNum[2] = 8;

	//RRScale.m_coef[0] = 1.264;
	//RRScale.m_ScaleMax[0] = 200;
	//RRScale.m_ScaleMin[0] = 0;
	//RRScale.m_ScaleNum[0] = 8;
	//RRScale.m_coef[1] = 1.106;
	//RRScale.m_ScaleMax[1] = 150;
	//RRScale.m_ScaleMin[1] = 0;
	//RRScale.m_ScaleNum[1] = 6;
	//RRScale.m_coef[2] = 0.638;
	//RRScale.m_ScaleMax[2] = 100;
	//RRScale.m_ScaleMin[2] = 0;
	//RRScale.m_ScaleNum[2] = 5;
	//RRScale.m_coef[3] = 0.3224;
	//RRScale.m_ScaleMax[3] = 50;
	//RRScale.m_ScaleMin[3] = 0;
	//RRScale.m_ScaleNum[3] = 5;

	PRScale.m_coef[0] = 1.27;
	PRScale.m_ScaleMax[0] = 225;
	PRScale.m_ScaleMin[0] = 25;
	PRScale.m_ScaleNum[0] = 8;
	PRScale.m_coef[1] = 1.112;
	PRScale.m_ScaleMax[1] = 200;
	PRScale.m_ScaleMin[1] = 25;
	PRScale.m_ScaleNum[1] = 7;
	PRScale.m_coef[2] = 0.794;
	PRScale.m_ScaleMax[2] = 150;
	PRScale.m_ScaleMin[2] = 25;
	PRScale.m_ScaleNum[2] = 5;
	PRScale.m_coef[3] = 0.476;
	PRScale.m_ScaleMax[3] = 100;
	PRScale.m_ScaleMin[3] = 25;
	PRScale.m_ScaleNum[3] = 5;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAnalysisDataDlg::SetLayout(void)
{
	CRect rtClient;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rtClient, 0);//屏幕大小(不含任务栏)
	m_nWidth = rtClient.right;
	m_nHeight = rtClient.bottom;
	MoveWindow(0, 0, m_nWidth, m_nHeight);
	
	CRgn m_rgn; 
	RECT rc; 
	GetClientRect(&rc); 
	m_rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,30,10); 
	SetWindowRgn(m_rgn,FALSE); 

	//波形布局
	int tWidth,tHeight;
	tWidth = m_nWidth*0.6;
	tHeight = (m_nHeight-30)/5;

	m_ReDataPlsWave.SetRegion(tWidth,tHeight);
	GetDlgItem(IDC_STATIC_PULSEWAVE)->MoveWindow(2, 1, tWidth, tHeight);
	GetDlgItem(IDC_BUTTON_PULSEP)->MoveWindow(tWidth+2, 2, 20, tHeight/2-2);
	GetDlgItem(IDC_BUTTON_PULSEM)->MoveWindow(tWidth+2, 1+tHeight/2+1, 20, tHeight/2-2);

	m_ReDataSpO2Wave.SetRegion(tWidth,tHeight);
	GetDlgItem(IDC_STATIC_SPO2WAVE)->MoveWindow(2, tHeight+3, tWidth, tHeight);
	GetDlgItem(IDC_BUTTON_SPO2P)->MoveWindow(tWidth+2, tHeight+4, 20, tHeight/2-2);
	GetDlgItem(IDC_BUTTON_SPO2M)->MoveWindow(tWidth+2, tHeight+3+tHeight/2+1, 20, tHeight/2-2);

	m_ReDataRespWave.SetRegion(tWidth,tHeight);
	GetDlgItem(IDC_STATIC_RESPWAVE)->MoveWindow(2, tHeight*2+5, tWidth, tHeight);
	GetDlgItem(IDC_BUTTON_RESPWAVEP)->MoveWindow(tWidth+2, tHeight*2+6, 20, tHeight/2-2);
	GetDlgItem(IDC_BUTTON_RESPWAVEM)->MoveWindow(tWidth+2, tHeight*2+5+tHeight/2+1, 20, tHeight/2-2);

	m_ReDataRRWave.SetRegion(tWidth,tHeight);
	GetDlgItem(IDC_STATIC_RESPRATE)->MoveWindow(2, tHeight*3+7, tWidth, tHeight);
	GetDlgItem(IDC_BUTTON_RRP)->MoveWindow(tWidth+2, tHeight*3+8, 20, tHeight/2-2);
	GetDlgItem(IDC_BUTTON_RRM)->MoveWindow(tWidth+2, tHeight*3+7+tHeight/2+1, 20, tHeight/2-2);

	m_ReDataPRWave.SetRegion(tWidth,tHeight);
	GetDlgItem(IDC_STATIC_PR)->MoveWindow(2, tHeight*4+9,tWidth, tHeight);
	GetDlgItem(IDC_BUTTON_PRP)->MoveWindow(tWidth+2, tHeight*4+10, 20, tHeight/2-3);
	GetDlgItem(IDC_BUTTON_PRM)->MoveWindow(tWidth+2, tHeight*4+9+tHeight/2+1, 20, tHeight/2-3);

	GetDlgItem(IDC_MYSCROLLBAR)->MoveWindow(2, m_nHeight-20, tWidth, 16);

	GetDlgItem(IDC_BUTTON_OPENFILE)->MoveWindow(m_nWidth-120, 5,35, 35);
	GetDlgItem(IDC_BUTTON_MIN)->MoveWindow(m_nWidth-80, 5,35, 35);
	GetDlgItem(IDCANCEL)->MoveWindow(m_nWidth-40, 5,35, 35);

	GetDlgItem(IDC_COMBO_SPO2)->MoveWindow(tWidth+(m_nWidth-tWidth)/16+(m_nWidth-tWidth)/32, 200,(m_nWidth-tWidth)/6, 20);
	GetDlgItem(IDC_COMBO_RR)->MoveWindow(tWidth+(m_nWidth-tWidth)/6+(m_nWidth-tWidth)/8+(m_nWidth-tWidth)/32, 200,(m_nWidth-tWidth)/6, 20);
	GetDlgItem(IDC_COMBO_PR)->MoveWindow(tWidth+(m_nWidth-tWidth)*2/6+(m_nWidth-tWidth)*3/16+(m_nWidth-tWidth)/32, 200,(m_nWidth-tWidth)/6, 20);
	
	GetDlgItem(IDC_BUTTON_SETUP)->MoveWindow(tWidth+(m_nWidth-tWidth)*3/6+(m_nWidth-tWidth)*1/4, 200,(m_nWidth-tWidth)/6, 35);

	GetDlgItem(IDC_STATIC_SETWORNING)->MoveWindow(tWidth+(m_nWidth-tWidth)/18, 150,m_nWidth-tWidth-40, 100);
	
	GetDlgItem(IDC_BUTTON_VIEWRESTORE)->MoveWindow(tWidth+2,m_nHeight-24,85,24);
	GetDlgItem(IDC_EDIT_FILEPATH)->MoveWindow(tWidth+90,m_nHeight-22,m_nWidth-tWidth-95,20);
	GetDlgItem(IDC_EDIT_FILEPATH)->SetWindowText(TEXT("文件地址："));
	CEdit *pEdit=(CEdit *)GetDlgItem(IDC_EDIT_FILEPATH);
	pEdit->SetSel(1, 5, false);

	GetDlgItem(IDC_LIST_MEASSAGE)->MoveWindow(tWidth+25,m_nHeight*3/5,m_nWidth-tWidth-30,m_nHeight*2/5-28);

	DWORD dwStyle = m_CListCtrlMessage.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）

	m_CListCtrlMessage.SetExtendedStyle(dwStyle); //设置扩展风格	
	m_CListCtrlMessage.InsertColumn(0, _T("  回放信息："), LVCFMT_LEFT, 1000);
	
	InsertMessageToList(_T("欢迎使用血氧监测数据回放软件！"));
	//////////////////////////////////////////////////////////////////////////
	SetWindowLong(this-> GetSafeHwnd(),GWL_EXSTYLE, 

	GetWindowLong(this-> GetSafeHwnd(),GWL_EXSTYLE)^0x80000); 
	HINSTANCE   hInst   =   LoadLibrary(_T( "User32.DLL "));   
	if(hInst)   
	{   
		typedef   BOOL   (WINAPI   *MYFUNC)(HWND,COLORREF,BYTE,DWORD);   
		MYFUNC   fun   =   NULL; 
		//取得SetLayeredWindowAttributes函数指针   
		fun=(MYFUNC)GetProcAddress(hInst,  "SetLayeredWindowAttributes"); 
		if(fun)fun(this-> GetSafeHwnd(),0,240,2);   
		FreeLibrary(hInst);   
	} 
	//////////////////////////////////////////////////////////////////////////
}

void CAnalysisDataDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO si;
	m_ScrollBarCtrl.GetScrollInfo(&si);
	switch(nSBCode)
	{
	case SB_LINERIGHT:   
		si.nPos++;   
		break;
	case SB_LINELEFT:   
		si.nPos--;   
		break;
	case SB_PAGERIGHT:   
		si.nPos += si.nPage;   
		break;
	case SB_PAGELEFT:   
		si.nPos += si.nPage;   
		break;
	case SB_THUMBTRACK:   
		si.nPos = nPos;   
		break;
	case SB_THUMBPOSITION:   
		si.nPos = nPos;   
		break;
	}
	m_ScrollBarCtrl.SetScrollInfo(&si);

	m_ReDataSpO2Wave.SetMapStartPoint(si.nPos);
	m_ReDataPlsWave.SetMapStartPoint(si.nPos);
	m_ReDataRespWave.SetMapStartPoint(si.nPos);
	m_ReDataRRWave.SetMapStartPoint(si.nPos);
	m_ReDataPRWave.SetMapStartPoint(si.nPos);

 	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAnalysisDataDlg::OnBnClickedButtonOpenfile()
{
	// TODO: Add your control notification handler code here
	DWORD dwVersion;
	int   structSize;
	CString strFileName;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		_T("数据文件(*.txt;*.log;*.dat)|*.txt;*.log;*.dat|所有文件(*.*)|*.*|"), this);

	//获取系统版本，以选择适当的打开对话框
	dwVersion = GetVersion();
	if (dwVersion < 0x80000000)
	{
		structSize = 88;
	}
	else
	{
		structSize = 76;
	}

	dlg.m_ofn.lStructSize = structSize; // 决定对话框是老式还是新式，88代表新文件对话框，76代表老对话框
	dlg.m_ofn.lpstrTitle = _T("打开数据文件");//弹出对话框的标题为“打开数据文件”

	if (IDOK == dlg.DoModal())
	{
		strFileName = dlg.GetPathName();
	}

	if (strFileName.IsEmpty())
	{
		return;
	}

	GetDlgItem(IDC_EDIT_FILEPATH)->SetWindowText(_T("文件路径：")+strFileName);//将选择的文件显示在“信息框”中
	InsertMessageToList(_T("文件路径为：")+strFileName);//将内容显示在“信息框中”,上一条语句好像没什么用

	AnalyseFile(strFileName);
	
	AnalyseResult();
	
	Invalidate();
}

void CAnalysisDataDlg::AnalyseFile(CString strFileName)
{
	CStdioFile file;
	int **pReadData;

	if (!file.Open(strFileName, CFile::modeRead | CFile::typeText))//打开文件只读，打开成功返回非0值，否则返回0；
	{
		AfxMessageBox(_T("文件打开失败!"));
		return;
	}

	m_bFileOpen = FALSE;
	m_nItemCount = 0;
	m_nDataCount = 0;
	m_checedIndex.RemoveAll();    //m_checedIndex存储被选中曲线的索引,RemoveAll=全部删除

	ULONGLONG fileLength = file.GetLength();
	UINT curPos = 0;
	float value = 0.0;
	CString strRead = _T("");//_T("")就是把引号内的字符串转换为宽字节的Unicode编码，和TEXT("")作用是一样的,
							 //用VC6开发的程序，默认都不是宽字节的，但用VS系列的开发工具，默认就是宽字节的
	UINT  rows = 0, cols = 0;
	UINT  index = 0;

	//分析数据，以便分配动态数组
	while (curPos < fileLength)
	{
		file.ReadString(strRead);//读取一行文本
		curPos += strRead.GetLength() + 2;

		if (strRead.IsEmpty())
		{
			continue;//break是结束整个循环体，continue是结束单次循环
		}

		index++;
		if (index == 2)  //计算列
		{
			strRead.Replace(_T("\t"), _T(" "));
			strRead.TrimLeft(_T(" "));//用于消除从左侧起所遇到的所有空格字符
			strRead.TrimRight(_T(" "));//用于消除从右侧起所遇到的所有空格字符
			while (-1 != strRead.Find(_T(" ")))
			{
				CString strTemp;
				UINT index = strRead.Find(_T(" "));//找到空格字符

				strTemp = strRead.Left(index);//读取空格字符左边的数据

				strRead = strRead.Right(strRead.GetLength() - strTemp.GetLength());
				strRead.TrimLeft(_T(" "));
				cols++;
			}

			if (!strRead.IsEmpty())
			{
				cols++;
			}
		}
		if (index > 2)
		{
			rows++;
		}
	}
	file.Close();

	//得出数据的行列数
	m_nItemCount = cols;
	m_nDataCount = rows;

	if (m_nDataCount <= 1)
	{
		m_nItemCount = 0;
		m_nDataCount = 0;
		return;
	}

	//生成二维数组存储数据
	pReadData = new INT*[rows];
	for (index = 0; index < rows; index++)
	{
		pReadData[index] = new INT[cols];//给二维数组每一行都初始化包含cols个数。
	}

	if (!file.Open(strFileName, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox(_T("文件打开失败!"));
		return;
	}

	m_strTitle = new CString[cols];

	curPos = 0;
	rows = 0; 
	cols = 0;
	index = 0;
	int i = 0, j = 0;
	fileLength = file.GetLength();

	while (curPos < fileLength)
	{
		file.ReadString(strRead);
		curPos += strRead.GetLength() + 2;

		strRead.Replace(_T("\t"), _T(" "));
		strRead.TrimLeft(_T(" "));
		strRead.TrimRight(_T(" "));

		if (strRead.IsEmpty())
		{
			continue;
		}

		index++;
		if (index == 1)  //获取曲线名称
		{
			i = 0;
			while (-1 != strRead.Find(_T(" ")))
			{
				CString strTemp;
				UINT index = strRead.Find(_T(" "));

				strTemp = strRead.Left(index);

				strRead = strRead.Right(strRead.GetLength() - strTemp.GetLength());
				strRead.TrimLeft(_T(" "));

				strTemp.TrimRight(_T(" "));
				m_strTitle[i++] = strTemp;
			}

			if (!strRead.IsEmpty())
			{
				m_strTitle[i] = strRead;
			}
		}

		if (index > 2)
		{
			//解析数据
			while (-1 != strRead.Find(_T(" ")))
			{
				CString strTemp;
				UINT index1 = strRead.Find(_T(" "));

				strTemp = strRead.Left(index1);

				strRead = strRead.Right(strRead.GetLength() - strTemp.GetLength());
				strRead.TrimLeft(_T(" "));

				value = _wtoi(strTemp);//获取值

				if (rows < m_nDataCount && cols < m_nItemCount)
				{
					pReadData[rows][cols++] = value;
				}
			}

			if (!strRead.IsEmpty())
			{
				value = _wtoi(strRead);

				if (rows < m_nDataCount && cols < m_nItemCount)
				{
					pReadData[rows][cols++] = value;
				}
			}
			rows++;
			cols = 0;
		}
	}
	file.Close();
	
	for (int t=0;t<5;t++)
	{
		m_pReadData[t] = new int[m_nDataCount];
	}
	
	for (cols = 0; cols < 5; cols++)//找到每列数的最大值和最小值
	{
		m_maxValue[cols] = pReadData[0][cols];
		m_minValue[cols] = pReadData[0][cols];
		
		
		m_maxValue2[cols] = pReadData[0][cols];

		for (rows = 0; rows < m_nDataCount; rows++)
		{
			if (m_maxValue[cols] < pReadData[rows][cols])
			{
				m_maxValue[cols] = pReadData[rows][cols];
			}

			if (m_minValue[cols] > pReadData[rows][cols])
			{
				m_minValue[cols] = pReadData[rows][cols];
			}
		}
	}

	for (UINT Count=0;Count<m_nDataCount;Count++)
	{
		//Pulse Wave
		if (m_pReadData[0][Count] != INVALID_VALUE)
		{
			m_pReadData[0][Count] = (pReadData[Count][0]-m_minValue[0]);
		}
		else
		{
			m_pReadData[0][Count] = INVALID_VALUE;
		}
		//SpO2
		if (m_pReadData[1][Count] != INVALID_VALUE)
		{
			m_pReadData[1][Count] =  pReadData[Count][1]-70;
		}
		else
		{
			m_pReadData[1][Count] = INVALID_VALUE;
		}
		//RespWave
		if (m_pReadData[2][Count] != INVALID_VALUE)
		{
			m_pReadData[2][Count] = pReadData[Count][2]-m_minValue[2];
		} 
		else
		{
			m_pReadData[2][Count] = INVALID_VALUE;
		}
		//Resp Rate
		if (m_pReadData[3][Count] != INVALID_VALUE)
		{
			m_pReadData[3][Count] =  pReadData[Count][3];
		} 
		else
		{
			m_pReadData[3][Count] = INVALID_VALUE;
		}
		//Pulse Rate
		if (m_pReadData[4][Count] != INVALID_VALUE)
		{
			m_pReadData[4][Count] =	pReadData[Count][4]-25;
		} 
		else
		{
			m_pReadData[4][Count] = INVALID_VALUE;
		}
	}
	delete pReadData;
	
	float time = m_nDataCount/62.5;
	float Sec = (m_nDataCount%3750)/62.5;
	UINT min = m_nDataCount/3750;

	CString str;
	str.Format(_T("数据持续时间为：%d Min %1.2f Sec （%1.2f s）"),min,Sec,time);
	InsertMessageToList(str);

	m_ReDataPlsWave.InputWaveData(m_pReadData[0],m_nDataCount);
	m_ReDataPlsWave.SetWaveTitle(_T("Pulse Wave"));
	m_ReDataPlsWave.SetViewCoef(0.73);

	m_ReDataSpO2Wave.InputWaveData(m_pReadData[1],m_nDataCount);
	m_ReDataSpO2Wave.SetWaveTitle(_T("SpO2"));
	m_ReDataSpO2Wave.SetViewCoef(SpO2Scale.m_coef[0]);

	m_ReDataRespWave.InputWaveData(m_pReadData[2],m_nDataCount);
	m_ReDataRespWave.SetWaveTitle(_T("Red Wave"));
	m_ReDataRespWave.SetViewCoef(0.73);

	m_ReDataRRWave.InputWaveData(m_pReadData[3],m_nDataCount);
	m_ReDataRRWave.SetWaveTitle(_T("IR Rate"));
	m_ReDataRRWave.SetViewCoef(0.73);

	m_ReDataPRWave.InputWaveData(m_pReadData[4],m_nDataCount);
	m_ReDataPRWave.SetWaveTitle(_T("Pulse Rate"));
	m_ReDataPRWave.SetViewCoef(PRScale.m_coef[0]);

	m_ReDataSpO2Wave.ScaleViewEnale(TRUE,70,100,6);
	//m_ReDataRRWave.ScaleViewEnale(TRUE,0,200,8);
	m_ReDataPRWave.ScaleViewEnale(TRUE,25,225,8);

	SCROLLINFO si;
	m_ScrollBarCtrl.GetScrollInfo(&si);
	si.cbSize = sizeof(SCROLLINFO);
	si.nMin = 1;
	si.nMax = m_nDataCount;
	si.nPage = si.nMax/10; 
	si.nPos = 0;
	m_ScrollBarCtrl.SetScrollInfo(&si);
	Invalidate();
}

void CAnalysisDataDlg::OnBnClickedButtonSetup()
{
	// TODO: Add your control notification handler code here
	UCHAR tempSpo2,tempResp,tempPR;
	UCHAR t;
	CString str;
	bool Flag = TRUE;

	tempSpo2 = m_ComboSpO2.GetCurSel();
	tempResp = m_ComboResp.GetCurSel();
	tempPR   = m_ComboPR.GetCurSel();
	
	m_ComboSpO2.GetWindowText(str);
	t=_wtoi(str);

	if (t>70&&t<=100)
	{
		m_SetLimit.m_SpO2Limit = t;
	}
	else
	{	
		Flag = FALSE;
		MessageBox(_T("SpO2报警线设置有误！"),_T("提示："),MB_OK|MB_ICONERROR);
	}

	m_ComboResp.GetWindowText(str);
	t=_wtoi(str);
	if (t>=0&&t<=200)
	{
		m_SetLimit.m_RespLimit = t;		
	} 
	else
	{
		Flag = FALSE;
		MessageBox(_T("Resp Rate报警线设置有误！"),_T("提示："),MB_OK|MB_ICONERROR);
	}

	m_ComboPR.GetWindowText(str);
	t=_wtoi(str);
	if (t>=25&&t<=225)
	{
		m_SetLimit.m_PRLimit = t;				
	} 
	else
	{
		Flag = FALSE;
		MessageBox(_T("Pulse Rate报警线设置有误！"),_T("提示："),MB_OK|MB_ICONERROR);
	}
	
	if (Flag == TRUE)
	{
		str.Format(_T("报警线设置为："));
		InsertMessageToList(str);
		str.Format(_T("   SpO2为低于%d，Pulse Rate 为高于%d"),m_SetLimit.m_SpO2Limit,m_SetLimit.m_PRLimit);
		InsertMessageToList(str);
	} 
	else
	{
		str.Format(_T("报警线设置有误！"));
		InsertMessageToList(str);
	}
}

void CAnalysisDataDlg::OnBnClickedButtonPulsep()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataPlsWave.m_ViewCoef;
	float t= f/1.05;
	if (t == 0)
	{
		t = f;
	}
	m_ReDataPlsWave.SetViewCoef(t);
}

void CAnalysisDataDlg::OnBnClickedButtonPulsem()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataPlsWave.m_ViewCoef*1.05;
	m_ReDataPlsWave.SetViewCoef(f);
}

void CAnalysisDataDlg::OnBnClickedButtonSpo2p()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataSpO2Wave.m_ViewCoef;
	float t= f/1.05;
	if (t == 0)
	{
		t = f;
	}
	m_ReDataSpO2Wave.SetViewCoef(t);
}

void CAnalysisDataDlg::OnBnClickedButtonSpo2m()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataSpO2Wave.m_ViewCoef*1.05;
	m_ReDataSpO2Wave.SetViewCoef(f);
}

void CAnalysisDataDlg::OnBnClickedButtonRespwavep()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataRespWave.m_ViewCoef;
	float t= f/1.05;
	if (t == 0)
	{
		t = f;
	}
	m_ReDataRespWave.SetViewCoef(t);
}

void CAnalysisDataDlg::OnBnClickedButtonRespwavem()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataRespWave.m_ViewCoef*1.05;
	m_ReDataRespWave.SetViewCoef(f);
}

void CAnalysisDataDlg::OnBnClickedButtonRrp()
{

		// TODO: Add your control notification handler code here
	float f= m_ReDataRRWave.m_ViewCoef;
	float t= f/1.05;
	if (t == 0)
	{
		t = f;
	}
	m_ReDataRRWave.SetViewCoef(t);
	//// TODO: Add your control notification handler code here
	//float f= m_ReDataRRWave.m_ViewCoef;

	//if (f == RRScale.m_coef[0])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[0]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[0],RRScale.m_ScaleMax[0],RRScale.m_ScaleNum[0]);
	//}
	//else if (f == RRScale.m_coef[1])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[0]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[0],RRScale.m_ScaleMax[0],RRScale.m_ScaleNum[0]);
	//} 
	//else if (f == RRScale.m_coef[2])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[1]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[1],RRScale.m_ScaleMax[1],RRScale.m_ScaleNum[1]);
	//}
	//else if (f == RRScale.m_coef[3])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[2]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[2],RRScale.m_ScaleMax[2],RRScale.m_ScaleNum[2]);
	//}
}

void CAnalysisDataDlg::OnBnClickedButtonRrm()
{
		float f= m_ReDataRRWave.m_ViewCoef*1.05;
	m_ReDataRRWave.SetViewCoef(f);
	//// TODO: Add your control notification handler code here
	//double f= m_ReDataRRWave.m_ViewCoef;

	//if (f == RRScale.m_coef[0])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[1]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[1],RRScale.m_ScaleMax[1],RRScale.m_ScaleNum[1]);
	//}
	//else if (f == RRScale.m_coef[1])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[2]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[2],RRScale.m_ScaleMax[2],RRScale.m_ScaleNum[2]);
	//} 
	//else if (f == RRScale.m_coef[2])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[3]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[3],RRScale.m_ScaleMax[3],RRScale.m_ScaleNum[3]);
	//}
	//else if (f == RRScale.m_coef[3])
	//{
	//	m_ReDataRRWave.SetViewCoef(RRScale.m_coef[3]);
	//	m_ReDataRRWave.ScaleViewEnale(TRUE,RRScale.m_ScaleMin[3],RRScale.m_ScaleMax[3],RRScale.m_ScaleNum[3]);
	//}
}

void CAnalysisDataDlg::OnBnClickedButtonPrm()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataPRWave.m_ViewCoef;
	if (f == PRScale.m_coef[0])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[0]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[0],PRScale.m_ScaleMax[0],PRScale.m_ScaleNum[0]);
	}
	else if (f == PRScale.m_coef[1])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[0]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[0],PRScale.m_ScaleMax[0],PRScale.m_ScaleNum[0]);
	} 
	else if (f == PRScale.m_coef[2])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[1]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[1],PRScale.m_ScaleMax[1],PRScale.m_ScaleNum[1]);
	}
	else if (f == PRScale.m_coef[3])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[2]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[2],PRScale.m_ScaleMax[2],PRScale.m_ScaleNum[2]);
	}
}

void CAnalysisDataDlg::OnBnClickedButtonPrp()
{
	// TODO: Add your control notification handler code here
	float f= m_ReDataPRWave.m_ViewCoef;

	if (f == PRScale.m_coef[0])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[1]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[1],PRScale.m_ScaleMax[1],PRScale.m_ScaleNum[1]);
	}
	else if (f == PRScale.m_coef[1])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[2]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[2],PRScale.m_ScaleMax[2],PRScale.m_ScaleNum[2]);
	} 
	else if (f == PRScale.m_coef[2])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[3]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[3],PRScale.m_ScaleMax[3],PRScale.m_ScaleNum[3]);
	}
	else if (f == PRScale.m_coef[3])
	{
		m_ReDataPRWave.SetViewCoef(PRScale.m_coef[3]);
		m_ReDataPRWave.ScaleViewEnale(TRUE,PRScale.m_ScaleMin[3],PRScale.m_ScaleMax[3],PRScale.m_ScaleNum[3]);
	}
}

void CAnalysisDataDlg::OnBnClickedButtonMin()
{
	// TODO: Add your control notification handler code here
	//PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	//PostMessage(WM_SYSCOMMAND, SC_RESTORE, 0);//还原

}

void CAnalysisDataDlg::OnBnClickedButtonViewrestore()
{
	// TODO: Add your control notification handler code here
	m_ReDataPlsWave.SetViewCoef(0.73);
	m_ReDataSpO2Wave.SetViewCoef(0.254);
	m_ReDataRespWave.SetViewCoef(13.41);
	m_ReDataRRWave.SetViewCoef(1.264);
	m_ReDataPRWave.SetViewCoef(1.27);
}

void CAnalysisDataDlg::InsertMessageToList(CString str)
{
	static UINT ui32Count = 0;
	ui32Count++;
	m_CListCtrlMessage.InsertItem(ui32Count,str);
	m_CListCtrlMessage.SendMessage(WM_VSCROLL,SB_BOTTOM,NULL);
	Invalidate(FALSE);
}

void CAnalysisDataDlg::AnalyseResult()
{
	//CString str;
	//str.Format(_T("数据文件中："));
	//InsertMessageToList(str);
	//str.Format(_T("		SpO2最高为：      %d，最低为：%d"),m_maxValue[1],m_minValue[1]);
	//InsertMessageToList(str);

	////str.Format(_T("		Resp Rate最高为： %d，最低为：%d"),m_maxValue[3],m_minValue[3]);
	////InsertMessageToList(str);

	//str.Format(_T("		Pulse Rate最高为：%d，最低为：%d"),m_maxValue[4],m_minValue[4]);
	//InsertMessageToList(str);

}
void CAnalysisDataDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}


