// PC_IBPTestToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PC_IBPTestTool.h"
#include "PC_IBPTestToolDlg.h"
#include "RESPPackID.h"
#include "CalDlg.h"
#include "SetBaseprussDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPC_IBPTestToolDlg 对话框




CPC_IBPTestToolDlg::CPC_IBPTestToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPC_IBPTestToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_pcComPort = NULL;
	m_fPrussure = 0;
	m_pfSaveData =NULL;//数据存储初始化
}


void CPC_IBPTestToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_WAVE, m_CStaticWave);
	DDX_Control(pDX, ID_TOPQUIT, m_ButtonQuit);
	//	DDX_Control(pDX, IDC_PRESSURE, m_PRViewValue);
//	DDX_Control(pDX, IDC_PRESSURE, m_PrussureView);
}

BEGIN_MESSAGE_MAP(CPC_IBPTestToolDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_WAVE, &CPC_IBPTestToolDlg::OnStnClickedStaticWave)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_TOPQUIT, &CPC_IBPTestToolDlg::OnBnClickedTopquit)
	ON_BN_CLICKED(IDC_SAVEDATA, &CPC_IBPTestToolDlg::OnBnClickedSavedata)
	ON_BN_CLICKED(IDC_CALIBRATION, &CPC_IBPTestToolDlg::OnBnClickedCalibration)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_QUERYINFO, &CPC_IBPTestToolDlg::OnMenuQueryInfo)
	ON_COMMAND(ID_MENU_CHECKLEAKAGE, &CPC_IBPTestToolDlg::OnMenuCheckLeakage)
	ON_COMMAND(ID_MENU_RESETMODULE, &CPC_IBPTestToolDlg::OnMenuResetModule)
	ON_COMMAND(ID_MENU_SETBASEPRESS, &CPC_IBPTestToolDlg::OnMenuSetBasePress)
	ON_COMMAND(ID_SETADULTMODE, &CPC_IBPTestToolDlg::OnSetAdultMode)
	ON_COMMAND(ID_SETCHILDMODE, &CPC_IBPTestToolDlg::OnSetChildMode)
	ON_COMMAND(ID_SETNEWBORNMODE, &CPC_IBPTestToolDlg::OnSetNewbornMode)
	ON_BN_CLICKED(IDC_BUTTON1, &CPC_IBPTestToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_START, &CPC_IBPTestToolDlg::OnBnClickedButtonStart)
	ON_COMMAND(ID_SCAN500, &CPC_IBPTestToolDlg::OnScan500)
	ON_COMMAND(ID_SCAN250, &CPC_IBPTestToolDlg::OnScan250)
	ON_COMMAND(ID_SCAN125, &CPC_IBPTestToolDlg::OnScan125)
	ON_COMMAND(ID_SCAN100, &CPC_IBPTestToolDlg::OnScan100)
	ON_COMMAND(ID_SCAN50, &CPC_IBPTestToolDlg::OnScan50)
	ON_COMMAND(ID_SETVIEWX1, &CPC_IBPTestToolDlg::OnSetviewx1)
	ON_COMMAND(ID_SETVIEWX2, &CPC_IBPTestToolDlg::OnSetviewx2)
	ON_COMMAND(ID_SETVIEWX3, &CPC_IBPTestToolDlg::OnSetviewx3)
	ON_COMMAND(ID_MENU_REBRUSH, &CPC_IBPTestToolDlg::OnMenuRebrush)
	ON_BN_CLICKED(IDC_SETMODE, &CPC_IBPTestToolDlg::OnBnClickedSetmode)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MODULESTOP, &CPC_IBPTestToolDlg::OnModulestop)
	ON_COMMAND(ID_MODULESTART, &CPC_IBPTestToolDlg::OnModulestart)
	ON_COMMAND(ID_SENSITIVTY1, &CPC_IBPTestToolDlg::OnSensitivty1)
	ON_COMMAND(ID_SENSITIVTY2, &CPC_IBPTestToolDlg::OnSensitivty2)
	ON_COMMAND(ID_SENSITIVTY3, &CPC_IBPTestToolDlg::OnSensitivty3)
	ON_COMMAND(ID_SENSITIVTY4, &CPC_IBPTestToolDlg::OnSensitivty4)
	ON_COMMAND(ID_SENSITIVTY5, &CPC_IBPTestToolDlg::OnSensitivty5)
