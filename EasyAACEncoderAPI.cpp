/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   libEasyAACEncoder.cpp
 * Author: Wellsen
 * 
 * Created on 2015年4月11日, 上午10:57
 */

#include "EasyAACEncoderAPI.h"
#include "EasyAACEncoder.h"

EasyAACEncoder_Handle Easy_AACEncoder_Create()
{
    g7712aac *encoder = new g7712aac();
    encoder->init();
    return encoder;
}

int Easy_AACEncoder_Encode(EasyAACEncoder_Handle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
    if(handle == NULL)
    {
        return -1;
    }
    return ((g7712aac*)handle)->aac_encode(inbuf, inlen, outbuf, outlen);
}

void Easy_AACEncoder_Release(EasyAACEncoder_Handle handle)
{
    if(handle != NULL)
    {
        delete ((g7712aac*)handle);
    }
}


