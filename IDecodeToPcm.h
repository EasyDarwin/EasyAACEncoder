/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#pragma once

#ifndef _IDECODETOPCM_H
#define _IDECODETOPCM_H

#include "EasyAACEncoderAPI.h"

#define USE_SHOUT_G711PACK 1

#if USE_SHOUT_G711PACK
#define G711_ONE_LEN 160
#define G711_ONE_OFFSET 0

#else
#define G711_ONE_LEN 164
#define G711_ONE_OFFSET 4
#endif

const int CON_PCM_SIZE = 320;

class audio_buffer;

class InAudioInfo
{
public:
	InAudioInfo();
	InAudioInfo(InitParam param);
	~InAudioInfo(){;}

	unsigned int CodecType()
	{
		return m_initparam.ucAudioCodec;
		//return m_u32AudioCodec;
	}
	unsigned int Samplerate()
	{
		return m_initparam.u32AudioSamplerate;
		//return m_u32AudioSamplerate;
	}
	unsigned int Channel()
	{
		return m_initparam.ucAudioChannel;
		//return m_u32AudioChannel;
	}
	unsigned int PCMBitSize()
	{
		return m_initparam.u32PCMBitSize;
		//return m_nPCMBitSize;
	}
	unsigned char G726RateBits()
	{
		return m_initparam.g726param.ucRateBits;
	}
private:
	unsigned int m_u32AudioCodec;
	unsigned int m_u32AudioSamplerate;
	unsigned int m_u32AudioChannel;

	unsigned int m_nPCMBitSize;

	InitParam m_initparam;
};
//----------------------------------------------------------
class IDecodeToPcm
{
public:
	IDecodeToPcm(void);
	virtual ~IDecodeToPcm(void);

public:
	virtual int Init(InAudioInfo info)=0;
	virtual int Decode( unsigned char* outbuf, unsigned int* outlen , unsigned char* inbuf, unsigned int inlen)=0;
	virtual int PCMSize()=0;
	virtual int G7FrameSize()=0;
};
//----------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------
class DecodeToPcmBase:public IDecodeToPcm
{
public:
	DecodeToPcmBase();
	virtual ~DecodeToPcmBase();

	int Init(InAudioInfo info);

public:
	virtual int Decode(unsigned char* outbuf, unsigned int* outlen , unsigned char* inbuf, unsigned int inlen);
	virtual int PCMSize();
	virtual int G7FrameSize();

	virtual unsigned short DecodeOneChar(unsigned char data)=0;

private:
	int m_g7FrameSize;
};

#endif