END_MESSAGE_MAP()


// CPC_IBPTestToolDlg 消息处理程序

BOOL CPC_IBPTestToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	SetWindowText(_T("呼吸监测平台"));
	for (UINT a = 0; a<2000;a++)
	{
		SampleFilterHP005(0,2000);
	}

	// TODO: 在此添加额外的初始化代码

	//pSleepMonitorDlg = new CSleepMonitorDlg; 
	//pSleepMonitorDlg->Create(IDD_SLEEPMONITOR_DIALOG,NULL);
	//pSleepMonitorDlg->ShowWindow(SW_HIDE);
	//pSleepMonitorDlg->m_pcComPort = m_pcComPort;
	//整个大小
	CRect tRectWindow;
	GetWindowRect(tRectWindow);
	CRect tRectClient;
	GetClientRect(tRectClient);

	CRect tRectNewWindow;
	tRectNewWindow.top = 0;
	tRectNewWindow.left = 0;
	tRectNewWindow.right = CLIENT_W+ tRectWindow.Width() - tRectClient.Width();
	tRectNewWindow.bottom =CLIENT_H+ tRectWindow.Height() - tRectClient.Height();
	MoveWindow(0, 0, tRectNewWindow.right, tRectNewWindow.bottom);

	GetDlgItem(IDC_PRESSURE)->SetWindowText(_T(""));
	GetDlgItem(IDC_RESPRATE)->SetWindowText(_T(""));

	GetDlgItem(IDC_PRESSURE)->MoveWindow(700, 75, 135,50);
	GetDlgItem(IDC_RESPRATE)->MoveWindow(455, 75, 135,50);
	GetDlgItem(ID_TOPQUIT)->MoveWindow(1060, 5, 30,30);

	m_ButtonQuit.MoveWindow(1055,10,33,33,0);
	m_ButtonQuit.SetBitmaps(IDB_QUIT1,RGB(255, 0, 0),IDB_QUIT2,RGB(0, 0, 255));
	m_ButtonQuit.DrawTransparent(TRUE);

	GetDlgItem(IDC_STATIC_WAVE)->MoveWindow(10, 145, WAVE_W,WAVE_H);//TITLE_PATIENT_W, TITLE_PATIENT_H);
	m_CStaticWave.SetRegion(WAVE_W,WAVE_H);
	//////////////////////////////////////////////////////////////////////////
	CFont *font1;
	font1 = new CFont;
	font1->CreateFont(60, 0, 0, 0, FW_BOLD,
		1, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, TEXT("Times New Roman"));

	GetDlgItem(IDC_PRESSURE)->SetFont(font1);
	GetDlgItem(IDC_RESPRATE)->SetFont(font1);

//////////////////////////////////////////////////////////////////////////
	m_cMenu.LoadMenuW(IDR_MAINMENU);
	//////////////////////////////////////////////////////////////////////////

//	MoveWindow(0,0,380,295);
	CRgn m_rgn; 
	RECT rc; 
	GetWindowRect(&rc); 
	m_rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,40,40); 
	SetWindowRgn(m_rgn,TRUE); 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//串口
	m_pcComWatchThread=new CComWatchThread(m_pcComPort, this);
	m_pcComWatchThread->CreateThread(CREATE_SUSPENDED);
	m_pcComWatchThread->SetThreadPriority(THREAD_PRIORITY_LOWEST);
	m_pcComWatchThread->ResumeThread();
	//////////////////////////////////////////////////////////////////////////
	SetTimer(1,200,NULL);
	//////////////////////////////////////////////////////////////////////////
	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
