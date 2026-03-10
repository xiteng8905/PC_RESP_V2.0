#ifndef __SRCH_PULSE_H__
#define __SRCH_PULSE_H__
//#include "DataType.h"
/*!!!
*************************************************************
	相关数据类型定义
*************************************************************
*/
typedef signed char				INT8;
typedef signed short			INT16;
typedef signed int				INT32;
typedef unsigned char			UINT8;
typedef unsigned short			UINT16;
typedef unsigned int			UINT32;
typedef volatile signed char	VINT8;
typedef volatile signed short	VINT16;
typedef volatile signed int		VINT32;
typedef volatile unsigned char	VUINT8;
typedef volatile unsigned short	VUINT16;
typedef volatile unsigned int	VUINT32;
typedef float            		FLOAT;
typedef double           		DOUBLE;

#define Sample_Rate		250	//???
#define SLOP_THRD		33	//[%]????????
#define SRCH_WAVE_LEN	300	//?????????
#define SRCH_THRD		30	//???????
///////////////////////////////////////////////////////////////
//定义波形结构体
///////////////////////////////////////////////////////////////
typedef struct{
	INT32 amp;		//[LSB]波形采样值
	INT32 slp;		//斜率：当前点波形值-其前第二点的波形值
	INT32 pos;		//位置：以采样率计
}PULWV;

/****************************************************************************************************
  接口变量
****************************************************************************************************/
extern UINT8 PulPeakTag;	//从当前点向前倒溯的峰点位置，0xFF标识为无效值
extern UINT8 PulSlopTag;	//从当前点向前倒溯的冲点位置，0xFF标识为无效值
extern UINT8 PulFootTag;	//从当前点向前倒溯的脚点位置，0xFF标识为无效值
extern UINT8 PulValyTag;	//从当前点向前倒溯的谷点位置，0xFF标识为无效值
extern UINT16 RtPeriod;		//实时脉搏周期

/****************************************************************************************************
  接口函数
****************************************************************************************************/
void SrchPulse(INT32 wv);
void ResetSrchPulse(void);

#endif
