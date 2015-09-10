/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef EasyAACEncoder_API_H
#define	EasyAACEncoder_API_H

#ifdef _WIN32
#define Easy_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#else
#define Easy_API
#define Easy_APICALL 
#endif

#define EasyAACEncoder_Handle void*

#ifdef __cplusplus
extern "C"
{
#endif
	/* 创建HLSSession  返回为句柄值 */
	Easy_API EasyAACEncoder_Handle Easy_APICALL Easy_AACEncoder_Create(unsigned long sampleRate, unsigned int numChannels);


	Easy_API int Easy_APICALL Easy_AACEncoder_Encode(EasyAACEncoder_Handle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

	Easy_API void Easy_APICALL Easy_AACEncoder_Release(EasyAACEncoder_Handle handle);

#ifdef __cplusplus
}
#endif

#endif	/* EasyAACEncoder_API_H */