//	pcMenuPopup->CheckMenuRadioItem(ID_SCAN500, ID_SCAN50, ID_SCAN500, MF_BYCOMMAND);
//	pcMenuPopup->CheckMenuRadioItem(ID_SETVIEWX1, ID_SETVIEWX3, ID_SETVIEWX1, MF_BYCOMMAND);

	InitAlgorithm();//算法初始化

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPC_IBPTestToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		DrawBackground(&dc);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPC_IBPTestToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPC_IBPTestToolDlg::RcvData(WITLEAF_PACKET tWitleafPacket)
{
	static UCHAR RespRate;
	static UCHAR RespFlag;
	static UCHAR PatientType;

	if(PARAM_RESP == tWitleafPacket.u8ParaType)
	{
		if(WITLEAF_PACKET_TYPE_DD == tWitleafPacket.u8Type)
		{
			if(MSG_RESP_WAVE_DATA == tWitleafPacket.u8Id)
			{
				int temp = tWitleafPacket.pu8Data[0] +(tWitleafPacket.pu8Data[1]<<8);
		//		INT temp1 =FilterHighPass0_15(temp);
				static int preValue=0;
				m_fPrussure = tWitleafPacket.pu8Data[2];
				if(m_pfSaveData != NULL)
				{
					_ftprintf(m_pfSaveData,_T("\n%d\t%d\t%d"),temp,RespRate,RespFlag);	
					RespRate = 0;
					RespFlag = 0;
				}
				if (temp>20000)
				{
					temp = preValue; 
				}
				else
					preValue = temp;

				m_CStaticWave.RcvOneData(temp/2);
			}
			else if(MSG_RESP_RESULT_STATUS == tWitleafPacket.u8Id)
			{
				RespRate=tWitleafPacket.pu8Data[0];
				RespFlag=tWitleafPacket.pu8Data[1];	
				PatientType=tWitleafPacket.pu8Data[2];	
				
				i32perSecCount = 0;
				/*SetCurrentRESPValue(RespRate,RespFlag);*/
			}		
			else if(MSG_RESP_LEAKAGE_STATUS == tWitleafPacket.u8Id)
			{
				MessageBox(_T("漏气！"),_T("Worning!"),MB_ICONWARNING);
			}		
			else if(MSG_RESP_REQUEST_START == tWitleafPacket.u8Id)//握手
			{
				WITLEAF_PACKET tPacket;	
				tPacket.u8Len = 0x0A;
				tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
				tPacket.u8Id = CMD_RESP_START;

				SendCmdPacket(tPacket);		
			}
		}
		else if(WITLEAF_PACKET_TYPE_DA == tWitleafPacket.u8Type)
		{
			CString s;
			if(MSG_RESP_MODULE_ANSWER == tWitleafPacket.u8Id)
			{
				/*
				COMMAND_PARAM_ERR=1,
				COMMAND_TYPE_ERR,
				COMMAND_ID_ERR,
				COMMAND_DATA_ERR,
				COMMAND_SERIAL_ERR,
				COMMAND_CHEEKSUM_ERR,
				COMMAND_EXESUCCESS_OK,
				COMMAND_EXEFAILURE_ERR,
				SYSETEM_BUSY_ERR
				*/
				switch(tWitleafPacket.pu8Data[0])
				{
				case 0x01:

					break;
				case 0x02:
					break;
				case 0x03:

					break;
				case 0x04:

					break;
				case 0x05:

					break;
				case 0x06:

					break;
				case 0x07:
					s=_T("命令执行成功！");
					break;
				case 0x08:
					s=_T("命令执行失败！");
					break;
				case 0x09:

					break;
				}
				MessageBox(s);
			}		
			else if(MSG_RESP_MODULE_INFO == tWitleafPacket.u8Id)
			{

			}		
		}		
	}
}

