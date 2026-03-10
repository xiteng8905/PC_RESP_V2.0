// ComPort.cpp: implementation of the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComPort.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComPort::CComPort()
{
	m_nCom = 0;
}

CComPort::CComPort(int nCom)
{
	m_nCom = nCom;	
}

CComPort::~CComPort()
{
    if (m_olRecv.hEvent)
        CloseHandle(m_olRecv.hEvent);
    if (m_olSend.hEvent)
        CloseHandle(m_olSend.hEvent);
    if (m_hComHandle != INVALID_HANDLE_VALUE)
        CloseHandle(m_hComHandle);
}

//
BOOL CComPort::Initialize()
{
    COMMTIMEOUTS commtimeouts;
    DCB   dcb;

    memset(&m_olRecv, 0, sizeof(OVERLAPPED));
    m_olRecv.hEvent     = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (NULL == m_olRecv.hEvent)
        return FALSE;

    memset(&m_olSend, 0, sizeof(OVERLAPPED));
    m_olSend.hEvent     = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (NULL == m_olSend.hEvent)
    {
        CloseHandle(m_olRecv.hEvent);
        return FALSE;
    }
//	ddddd

    // create com file
	TCHAR szCom[16];
	switch ( m_nCom) {
		case 0:
			_sntprintf(szCom, 15, _T("%s"), _T("COM1"));
			break;
		case 1:
			_sntprintf(szCom, 15, _T("%s"), _T("COM2"));
			break;
		case 2:
			_sntprintf(szCom, 15, _T("%s"), _T("COM3"));
			break;
		case 3:
			_sntprintf(szCom, 15, _T("%s"), _T("COM4"));
			break;
		default:
			_sntprintf(szCom, 15, _T("%s"), _T("COM1"));
			break;
	}

    m_hComHandle = CreateFile(szCom,
                    GENERIC_READ | GENERIC_WRITE,
                    0,                              // exclusive access
                    NULL,                           // no security attrs
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL |
                    FILE_FLAG_OVERLAPPED,           // overlapped I/O
                    NULL);
	if (m_hComHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

    // get any early notifications
    SetCommMask(m_hComHandle, EV_RXCHAR);

    // setup device buffers
    SetupComm(m_hComHandle, 4800, 4800);

    // purge any information in the buffer
    PurgeComm(m_hComHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

    // set up for overlapped I/O
    commtimeouts.ReadIntervalTimeout        = MAXDWORD;
    commtimeouts.ReadTotalTimeoutMultiplier = 0;
    commtimeouts.ReadTotalTimeoutConstant   = 0;

    commtimeouts.WriteTotalTimeoutMultiplier = 0;
    commtimeouts.WriteTotalTimeoutConstant   = 0;
    SetCommTimeouts(m_hComHandle, &commtimeouts);

    GetCommState(m_hComHandle, &dcb);

    dcb.DCBlength = sizeof(DCB);
//    dcb.BaudRate  = CBR_256000;
	dcb.BaudRate = CBR_115200;
    dcb.fBinary   = TRUE;
	dcb.fParity   = FALSE;			//new
//	dcb.fParity   = TRUE;			//old
    dcb.ByteSize  = 8;
	//dcb.Parity    = NOPARITY;	//new;
	dcb.Parity    = ODDPARITY;	//old
    dcb.StopBits  = ONESTOPBIT;          

    // setup hardware flow control
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl  = DTR_CONTROL_DISABLE;

    dcb.fOutxCtsFlow = FALSE;
    dcb.fRtsControl  = RTS_CONTROL_DISABLE;

    dcb.fDsrSensitivity = FALSE;
    dcb.fOutX = FALSE;
    dcb.fInX  = FALSE;
    dcb.fNull = FALSE;

    // other various settings
    SetCommState(m_hComHandle, &dcb);

    return TRUE;
}

// Arguments:
//      buf - 存放串口数据的缓冲区
//      maxsize - 能够读出的最大字节数
//      size - 实际读出的字节数
//  Return:
//      TURE-接收成功，FALSE-失败
//  Description:
//    使用异步方式后台接收数据，ReadFile 会立刻返回，通过
//    查询异步接收状态判断发送是否成功，GetOverlappedResult 这里的工
//    作方式是直到接收成功或者遇到错误才返回，该函数返回的字节个数是
//    不定的，数据帧的判断由应用程序处理
BOOL CComPort::Recv(BYTE *buf, DWORD maxsize, DWORD &size)
{
    if (buf == NULL || maxsize == 0)
        return FALSE;
        
	DWORD event, error, ecode, readbytes;
	COMSTAT cs;

	ClearCommError(m_hComHandle, &error, &cs);

	// 等待串口事件到来
	if (!WaitCommEvent(m_hComHandle, &event, &m_olRecv))
    {
        ecode = GetLastError();
		if (ecode != ERROR_IO_PENDING) // 等待串口事件是否在异步进行
        {
			ClearCommError(m_hComHandle, &error, &cs);
			return FALSE;
        }
        while (!GetOverlappedResult(m_hComHandle, &m_olRecv, &size, FALSE))
        {
            ecode = GetLastError();
			if (ecode != ERROR_IO_INCOMPLETE)
            {
                ClearCommError(m_hComHandle, &error, &cs);
				return FALSE;
            }
        }
	}

	//缓冲区中有数据到达
	if ((event&EV_RXCHAR) != EV_RXCHAR)
//	{
 //       Beep(2000,1000)  ;
		return FALSE;
//	}
	ClearCommError(m_hComHandle, &error, &cs);
    readbytes = cs.cbInQue; // 缓冲区中字节数

    if (readbytes == 0) // 没有数据
        return FALSE;

    // 超过了最大结束数
    if (readbytes > maxsize)
        readbytes = maxsize;

	if (!ReadFile(m_hComHandle, buf, readbytes, &size, &m_olRecv))
    {
        // 正在异步读取数据
        ecode = GetLastError();
        if (ecode != ERROR_IO_PENDING)
        {
            ClearCommError(m_hComHandle, &error, &cs);
            return FALSE;
        }
        while (!GetOverlappedResult(m_hComHandle, &m_olRecv, &size, FALSE))
        {
            if (GetLastError() != ERROR_IO_INCOMPLETE)
            {
                ClearCommError(m_hComHandle, &error, &cs);
                return FALSE;
            }
        }
	}

    return TRUE;
}

// Arguments:
//      buf - 发送缓冲区
//      size - 发送字节数 
BOOL CComPort::Send(BYTE *buf, DWORD size)
{
    if (buf == NULL || size == 0)
        return FALSE;

    DWORD error, ecode, writebytes;
    COMSTAT cs;

    if (!WriteFile(m_hComHandle, buf, size, &writebytes, &m_olSend))
    {
        ecode = GetLastError();
        if (ecode != ERROR_IO_PENDING)
        {
            ClearCommError(m_hComHandle, &error, &cs);
            return FALSE;
        }
        while (!GetOverlappedResult(m_hComHandle, &m_olSend, &writebytes, TRUE))
        {
            ecode = GetLastError();
            if (ecode != ERROR_IO_INCOMPLETE)
            {
                ClearCommError(m_hComHandle, &error, &cs);
                return FALSE;
            }
        }
    }
    return TRUE;
}

bool CComPort::WaitRevEvent()
{
	DWORD event, error, ecode ;
	COMSTAT cs;
	ResetEvent(m_olRecv.hEvent);
	// 等待串口事件到来
	if (!WaitCommEvent(m_hComHandle, &event, &m_olRecv))
        {
        ecode = GetLastError();
        if (ecode != ERROR_IO_PENDING) // 等待串口事件是否在异步进行
        {
            ClearCommError(m_hComHandle, &error, &cs);
            return FALSE;
        }
 /*       while (!GetOverlappedResult(m_hComHandle, &m_olRecv, &size, FALSE))
        {
            ecode = GetLastError();
            if (ecode != ERROR_IO_INCOMPLETE)
            {
                ClearCommError(m_hComHandle, &error, &cs);
                return FALSE;
            }
        }     */
	}
  //      if ((event&EV_RXCHAR) != EV_RXCHAR)
   //         return FALSE;
        return TRUE;

}
