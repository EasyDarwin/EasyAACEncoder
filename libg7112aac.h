/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   libg7112aac.h
 * Author: Wellsen
 *
 * Created on 2015年4月11日, 上午10:57
 */

#ifndef LIB_G7112AAC_H
#define	LIB_G7112AAC_H

typedef void* EASY_AAC_ENC_HANDLE;

EASY_AAC_ENC_HANDLE libg7112aac_open();

int libg7112aac_encode(EASY_AAC_ENC_HANDLE handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

void libg7112aac_close(EASY_AAC_ENC_HANDLE handle);

#endif	/* LIB_G7112AAC_H */