void CPC_IBPTestToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{	
		SetCurrentPRValue((float)m_fPrussure);
		m_fPrussure = 0;

		i32perSecCount++;
		if (i32perSecCount >= 50)
		{
			i32perSecCount = 0;
		/*	SetCurrentRESPValue(0,0);*/
		}
	}

	if(nIDEvent == 2)
	{
		static bool t=FALSE;
		if (t == TRUE)
		{
			t = FALSE;
			GetDlgItem(IDC_SAVEDATA)->SetWindowText(_T("Saving..."));
		}else
		{
			GetDlgItem(IDC_SAVEDATA)->SetWindowText(_T("Saving"));		
			t = TRUE;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CPC_IBPTestToolDlg::SetCurrentPRValue(float tValue)
{
	static CString temp;
	CString TextValue;

	TextValue.Format(TEXT("%3.0f  "),tValue);

	if (temp == TextValue )
	{
		return;
	}
	else
	{
		temp = TextValue;
	}

	GetDlgItem(IDC_PRESSURE)->SetWindowText(TextValue);

	CRect cRect(680, 70, 700+160, 140);
	InvalidateRect(cRect, false);
}

void CPC_IBPTestToolDlg::SetCurrentRESPValue(UCHAR RespRate,UCHAR RespFlag)
{
	static CString tPreviousText;
	static CString TextValue;

	//if (RespFlag ==0)
	//{
	//	count++;
	//}
	//else
	//{
	//	count = 0;
	//}
	//
	//if (count >= 625*8)//5s没有检测到
	//{
	//	m_CStaticWave.SetRESPStatus(TEXT("未检测到呼吸         "));
	//	TextValue.Format(TEXT("- - - "));
	//	count = 625*8;
	//}
	//else if ((count%15*8)==0)
	//{
	//	m_CStaticWave.SetRESPStatus(TEXT("检测到呼吸        "));
	//	TextValue.Format(TEXT("%d "),(UCHAR)(RespRate));
	//}
	if (RespFlag == 1)
	{
		m_CStaticWave.SetRESPStatus(TEXT("检测到呼吸        "));
		TextValue.Format(TEXT("%d "),(UCHAR)(RespRate));
	}
	else
	{
		m_CStaticWave.SetRESPStatus(TEXT("未检测到呼吸        "));
		TextValue.Format(TEXT("---"));
	}
	if (TextValue != tPreviousText)
	{
		GetDlgItem(IDC_RESPRATE)->SetWindowText(TextValue);
		CRect cRect(420, 70, 420+170, 140);
		InvalidateRect(cRect, false);
	}
	tPreviousText = TextValue;

/*
	if (m_RespFlag ==0)
	{
		m_CStaticWave.SetRESPStatus(TEXT("未检测到呼吸"));
		TextValue.Format(TEXT("- - - "));
		TextValue.Format(TEXT("%d "),(UCHAR)(m_RespRate));
	}
	else
	{
		m_CStaticWave.SetRESPStatus(TEXT("检测到呼吸"));
		TextValue.Format(TEXT("%d "),(UCHAR)(m_RespRate));
	}

	GetDlgItem(IDC_RESPRATE)->SetWindowText(TextValue);

	CRect cRect(420, 70, 420+170, 140);
	InvalidateRect(cRect, false);
*/
}

HBRUSH CPC_IBPTestToolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if (pWnd->GetDlgCtrlID() == IDC_PRESSURE||pWnd->GetDlgCtrlID() == IDC_RESPRATE)
	{
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetTextColor(RGB(0,0,0));
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CPC_IBPTestToolDlg::DrawBackground(CDC* pDC)
{
	CRect   rect;   
	GetClientRect(&rect);   
	CDC   dcMem;   
	dcMem.CreateCompatibleDC(pDC);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_IBPMain);   

	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
}

void CPC_IBPTestToolDlg::OnStnClickedStaticWave()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPC_IBPTestToolDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

void CPC_IBPTestToolDlg::OnBnClickedTopquit()
{
	if(6==MessageBox(_T("确定退出？"),_T("提示："),MB_YESNO|MB_ICONQUESTION))
	{
		PostMessage(WM_CLOSE,0,0);
	}
}

void CPC_IBPTestToolDlg::InitAlgorithm(void)
{
/*	WLRespInit();
	WLRespSetPatientType(WL_RESP_PATIENT_TYPE_ADULT);
	WLRespSetBreathSensitivity(WL_RESP_BREATH_SENSITIVITY_5);
*/
}

void CPC_IBPTestToolDlg::OnBnClickedSavedata()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pfSaveData==NULL)
	{
		CString pulseFileName;
		CTime realtime;
		realtime = CTime::GetCurrentTime();                 //把获得的当前时间保存到变量tm中
		pulseFileName=_T("RespRawWaveData_") +realtime.Format("%Y%m%d%H%M%S") ;
		CFileDialog fileDlg(FALSE, _T("xls"), pulseFileName, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY, _T("Text Files(*.xls)\0*.xls\0All Files(*.*)\0*.*\0\0"), this);
//		CFileDialog fileDlg(FALSE);
  //  	fileDlg.m_ofn.lpstrFilter=_T("Text Files(*.xls)\0*.xls\0All Files(*.*)\0*.*\0\0");
		//fileDlg.m_ofn.lpstrDefExt=_T("xls");
		//fileDlg.m_ofn.lpstrFileTitle=_T("Save RESP Wave Data");

		if(IDOK == fileDlg.DoModal())
		{
			m_pfSaveData = _tfopen(fileDlg.GetPathName(), _T("w"));
			if(m_pfSaveData != NULL)
			{
				_ftprintf(m_pfSaveData,_T("RESP Wave"));	
			}

			SetTimer(2,500,NULL);
		}
	}else if ( NULL != m_pfSaveData ) 
	{
		KillTimer(2);
		GetDlgItem(IDC_SAVEDATA)->SetWindowText(_T("Save"));
		fclose(m_pfSaveData);
		m_pfSaveData = NULL;
	}

}

