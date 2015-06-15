/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   libg7112aac.cpp
 * Author: Wellsen
 * 
 * Created on 2015年4月11日, 上午10:57
 */

#include "libg7112aac.h"
#include "g7712aac.h"

EASY_AAC_ENC_HANDLE libg7112aac_open()
{
    g7712aac *encoder = new g7712aac();
    encoder->init();
    return encoder;
}

int libg7112aac_encode(EASY_AAC_ENC_HANDLE handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
    if(handle == NULL)
    {
        return -1;
    }
    return ((g7712aac*)handle)->aac_encode(inbuf, inlen, outbuf, outlen);
}

void libg7112aac_close(EASY_AAC_ENC_HANDLE handle)
{
    if(handle != NULL)
    {
        delete ((g7712aac*)handle);
    }
}


