/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   libEasyAACEncoder.cpp
 * Author: Wellsen@easydarwin.org
 * 
 * Created on 2015年4月11日, 上午10:57
 */

#include "EasyAACEncoderAPI.h"
#include "EasyAACEncoder.h"
#include "condef.h"

Easy_API EasyAACEncoder_Handle Easy_APICALL Easy_AACEncoder_Init(InitParam initPar)
{
    G7ToAac *encoder = new G7ToAac();
	InAudioInfo info(initPar );
	bool ret = encoder->init(info);
	if (!ret)
	{
		SAFE_DELETE_OBJ(encoder);
	}
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