bool CPC_IBPTestToolDlg::StartWitleaf_CmdHandler(WITLEAF_PACKET tPacket)
{
	if(PARAM_RESP == tPacket.u8ParaType)
	{
		if(WITLEAF_PACKET_TYPE_DD == tPacket.u8Type)
		{
			if(MSG_RESP_REQUEST_START == tPacket.u8Id)
			{
				if (0x0a == tPacket.u8Len)
				{
					return TRUE;
				}
			}		
		}
	}
	return false;
}

void CPC_IBPTestToolDlg::OnBnClickedCalibration()
{
	// TODO: 在此添加控件通知处理程序代码
/*	WITLEAF_PACKET tPacket;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Id = CMD_RESP_SET_CALIBRATION;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Len ;*/
	//CCalDlg Dlg;//(m_pcComPort);
	//Dlg.m_Comprot =  m_pcComPort;
	//Dlg.DoModal();
	CCalDlg *pDlg;//(m_pcComPort);
	pDlg = new CCalDlg; 
	pDlg->m_Comprot =  m_pcComPort;
	pDlg->Create(IDD_CALDLG,NULL);
	pDlg->ShowWindow(SW_SHOW);
}

void CPC_IBPTestToolDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	ClientToScreen(&point);
	pcMenuPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	CDialog::OnRButtonDown(nFlags, point);
}

void CPC_IBPTestToolDlg::OnMenuQueryInfo()
{
	// TODO: 在此添加命令处理程序代码
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 0x0A;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DR;
	tPacket.u8Id = CMD_RESP_MODULE_INFO;

	SendCmdPacket(tPacket);
}

void CPC_IBPTestToolDlg::OnMenuCheckLeakage()
{
	// TODO: 在此添加命令处理程序代码
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 0x0A;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_CHECK_LEAKAGE;

	SendCmdPacket(tPacket);
}

void CPC_IBPTestToolDlg::OnMenuResetModule()
{
	// TODO: 在此添加命令处理程序代码
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 0x0A;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_RESET_MODULE;
	tPacket.pu8Data[0] = 0x00;

	SendCmdPacket(tPacket);
}

void CPC_IBPTestToolDlg::OnMenuSetBasePress()
{
	// TODO: 在此添加命令处理程序代码
	CSetBaseprussDlg *pDlg;//(m_pcComPort);
	pDlg = new CSetBaseprussDlg(this); 
//	pDlg->m_Comprot =  m_pcComPort;
	pDlg->Create(IDD_BASEPRUSS_DIALOG,NULL);
	pDlg->ShowWindow(SW_SHOW);

}

