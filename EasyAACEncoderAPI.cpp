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

Easy_API EasyAACEncoder_Handle Easy_APICALL Easy_AACEncoder_Init(unsigned int u32AudioCodec, unsigned int u32AudioSamplerate, unsigned int u32AudioChannel)
{
    G7ToAac *encoder = new G7ToAac();
    //encoder->init();

	InAudioInfo info(u32AudioCodec , u32AudioSamplerate , u32AudioChannel );
	encoder->init(info);


    return encoder;
}

Easy_API int Easy_APICALL Easy_AACEncoder_Encode(EasyAACEncoder_Handle handle, unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
    if(handle == NULL)
    {
        return -1;
    }
    return ((G7ToAac*)handle)->aac_encode(inbuf, inlen, outbuf, outlen);
}

Easy_API void Easy_APICALL Easy_AACEncoder_Release(EasyAACEncoder_Handle handle)
{
    if(handle != NULL)
    {
        delete ((G7ToAac*)handle);
    }
}


