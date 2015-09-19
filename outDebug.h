#ifndef _OUTDEBUG_H
#define _OUTDEBUG_H



#define DBG_MSG_BUFF_SIZE 3000
#define FILE_NAME "-EasyAAC-"

#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>

#define INFO_USE(fmt, ...) \
{ \
	TCHAR traceBuffer[DBG_MSG_BUFF_SIZE]; \
	_stprintf_s(traceBuffer, _T(FILE_NAME) _T(" :INFO: ") _T(__FUNCTION__) _T("<%d>: ") _T(fmt) _T("\n"), __LINE__, ##__VA_ARGS__); \
	OutputDebugString(traceBuffer); \
}


#define INFO_CHOOSEUSE(fmt, ...)	{INFO_USE(fmt, ##__VA_ARGS__);}

#define INFO_D(OUT,fmt, ...)\
{ \
	if(OUT)\
	{\
	INFO_CHOOSEUSE(fmt, ##__VA_ARGS__);\
	}\
}




#define AAC_DEBUG 0

#endif