void CPC_IBPTestToolDlg::OnSetAdultMode()
{
	// TODO: 在此添加命令处理程序代码
	/*
	unsigned char u8Len;
	unsigned char u8ParaType;
	unsigned char u8Type;
	unsigned char u8Id;
	unsigned int u32No;
	unsigned char pu8Data[WITLEAF_MAX_FRAME_DATA_LEN];
	unsigned char u8Checksum;
	*/
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 11;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_SET_PATIENT;
	tPacket.pu8Data[0] = 0x00;

	SendCmdPacket(tPacket);
}

void CPC_IBPTestToolDlg::OnSetChildMode()
{
	// TODO: 在此添加命令处理程序代码
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 0x0B;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_SET_PATIENT;
	tPacket.pu8Data[0] = 0x01;

	SendCmdPacket(tPacket);
}

void CPC_IBPTestToolDlg::OnSetNewbornMode()
{
	// TODO: 在此添加命令处理程序代码
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 0x0B;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_SET_PATIENT;
	tPacket.pu8Data[0] = 0x02;

	SendCmdPacket(tPacket);
}

void CPC_IBPTestToolDlg::SendCmdPacket(WITLEAF_PACKET tPacket)
{
/*
unsigned char u8Len;
unsigned char u8ParaType;
unsigned char u8Type;
unsigned char u8Id;
unsigned int u32No;
unsigned char pu8Data[WITLEAF_MAX_FRAME_DATA_LEN];
unsigned char u8Checksum;
*/
	unsigned char puchBuff[MAX_PATH];
	unsigned char uchIndex = 0;
	unsigned long gu32No = 0;

	puchBuff[uchIndex ++] = WITLEAF_PACKET_HEAD;
	puchBuff[uchIndex ++] = tPacket.u8Len;
	puchBuff[uchIndex ++] = PARAM_RESP;
	puchBuff[uchIndex ++] = tPacket.u8Type;
	puchBuff[uchIndex ++] = tPacket.u8Id;
	puchBuff[uchIndex ++] = gu32No & 0xFF;
	puchBuff[uchIndex ++] = (gu32No >> 8) & 0xFF;
	puchBuff[uchIndex ++] = (gu32No >> 16) & 0xFF;
	puchBuff[uchIndex ++] = (gu32No >> 24) & 0xFF;

	gu32No ++;
	for ( int i = 0; i < tPacket.u8Len - 10; i ++ )
	{
		puchBuff[uchIndex ++] = tPacket.pu8Data[i];
	}

	unsigned char uchChecksum = 0;
	for ( int i = 1; i < uchIndex; i ++ )
	{
		uchChecksum += puchBuff[i];
	}
	puchBuff[uchIndex ++] = uchChecksum;

//	m_pcComPort->Send(puchBuff, uchIndex);
	m_pcComPort->Send(puchBuff,  tPacket.u8Len);
}

