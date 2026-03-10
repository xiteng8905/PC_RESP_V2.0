// ComWatchThread.cpp : implementation file
//

#include "stdafx.h"
#include "ComWatchThread.h"
#include "PC_IBPTestTool.h"
#include "PC_IBPTestToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComWatchThread

IMPLEMENT_DYNCREATE(CComWatchThread, CWinThread)

FILE * gpfResultFile = NULL;

CComWatchThread::CComWatchThread()
{
	gtWitleafComm.u32ReadIndex = 0;
	gtWitleafComm.u32WriteIndex = 0;

	if ( NULL == gpfResultFile )
	{
		gpfResultFile = fopen("rcvdata.dat", "wb");
	}
}

CComWatchThread::CComWatchThread(CComPort * pcComPort, CPC_IBPTestToolDlg* pcMonitorDlg)
{
	m_pcComPort = pcComPort;
	m_pcMonitorDlg = pcMonitorDlg;
	m_pcSleepMonitorDlg = NULL;

	gtWitleafComm.u32ReadIndex = 0;
	gtWitleafComm.u32WriteIndex = 0;

	m_bStopFlag = false;
	m_bModeflag = false;
	if ( NULL == gpfResultFile )
	{
		gpfResultFile = fopen("rcvdata.dat", "wb");
	}
}

CComWatchThread::CComWatchThread(CComPort * pcComPort, CSleepMonitorDlg* pcMonitorDlg)
{
	m_pcComPort = pcComPort;
	m_pcSleepMonitorDlg = pcMonitorDlg;
	m_pcMonitorDlg = NULL;

	gtWitleafComm.u32ReadIndex = 0;
	gtWitleafComm.u32WriteIndex = 0;

	m_bStopFlag = false;
	m_bModeflag = false;
	if ( NULL == gpfResultFile )
	{
		gpfResultFile = fopen("rcvdata.dat", "wb");
	}
}

CComWatchThread::~CComWatchThread()
{
	if ( NULL != gpfResultFile )
	{
		fclose(gpfResultFile);
	}
}

BOOL CComWatchThread::InitInstance()                
{
	// TODO:  perform and per-thread initialization here
	m_bStopFlag = false;

	BYTE  pBuf[512];
	DWORD size;

	memset(pBuf, 0, 512);
	while( (m_pcComPort != NULL) && (false == m_bStopFlag) ) 
	{
		Sleep(0);
		// 如果没有受到数据，该Recv函数将阻塞
		if(!m_pcComPort->Recv(pBuf, 512, size)) 
			// 发生了什么错误，休息一会，接着来.
			continue;

		for ( UINT i = 0;  i < size; i ++ ) 
		{
			gtWitleafComm.pu8Buff[gtWitleafComm.u32WriteIndex] = pBuf[i];
			gtWitleafComm.u32WriteIndex++;
			if ( gtWitleafComm.u32WriteIndex >= WITLEAF_UART_BUFF_LEN ) 
			{
				gtWitleafComm.u32WriteIndex = 0;
			}

			fwrite(&(pBuf[i]), 1, 1, gpfResultFile);
			fflush(gpfResultFile);
		}

		WitleafRcvCmd();
	}

    return TRUE;
}

int CComWatchThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CComWatchThread, CWinThread)
	//{{AFX_MSG_MAP(CComWatchThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


unsigned int CComWatchThread::WitleafGetUartRxBuffLen()
{
	unsigned int u32Len;

	if ( gtWitleafComm.u32WriteIndex >= gtWitleafComm.u32ReadIndex )
	{
		u32Len = gtWitleafComm.u32WriteIndex - gtWitleafComm.u32ReadIndex;
	}
	else
	{
		u32Len = WITLEAF_UART_BUFF_LEN - gtWitleafComm.u32ReadIndex + gtWitleafComm.u32WriteIndex;
	}

	return u32Len;
}

unsigned int CComWatchThread::WitleafGetUartRxStr(unsigned char * pu8DestBuff, unsigned int u32Len)	 // 读取缓冲区数据内容
{
	unsigned int u32RealLen;
	unsigned int u32Index;

	u32RealLen = 0;

	for ( u32Index = 0; u32Index < u32Len; u32Index ++ )
	{
		if ( gtWitleafComm.u32ReadIndex == gtWitleafComm.u32WriteIndex )
		{
			return u32RealLen;
		}
		pu8DestBuff[u32Index] = gtWitleafComm.pu8Buff[gtWitleafComm.u32ReadIndex];

		gtWitleafComm.u32ReadIndex ++;
		u32RealLen ++;

		if ( WITLEAF_UART_BUFF_LEN <= gtWitleafComm.u32ReadIndex )
		{
			gtWitleafComm.u32ReadIndex = 0;
		}
	}

	return u32Len;
}

void CComWatchThread::WitleafRestoreUartRxStr(unsigned int u32Len)
{
	if ( gtWitleafComm.u32ReadIndex >= u32Len )
	{
		gtWitleafComm.u32ReadIndex = gtWitleafComm.u32ReadIndex - u32Len;
	}
	else
	{
		gtWitleafComm.u32ReadIndex = WITLEAF_UART_BUFF_LEN + gtWitleafComm.u32ReadIndex - u32Len;
	}
}

