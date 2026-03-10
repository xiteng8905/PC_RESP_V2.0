#if !defined(AFX_COMWATCHTHREAD_H__540B53AF_DEAB_11D5_9061_0010885090EC__INCLUDED_)
#define AFX_COMWATCHTHREAD_H__540B53AF_DEAB_11D5_9061_0010885090EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComWatchThread.h : header file
//

#include "ComPort.h"

class CPC_IBPTestToolDlg;
class CSleepMonitorDlg;
/////////////////////////////////////////////////////////////////////////////
// CComWatchThread thread

#define WITLEAF_UART_BUFF_LEN		1024
#define WITLEAF_MIN_FRAME_LEN		10
#define WITLEAF_MAX_FRAME_DATA_LEN	48
#define WITLEAF_MAX_FRAME_CACHE_LEN	100

#define WITLEAF_PACKET_HEAD	0xFA

//读取数据
typedef struct _WITLEAF_UARTCOMM
{
	unsigned char pu8Buff[WITLEAF_UART_BUFF_LEN];				// 串口数据接收缓冲区
	unsigned int u32WriteIndex;                   					// 串口数据接收缓冲区写入数据下标
	unsigned int u32ReadIndex;                    					// 串口数据接收缓冲区读出数据下标     
} WITLEAF_UARTCOMM;

typedef enum _WITLEAF_SEARCH_PACKET_STATUS_LIST
{
	WITLEAF_SEARCH_PACKET_STATUS_HEAD,
	WITLEAF_SEARCH_PACKET_STATUS_LEN,
	WITLEAF_SEARCH_PACKET_STATUS_PARA_TYPE,	 //eg:CCO,IBP
	WITLEAF_SEARCH_PACKET_STATUS_TYPE,		 //eg:DC,DR
	WITLEAF_SEARCH_PACKET_STATUS_ID,
	WITLEAF_SEARCH_PACKET_STATUS_NO_0,
	WITLEAF_SEARCH_PACKET_STATUS_NO_1,
	WITLEAF_SEARCH_PACKET_STATUS_NO_2,
	WITLEAF_SEARCH_PACKET_STATUS_NO_3,
	WITLEAF_SEARCH_PACKET_STATUS_DATA,	
	WITLEAF_SEARCH_PACKET_STATUS_CHECKSUM,

	WITLEAF_SEARCH_PACKET_STATUS_MAX
} WITLEAF_SEARCH_PACKET_STATUS_LIST;

//解析出来的包                                      
typedef struct _WITLEAF_PACKET
{
	unsigned char u8Len;
	unsigned char u8ParaType;
	unsigned char u8Type;
	unsigned char u8Id;
	unsigned int u32No;
	unsigned char pu8Data[WITLEAF_MAX_FRAME_DATA_LEN];
	unsigned char u8Checksum;
} WITLEAF_PACKET;

//数据包类型 
typedef enum _WITLEAF_PACKET_TYPE_LIST
{	
	WITLEAF_PACKET_TYPE_DC = 0x01,
	WITLEAF_PACKET_TYPE_DR = 0x02,
	WITLEAF_PACKET_TYPE_DA = 0x03,
	WITLEAF_PACKET_TYPE_DD = 0x04,

	WITLEAF_PACKET_TYPE_MAX
} WITLEAF_PACKET_TYPE_LIST;


class CComWatchThread : public CWinThread
{
	DECLARE_DYNCREATE(CComWatchThread)
protected:
	CComWatchThread();           // protected constructor used by dynamic creation
	

// Attributes
public:
	CComPort *m_pcComPort;
	CPC_IBPTestToolDlg* m_pcMonitorDlg;
	CSleepMonitorDlg *m_pcSleepMonitorDlg;

	WITLEAF_UARTCOMM gtWitleafComm;
	WITLEAF_PACKET gtWitleafPacket;

// Operations
public:
	CComWatchThread(CComPort *pcComPort, CPC_IBPTestToolDlg *pcMonitorDlg); 
	CComWatchThread(CComPort * pcComPort, CSleepMonitorDlg* pcMonitorDlg);
	virtual ~CComWatchThread();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComWatchThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComWatchThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	unsigned char WitleafUnpackUartData(unsigned char * pu8Buff, unsigned int u32BuffLen, WITLEAF_PACKET * ptPacket, unsigned int * pu32RemainLen);
	unsigned int WitleafGetUartRxBuffLen();
	unsigned int WitleafGetUartRxStr(unsigned char * pu8DestBuff, unsigned int u32Len);	 // 读取缓冲区数据内容
	void WitleafRestoreUartRxStr(unsigned int u32Len);
	void WitleafRcvCmd();//unsigned char * puchBuff, unsigned int u32Size)

public:
	void SetStopFlag(bool bFlag);
	BOOL m_bModeflag;
protected:
	bool m_bStopFlag;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMWATCHTHREAD_H__540B53AF_DEAB_11D5_9061_0010885090EC__INCLUDED_)