int CPC_IBPTestToolDlg::SampleFilterHP005(unsigned char u8Index, int u32Data)
{
	static INT32 gppi32XDataHP005[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	static INT32 gppi32YDataHP005[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	static INT32 gppi32Y1DataHP005[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

	INT32 i;
	INT32 i32Temp1, i32Temp2;

	for ( i = 3 - 1; i > 0; i -- ) {
		gppi32XDataHP005[u8Index][i] = gppi32XDataHP005[u8Index][i - 1];
		gppi32YDataHP005[u8Index][i] = gppi32YDataHP005[u8Index][i - 1];
		gppi32Y1DataHP005[u8Index][i] = gppi32Y1DataHP005[u8Index][i - 1];
	}

	gppi32XDataHP005[u8Index][0] = u32Data * 16;

	// Calculating
	i32Temp1 = 8189 * (gppi32XDataHP005[u8Index][0] + gppi32XDataHP005[u8Index][2])
		- 16378 * (gppi32XDataHP005[u8Index][1] - gppi32YDataHP005[u8Index][1])
		- 8186 * gppi32YDataHP005[u8Index][2];

	i32Temp2 = 16378 * gppi32Y1DataHP005[u8Index][1] - 8186 * gppi32Y1DataHP005[u8Index][2];

	if ( 0 <= i32Temp2 ) {
		i32Temp2 >>= 13;
	}
	else {
		i32Temp2 = - i32Temp2;
		i32Temp2 >>= 13;
		i32Temp2 = - i32Temp2;
	}

	i32Temp1 += i32Temp2;

	if ( 0 <= i32Temp1 ) {
		gppi32Y1DataHP005[u8Index][0] = i32Temp1 % 8192;
		i32Temp1 >>= 13;
	}
	else {
		gppi32Y1DataHP005[u8Index][0] = - ((-i32Temp1) % 8192);
		i32Temp1 = - i32Temp1;
		i32Temp1 >>= 13;
		i32Temp1 = - i32Temp1;
	}

	gppi32YDataHP005[u8Index][0] = i32Temp1;

	return i32Temp1 / 16;
}

void CPC_IBPTestToolDlg::SetBaseprussCmd(unsigned char t)
{
	WITLEAF_PACKET tPacket;
	tPacket.u8Len = 0x0B;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_SET_BASEPRESS;
	tPacket.pu8Data[0] = t;

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetBaseprussDlg *pDlg;//(m_pcComPort);
	pDlg = new CSetBaseprussDlg(this); 
	//	pDlg->m_Comprot =  m_pcComPort;
	pDlg->Create(IDD_BASEPRUSS_DIALOG,NULL);
	pDlg->ShowWindow(SW_SHOW);
}

int CPC_IBPTestToolDlg::FilterHighPass0_15(int iData)
{
#define COEFF_NUM_HP0_15	3

	static int xData[COEFF_NUM_HP0_15] = {0, 0, 0};
	static int yData[COEFF_NUM_HP0_15] = {0, 0, 0};
	static int y1Data[COEFF_NUM_HP0_15] = {0, 0, 0};

	int i;
	int iTemp1, iTemp2;

	for ( i = COEFF_NUM_HP0_15 - 1; i > 0; i -- )
	{
		xData[i] = xData[i - 1];
		yData[i] = yData[i - 1];
		y1Data[i] = y1Data[i - 1];
	}

	xData[0] = iData;

	iTemp1 = (int)(8101.513 * xData[0] - 16203 * xData[1] + 8101.513 * xData[2] + 16202 * yData[1] - 8012.026 * yData[2]);

	iTemp2 = (int)(16202 * y1Data[1] - 8012.026 * y1Data[2]);

	if ( 0 <= iTemp2 )
	{
		iTemp2 >>= 13;
	}
	else
	{
		iTemp2 = - iTemp2;
		iTemp2 >>= 13;
		iTemp2 = - iTemp2;
	}

	iTemp1 += iTemp2;

	if ( 0 <= iTemp1 )
	{
		y1Data[0] = iTemp1 % 8192;
		iTemp1 = iTemp1 >> 13;
	}
	else 
	{
		y1Data[0] = - ((-iTemp1) % 8192);
		iTemp1 = - iTemp1;
		iTemp1 = iTemp1 >> 13;
		iTemp1 = - iTemp1;
	}

	yData[0] = iTemp1;

	return iTemp1;
}

void CPC_IBPTestToolDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 10;
	tPacket.u8ParaType = PARAM_SPO2;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = 1;
	tPacket.u32No = 0;					

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnScan500()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetScanSpeed(SCAN_SPEED_125);
	m_CStaticWave.Invalidate();

	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SCAN500, ID_SCAN50, ID_SCAN500, MF_BYCOMMAND);
}

void CPC_IBPTestToolDlg::OnScan250()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetScanSpeed(SCAN_SPEED_62_5);	
	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SCAN500, ID_SCAN50, ID_SCAN250, MF_BYCOMMAND);

}

void CPC_IBPTestToolDlg::OnScan125()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetScanSpeed(SCAN_SPEED_40);	
	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SCAN500, ID_SCAN50, ID_SCAN125, MF_BYCOMMAND);

}

void CPC_IBPTestToolDlg::OnScan100()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetScanSpeed(SCAN_SPEED_25);

	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SCAN500, ID_SCAN50, ID_SCAN100, MF_BYCOMMAND);

}

