#ifndef RESPPACKID_H_H
#define RESPPACKID_H_H

#define MAX_COUNT 1124
#define INVALID_VALUE 10000
#define DEFAULT_VALUE 100
#define SPO2_DEFAULT_VALUE 250
#define MAX_COUNT 1124

enum PACKET_RESP_
{
	PARAM_SPO2=03,	
	PARAM_RESP=06	
};

enum PACKET_RESP_ID_LIST
{
	PACKET_ID_START = 0,
	CMD_RESP_START = 0x01,
	CMD_RESP_MODULE_INFO ,
	CMD_RESP_MODULE_WORK ,
	CMD_RESP_BREATH_SENSITIVITY,
	CMD_RESP_SET_PATIENT = 0x10,
	CMD_RESP_SET_BASEPRESS = 0x11,
	CMD_RESP_SET_CALIBRATION = 0x20,
	CMD_RESP_RESET_CALIBRATION = 0x21,
	CMD_RESP_CHECK_LEAKAGE  = 0x22,
	CMD_RESP_RESET_MODULE = 0x30,
	CMD_RESP_OK_CALIBRATION  = 0x40,

	MSG_RESP_MODULE_ANSWER = 0x80,
	MSG_RESP_REQUEST_START = 0x81,
	MSG_RESP_MODULE_INFO ,
	MSG_RESP_RESULT_STATUS ,
	MSG_RESP_WAVE_DATA ,
	MSG_RESP_LEAKAGE_STATUS ,
};

typedef enum _WITLEAF_RESPONSE_LIST
{
	WITLEAF_RESPONSE_ANSWER			           = 0x80,     //通用命令应答包
	WITLEAF_RESPONSE_CONNECT_ACK 	           = 0x81,     //上电握手请求数据包
	WITLEAF_RESPONSE_MOUDLE_INFO               = 0x82,     //软件、算法及通讯协议版本
	WITLEAF_RESPONSE_SELF_TEST_INFO 	       = 0x83,     //模块自检结果数据包
	WITLEAF_RESPONSE_RT_PLS 		           = 0x84,     //实时波形数据包
	WITLEAF_RESPONSE_RESULT 		           = 0x85,     //计算结果及状态数据包

	WITLEAF_RESPONSE_MAX
} WITLEAF_RESPONSE_LIST;

typedef enum _WITLEAF_CMD_LIST
{
	WITLEAF_CMD_CONNECT_ACK     			= 0x01,      //上电握手命令帧ID
	WITLEAF_CMD_REQUEST_MODULE_INFO 		= 0x02,	     //查询模块信息帧ID，包括版本信息、算法信息、通讯协议信息
	WITLEAF_CMD_REQUEST_SELF_TEST_RESULT	= 0x03,      //自检结果查询
	WITLEAF_CMD_SET_PATIENT_MODE			= 0x04,      //设置病人类型
	WITLEAF_CMD_SET_AVERAGE_TIME			= 0x05,      //设置计算灵敏度

	WITLEAF_CMD_UPDATE				= 0x7F,

	WITLEAF_CMD_MAX
} WITLEAF_CMD_LIST;

typedef enum _SYS_REPORT_STATUS
{
	SYS_ALL_NORMAL          = 0x00,         //系统一切正常；
	SYS_HYPOPERFUSION   = 0X01,         // 低灌注: '1'，表示低灌注；若为'0'，则表示正常
	SYS_MOVEMEMT_DISTURB  = 0X02,       // 运动干扰: '1'，表示运动干扰；若为'0'，则正常
	SYS_HYPER_MOVEMEMT_DISTURB = 0x04,  // 过度运动干扰: '1'，表示过度运动干扰；若为'0'，则正常
	SYS_SEARCH_PULSE = 0X08,            // 搜索脉搏波: '1'，表示搜索脉搏波；若为'0'，则表示正常
	SYS_LONGTIME_SEARCH_PULSE_NO = 0x10,// 搜索脉搏波时间过长或无脉搏波
	SYS_LED_DITACHED = 0x20,            // 探头未接:'1'，表示探头未接；若为'0'，则表示正常。
	SYS_FIGURE_NOT_IN = 0x40,           // 手指未接入:'1'，表示手指未接入；若为'0'，则表示正常。
	SYS_LED_ERROR = 0X80,               // 探头故障:'1', 探头故障；若为'0',则表示正常。
	SYS_HARDWARE_ERROR = 0x01,          // 硬件错误:'1', 硬件错误；若为'0',则表示正常
	SYS_BACKLIGHT_TOOBRIGHT = 0X02,     // 背景光太强:'1', 背景光太强；若为'0',则表示正常
	SYS_LED_UNMATCHING = 0x04           // 探头不匹配:'1', 探头不匹配；若为'0',则表示正常
}SYS_REPORT_STATUS;


#define INVALID_PULSE_WAVE  0xFF
#define INVALID_SPO2        0x7F
#define INVALID_PLUSE_RARE  0x1FF

#endif