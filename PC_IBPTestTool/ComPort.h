// ComPort.h: interface for the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPORT_H__60626E55_013F_46A8_BB37_287D71A1062E__INCLUDED_)
#define AFX_COMPORT_H__60626E55_013F_46A8_BB37_287D71A1062E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComPort
{
public:
	bool WaitRevEvent();
	HANDLE		m_hComHandle;
    OVERLAPPED	m_olSend;
    OVERLAPPED	m_olRecv;
	CComPort();
	CComPort(int nCom);
	virtual ~CComPort();

// Attributes
    HANDLE GetHandle() { return m_hComHandle; }

// Operations
    BOOL Initialize();
    BOOL Recv(BYTE *buf, DWORD maxsize, DWORD &size);
    BOOL Send(BYTE *buf, DWORD size);
	OVERLAPPED GetRevEvent()    { return m_olRecv; }
protected:
// Attributes
	
	int m_nCom;
};

#endif // !defined(AFX_COMPORT_H__60626E55_013F_46A8_BB37_287D71A1062E__INCLUDED_)