void CPC_IBPTestToolDlg::OnScan50()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetScanSpeed(SCAN_SPEED_12_5);

	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SCAN500, ID_SCAN50, ID_SCAN50, MF_BYCOMMAND);
}

void CPC_IBPTestToolDlg::OnSetviewx1()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetShowGain(1);
	m_CStaticWave.Invalidate();

	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SETVIEWX1, ID_SETVIEWX3, ID_SETVIEWX1, MF_BYCOMMAND);

	//ShowWindow(SW_HIDE);
	//CSleepMonitorDlg dlg;
	//dlg.DoModal();
}

void CPC_IBPTestToolDlg::OnSetviewx2()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetShowGain(2);
	m_CStaticWave.Invalidate();
	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SETVIEWX1, ID_SETVIEWX3, ID_SETVIEWX2, MF_BYCOMMAND);
}

void CPC_IBPTestToolDlg::OnSetviewx3()
{
	// TODO: 在此添加命令处理程序代码
	m_CStaticWave.SetShowGain(3);
	m_CStaticWave.Invalidate();

	CMenu * pcMenuPopup = m_cMenu.GetSubMenu(0);
	pcMenuPopup->CheckMenuRadioItem(ID_SETVIEWX1, ID_SETVIEWX3, ID_SETVIEWX3, MF_BYCOMMAND);
}

void CPC_IBPTestToolDlg::OnMenuRebrush()
{
	// TODO: 在此添加命令处理程序代码
// 	Invalidate();
// 	UpdateWindow();
	RedrawWindow();
}

void CPC_IBPTestToolDlg::OnBnClickedSetmode()
{
	// TODO: Add your control notification handler code here
// 	pSleepMonitorDlg->ShowWindow(SW_SHOW);
// 	m_pcComWatchThread->m_bModeflag = TRUE;
// 	ShowWindow(SW_HIDE);
//	SendMessage(WM_CLOSE);
}

BOOL CPC_IBPTestToolDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	
	//CDC dcMem;
	//dcMem.CreateCompatibleDC(pDC);
	//CBitmap *pOldBitmap = dcMem.SelectObject(&m_SleepMainBk);

	//CRect rcClient;
	//GetClientRect(&rcClient);
	//pDC->BitBlt(rcClient.left,  rcClient.top, rcClient.Width(), rcClient.Height(),
	//	&dcMem, 0, 0, SRCCOPY);
	//dcMem.SelectObject(pOldBitmap);
	//dcMem.DeleteDC();
//	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}

void CPC_IBPTestToolDlg::OnModulestop()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = 3;
	tPacket.u32No = 0;					
	tPacket.pu8Data[0] = 0;

	SendCmdPacket(tPacket);	

}

void CPC_IBPTestToolDlg::OnModulestart()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = 0x03;
	tPacket.u32No = 0;	
	tPacket.pu8Data[0] = 1;

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnSensitivty1()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_BREATH_SENSITIVITY;
	tPacket.u32No = 0;	
	tPacket.pu8Data[0] = 0;

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnSensitivty2()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_BREATH_SENSITIVITY;
	tPacket.u32No = 0;	
	tPacket.pu8Data[0] = 1;

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnSensitivty3()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_BREATH_SENSITIVITY;
	tPacket.u32No = 0;	
	tPacket.pu8Data[0] = 2;

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnSensitivty4()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_BREATH_SENSITIVITY;
	tPacket.u32No = 0;	
	tPacket.pu8Data[0] = 3;

	SendCmdPacket(tPacket);	
}

void CPC_IBPTestToolDlg::OnSensitivty5()
{
	// TODO: Add your command handler code here
	WITLEAF_PACKET tPacket;

	tPacket.u8Len = 11;
	tPacket.u8ParaType = PARAM_RESP;
	tPacket.u8Type = WITLEAF_PACKET_TYPE_DC;
	tPacket.u8Id = CMD_RESP_BREATH_SENSITIVITY;
	tPacket.u32No = 0;	
	tPacket.pu8Data[0] = 4;

	SendCmdPacket(tPacket);	
}
