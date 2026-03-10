#include "stdafx.h"
/*
******************************************************
	Âö²«²¨ËÑË÷

	1.0    2024-08
******************************************************
*/

#include <string.h>
#include "SrchPulse.h"

UINT8 PulPeakTag = 0xFF;
UINT8 PulSlopTag = 0xFF;
UINT8 PulFootTag = 0xFF;
UINT8 PulValyTag = 0xFF;

UINT16 RtPeriod = 0;
INT32 RtPulAmp = 0;
UINT8 reActPeriod = 47;

UINT16 posBufPeak = 0;
UINT16 posBufSlop = 0;
UINT16 posBufFoot = 0;
UINT16 posBufValy = 0;

PULWV PulPeak = {0};
PULWV PulSlop = {0};
PULWV PulFoot = {0};
PULWV PulValy = {0};

INT32 srchThrd = SRCH_THRD;
UINT8 srchPhase = 0;
INT32 posPrvPeak = 0;

INT32 sampTime = 0;
PULWV currWv = {0};
PULWV prv1Wv = {0};
PULWV prv2Wv = {0};

UINT8 srchHead = 0;
UINT8 srchTail = 0;
PULWV srchBuff[SRCH_WAVE_LEN] = {0};

/*!
******************************************************
??:????
????:wv:??????
????:?
******************************************************
*/
void SrchPulse(INT32 wv)
{
	INT32 num = 0;
	INT32 curpos;
	PULWV backdata;

	sampTime++;

	//?????
	currWv.pos = sampTime;
	currWv.amp = wv;
	if(0 == prv1Wv.pos)
	{
		currWv.slp = 0;
	}
	else if(0 == prv2Wv.pos)
	{
		currWv.slp = currWv.amp - prv1Wv.amp;
	}
	else
	{
		currWv.slp = currWv.amp - prv2Wv.amp;
	}
	prv2Wv = prv1Wv;
	prv1Wv = currWv;

	//????
	srchBuff[srchTail] = currWv;
	curpos = srchTail;
	srchTail++;
	if(SRCH_WAVE_LEN <= srchTail)
	{
		srchTail = 0;
	}
	if(srchHead == srchTail)
	{
		srchHead++;
		if(SRCH_WAVE_LEN <= srchHead)
		{
			srchHead = 0;
		}
	}

	//??????
	PulPeakTag = 0xFF;
	PulSlopTag = 0xFF;
	PulFootTag = 0xFF;
	PulValyTag = 0xFF;

	if(posPrvPeak + 3*Sample_Rate < currWv.pos)
	{
		srchThrd = SRCH_THRD;
	}
	
	//????
	if(0 == srchPhase)
	{
		//????
		if(PulValy.amp > currWv.amp)
		{ 
			PulValy = currWv;
			posBufValy = curpos;
		} 
		else if(PulValy.amp + srchThrd > currWv.amp)
		{
			//????????????,????
		}
		else
		{
			//??????????????
			//???????:?????????????
			PulValyTag = currWv.pos - PulValy.pos;	//??????
			
			//??????:1
			srchPhase = 1;
			
			//?????
			PulPeak = currWv;
			PulFoot = currWv;
			PulSlop = currWv;
			posBufSlop = curpos;
			//?????????????
			PulSlop.slp = 0;
		}
	}
	else
	{
		//????
		if(PulPeak.amp < currWv.amp)
		{
			//?????
			PulPeak = currWv;

			//????????????????????
			if(PulSlop.slp < currWv.slp)
			{
				PulSlop = currWv;
				//???????????????
				posBufSlop = curpos;
			}
		}
		else if(PulPeak.amp < currWv.amp + srchThrd)
		{
			//????????????,????
		}
		else
		{
			//??????????????,??????

			if(reActPeriod < PulPeak.pos - posPrvPeak)
			{
				//??????????????,?????????
				//??,??????,??,????????
				//??????????????????????
				//???????????
				posBufFoot = posBufSlop;
				//?????????
				backdata = PulValy;
				num = 0;
				while(3 > num)
				{
					//??????
					if(0 == posBufFoot)
					{
						posBufFoot = SRCH_WAVE_LEN-1;
					}
					else
					{
						posBufFoot--;
					}
					//??????????
					if(posBufFoot == posBufValy)
					{
						//?????,????????
						break;
					}
					else
					{
						//?????
						backdata = srchBuff[posBufFoot];
						if(backdata.slp < PulSlop.slp*SLOP_THRD/100
							|| backdata.slp <= 0)
						{
							//????????????????????????
							//??????????????????
							num++;
						}
						else
						{
							num = 0;
						}
					}
				}
				
				//?????????
				PulFoot = backdata;

				//?????????
				RtPulAmp = PulPeak.amp - PulFoot.amp;
				srchThrd = RtPulAmp/4;
				//????????????
				RtPeriod = (UINT16)(PulPeak.pos - posPrvPeak);

				if(2*srchThrd < RtPulAmp && reActPeriod/3 < PulPeak.pos - PulFoot.pos)
				{
					PulPeakTag = currWv.pos - PulPeak.pos;
					PulSlopTag = currWv.pos - PulSlop.pos;
					PulFootTag = currWv.pos - PulFoot.pos;
				}

				//??????????
				posPrvPeak = PulPeak.pos;
			}

			//?????
			srchPhase = 0;
			
			//?????
			PulValy = currWv;
			
			//?????????,??????
			srchHead = 0;
			srchTail = 0;
			posBufValy = 0;
			
			return;
		}
	}
}


void ResetSrchPulse(void)
{
	PulPeakTag = 0xFF;
	PulSlopTag = 0xFF;
	PulFootTag = 0xFF;
	PulValyTag = 0xFF;
	RtPeriod = 0;
	RtPulAmp = 0;
	posBufPeak = 0;
	posBufSlop = 0;
	posBufFoot = 0;
	posBufValy = 0;
	srchThrd = SRCH_THRD;
	srchPhase = 0;
	posPrvPeak = 0;
	sampTime = 0;
	memset(&PulPeak, 0, sizeof(PulPeak));
	memset(&PulSlop, 0, sizeof(PulSlop));
	memset(&PulFoot, 0, sizeof(PulFoot));
	memset(&PulValy, 0, sizeof(PulValy));
	memset(&currWv, 0, sizeof(currWv));
	memset(&prv1Wv, 0, sizeof(prv1Wv));
	memset(&prv2Wv, 0, sizeof(prv2Wv));
	srchHead = 0;
	srchTail = 0;
	memset(srchBuff, 0, sizeof(srchBuff));
}





