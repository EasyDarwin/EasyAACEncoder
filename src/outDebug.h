/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#ifndef _OUTDEBUG_H
#define _OUTDEBUG_H



#define DBG_MSG_BUFF_SIZE 3000
#define FILE_NAME "-EasyAACEncoder-"

#ifndef __linux__
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

#else
#define INFO_D(OUT,fmt, ...)\
{ \
	if(OUT)\
	{\
	printf(fmt, ##__VA_ARGS__);\
	}\
}
#endif


#define AAC_DEBUG 0

#endif
