#ifndef _WITLEAFRESPLIB_H_
#define _WITLEAFRESPLIB_H_

typedef enum
{
	WL_RESP_PATIENT_TYPE_ADULT,
	WL_RESP_PATIENT_TYPE_NEONATE,
	WL_RESP_PATIENT_TYPE_PED,

	WL_RESP_PATIENT_TYPE_MAX

} WL_RESP_PATIENT_TYPE_LIST;

typedef enum
{
	WL_RESP_BREATH_SENSITIVITY_1 = 0,
	WL_RESP_BREATH_SENSITIVITY_2,
	WL_RESP_BREATH_SENSITIVITY_3,
	WL_RESP_BREATH_SENSITIVITY_4,
	WL_RESP_BREATH_SENSITIVITY_5,
	
	WL_RESP_BREATH_SENSITIVITY_MAX
	
} WL_RESP_BREATH_SENSITIVITY_LIST;

void WLRespVersion(unsigned char * pu8MainVersion, unsigned char * pu8SubVersion);
void WLRespInit(void);
unsigned char WLRespSetPatientType(WL_RESP_PATIENT_TYPE_LIST tPatientType);
unsigned char WLRespSetBreathSensitivity(WL_RESP_BREATH_SENSITIVITY_LIST tSensitivity);
void WLRespProcessData(signed short i16RespData, unsigned char u8RWaveFlag);
void WLRespGetResult(unsigned char * pu8RespDetected, unsigned char * pu8CvaDetected, unsigned short * pu16RespRate);

#endif
