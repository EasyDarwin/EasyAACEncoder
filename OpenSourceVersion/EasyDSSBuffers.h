/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#ifndef _TOOLS_H_
#define _TOOLS_H_

#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#include <guiddef.h>
#include <time.h>
#else
#include <pthread.h>
#include <sys/time.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

#include <errno.h>
#if (defined(_WIN32)) //windows
//#define WIN32
#ifndef DLL_EXPORT
#define JD_API  extern "C"__declspec(dllimport)
#else
#define JD_API  extern "C"__declspec(dllexport)
#endif
#elif defined(__linux__) //linux
#define __stdcall 
#define CALLBACK 
#define JD_API  extern "C"
#define WINAPI
typedef int HANDLE;
typedef int HWND;
#endif

#ifdef _WIN32
#include <Windows.h>
#endif
#include <string>
#include <stdlib.h>
#include <map>

using namespace std;

#define PFRAME             0x00
#define IFRAME             0x01

const int iBufLen = 1024 * 128;
const int iRecvBufLen = iBufLen * 2;
const int iMaxParamterNum = 128;
const int iBufNum = 10;
const int MAX_BUF_NUM = 50;
const int iCharBufLen = 64;
const char BoundTag[] = "\r\n"; //帧间隔标识
const int BoundTagLen = sizeof (BoundTag) - 1; //帧间隔标识长度
//const char IFrameTag[]  = "HISI264I";//录像I帧标志
//const char PFrameTag[]  = "HISI264P";//录像P帧标志
//const int FrameTagLen = sizeof(IFrameTag) - 1;// 录像帧标志长度

const int MaxWaitTime = 3000; //超时时间
const int MaxCameraNum = 24; //最大摄像机数量

const int AUDIO_BUFFER_SIZE = 960; //定义播放的每一片缓冲都是800个字节
const int MAX_AUDIO_BUF = 4; //播放缓冲的通知索引
const int BUFFERNOTIFYSIZE = AUDIO_BUFFER_SIZE;/*8192*//*192000*/ //缓冲通知位置的大小，请参见DirectSound应用程序开发快速入门
const int SAMPLE_RATE = 8000;/*44100*/ //pcm 的采样率  8k
const int N_CHANNEL = 1;/*2*/   //PCM 声道数 单通道
const int BITS_PER_SAMPLE = 16;  //每个采样点的比特数
const int CHANNEL = 1;
const int SAMPLES_PER_SECOND = 8000;
const int SIZE_AUDIO_FRAME = 960;

#ifdef WIN32
const GUID GUID_YUY2 = {0xc68e1552, 0x4a3f, 0x4706,
    {0xb2, 0xd4, 0x83, 0x41, 0x4f, 0x15, 0xdc, 0xcc}};
//typedef char int8_t;
//typedef unsigned char uint8_t;
//typedef short int16_t;
//typedef unsigned short uint16_t;
//typedef int int32_t;
//typedef unsigned int uint32_t;
//typedef __int64 int64_t;
//typedef unsigned __int64 uint64_t;
#else
typedef pthread_mutex_t CRITICAL_SECTION;
#define InitializeCriticalSection pthread_mutex_init 
#define DeleteCriticalSection pthread_mutex_destroy 
#define EnterCriticalSection pthread_mutex_lock
#define LeaveCriticalSection pthread_mutex_unlock
//typedef void* LPVOID;
//typedef unsigned long DWORD;
//#define CloseHandle close
#define Sleep(x) usleep(x*1000)
//#define closesocket close
//#define TRUE true
//#define FALSE false
//typedef bool BOOL;

typedef struct
{
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    bool manual_reset;
    bool signaled;
} THANDLE, *PHANDLE;

#define INFINITE 0xFFFFFFFF
#define WAIT_TIMEOUT 0x00000102L
#define WAIT_OBJECT_0 0
#endif

#ifndef TRACE
#define	TRACE printf
#endif

/*!
 \brief H264码流回调函数指针
 \param iPlayHandle 播放句柄
 \param sData 数据缓冲区
 \param iLen 数据长度
 \param iDataType 数据类型 0 - 实时数据流, 1 - 录像数据流, 2 - 本地采集的音频流, 3 - 设备发过来的音频流
*/
typedef void(CALLBACK* fVideoDataCallBack)(int iPlayHandle, char* sData, int iLen, int iDataType, void* pUserData);

/*!
 \brief 告警信息回调函数指针
 \param pAlarmInfo 告警信息T_JD_AlarmInfo结构体指针
 \param pUserData 用户数据
*/
typedef void(CALLBACK* fMessageCallBack)(void* pAlarmInfo, void* pUserData);

typedef struct
{
    char *start;
    size_t length;
    int frame_type;
    int frame_index;
    int channel;
} buffer_t;

typedef struct _buffers_t
{
    int rear;
    int front;
    int bufnum;
    int fps;
    CRITICAL_SECTION cs;
    buffer_t buf[MAX_BUF_NUM];
    fVideoDataCallBack pOnVideoData; // 数据回调函数指针
    void* pUserData; //回调函数用户数据

    _buffers_t()
    {
        pOnVideoData = NULL;
        pUserData = NULL;
    }

} buffers_t;

int init_buffers(buffers_t * bufs, int bufsize, int bufnum);

int free_buffers(buffers_t *bufs);

int buffers_get_data(void *data, unsigned int *length, buffers_t * bufs, int *type, int *channel, int *frame_index);

int buffers_put_data(void *data, unsigned int length, buffers_t * bufs, int type, int channel, int frame_index);

void buffers_clear_data(buffers_t * bufs);

#endif
