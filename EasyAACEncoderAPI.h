/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef EasyAACEncoder_API_H
#define	EasyAACEncoder_API_H

typedef void* EASY_AAC_ENC_HANDLE;

EASY_AAC_ENC_HANDLE libg7112aac_open();

int libg7112aac_encode(EASY_AAC_ENC_HANDLE handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

void libg7112aac_close(EASY_AAC_ENC_HANDLE handle);

#endif	/* EasyAACEncoder_API_H */