unsigned char CComWatchThread::WitleafUnpackUartData(unsigned char * pu8Buff, unsigned int u32BuffLen, WITLEAF_PACKET * ptPacket, unsigned int * pu32RemainLen)
{
	WITLEAF_SEARCH_PACKET_STATUS_LIST tSearchPacketStatus;

	unsigned char u8CurrentByte;
	unsigned char pu8No[4];
	unsigned char u8Checksum = 0;

	unsigned int u32Len;
	unsigned int u32HeadIndex = 0;
	unsigned int u32Index;

	int i = 0;

	tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_HEAD;

	u32Len = u32BuffLen;
	u32Index = 0;

	while ( u32Len > 0) 
	{        
		u8CurrentByte = pu8Buff[u32Index ++];
		u32Len --;

		switch ( tSearchPacketStatus )
		{
		case WITLEAF_SEARCH_PACKET_STATUS_HEAD:
			if ( WITLEAF_PACKET_HEAD == u8CurrentByte )
			{
				tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_LEN;
				u32HeadIndex = (u32Index - 1);
			}
			else if ( u32Len < WITLEAF_MIN_FRAME_LEN )
			{
				(* pu32RemainLen) = u32Len + 1;
				return 0;
			}
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_LEN:
			ptPacket->u8Len = u8CurrentByte;
			if ( WITLEAF_MAX_FRAME_DATA_LEN < ptPacket->u8Len ) 
			{
				u32Index = u32HeadIndex + 1;
				u32Len = u32BuffLen - u32Index;
				tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_HEAD;                         
			}/*
			else if ( (ptPacket->u8Len - 2) <= u32Len )
			{
				tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_PARA_TYPE;
			}
			else
			{
				(* pu32RemainLen) = u32Len + 2;
				return 0;
			}  */
			else //屏蔽上面，以下黄老师，要求加的
			{
				int iLen = ptPacket->u8Len - 2;
				int i32Len = u32Len;
				if ( iLen <= i32Len )
				{
					tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_PARA_TYPE;
				}
				else
				{
					(* pu32RemainLen) = u32Len + 2;
					return 0;
				}
			}//到此处

			break;

		case WITLEAF_SEARCH_PACKET_STATUS_PARA_TYPE:
			ptPacket->u8ParaType = u8CurrentByte;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_TYPE;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_TYPE:
			ptPacket->u8Type = u8CurrentByte;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_ID;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_ID:
			ptPacket->u8Id = u8CurrentByte;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_NO_0;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_NO_0:
			pu8No[0] = u8CurrentByte;
			ptPacket->u32No = u8CurrentByte;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_NO_1;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_NO_1:
			pu8No[1] = u8CurrentByte;
			ptPacket->u32No += u8CurrentByte << 8;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_NO_2;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_NO_2:
			pu8No[2] = u8CurrentByte;
			ptPacket->u32No += u8CurrentByte << 16;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_NO_3;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_NO_3:
			pu8No[3] = u8CurrentByte;
			ptPacket->u32No += u8CurrentByte << 24;
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_DATA;

		case WITLEAF_SEARCH_PACKET_STATUS_DATA:
			u8Checksum = ptPacket->u8Len;
			u8Checksum += ptPacket->u8ParaType;
			u8Checksum += ptPacket->u8Type;
			u8Checksum += ptPacket->u8Id;
			u8Checksum += pu8No[0];
			u8Checksum += pu8No[1];
			u8Checksum += pu8No[2];
			u8Checksum += pu8No[3];
			for ( i = 0; i < (ptPacket->u8Len - 10); i ++ )
			{
				ptPacket->pu8Data[i] = pu8Buff[u32Index ++];
				u8Checksum += ptPacket->pu8Data[i];
				u32Len --;
			}
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_CHECKSUM;
			break;

		case WITLEAF_SEARCH_PACKET_STATUS_CHECKSUM:
			if ( u8Checksum == u8CurrentByte )
			{
				ptPacket->u8Checksum = u8CurrentByte;
				(* pu32RemainLen) = u32BuffLen - u32Index;
				return 1;
			}
			else
			{
				tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_HEAD;
				u32Index = u32HeadIndex + 1;
				u32Len = u32BuffLen - u32Index;
			}
			break;

		default:
			tSearchPacketStatus = WITLEAF_SEARCH_PACKET_STATUS_HEAD;
			u32Index = 0;
			break;
		}   
	}

	return 0;
}

void CComWatchThread::WitleafRcvCmd()//unsigned char * puchBuff, unsigned int u32Size)
{
	unsigned int u32RcvLen;
	unsigned int u32CacheLen;
	unsigned int u32RemainLen;
	unsigned int u32Index;

	bool bValidePack = TRUE;

	unsigned char pu8CacheBuff[WITLEAF_MAX_FRAME_CACHE_LEN];

	u32RcvLen = WitleafGetUartRxBuffLen();

	if ( u32RcvLen < WITLEAF_MIN_FRAME_LEN )
	{
		return;
	}
	else if ( u32RcvLen > WITLEAF_MAX_FRAME_CACHE_LEN )
	{
		u32RcvLen = WITLEAF_MAX_FRAME_CACHE_LEN;
	}

	u32CacheLen = WitleafGetUartRxStr(pu8CacheBuff, u32RcvLen);

	u32Index = 0;

	while ( (u32CacheLen >= WITLEAF_MIN_FRAME_LEN) && ( true == bValidePack))
	{
		bValidePack = WitleafUnpackUartData(&pu8CacheBuff[u32Index], u32CacheLen, &gtWitleafPacket, &u32RemainLen);
		
		if ( bValidePack)
		{	
			if (m_bModeflag == FALSE)
			{
				m_pcMonitorDlg->RcvData(gtWitleafPacket);
			}
			else
			{
				m_pcSleepMonitorDlg->RcvData(gtWitleafPacket);
			}
		}

		u32Index = u32RcvLen - u32RemainLen;
		u32CacheLen = u32RemainLen;		
	}

	if ( 0 != u32CacheLen )
	{
		WitleafRestoreUartRxStr(u32CacheLen);
	}
}

void CComWatchThread::SetStopFlag(bool bFlag)
{
	m_bStopFlag = bFlag;
}
