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

class IDecodeToPcm
{
public:
	IDecodeToPcm(void);
	virtual ~IDecodeToPcm(void);

public:
	virtual int Init()=0;
	virtual int Decode( unsigned char* outbuf, unsigned int* outlen , unsigned char* inbuf, unsigned int inlen)=0;
	virtual int PCMSize()=0;
	virtual int G7FrameSize()=0;
};
//----------------------------------------------------------------------------------------------------------------------
class InAudioInfo
{
public:
	InAudioInfo(unsigned int u32AudioCodec=EASY_SDK_AUDIO_CODEC_G711A, unsigned int u32AudioSamplerate=8000, unsigned int u32AudioChannel=1);
	~InAudioInfo(){;}

	unsigned int CodecType()
	{
		return m_u32AudioCodec;
	}
	unsigned int Samplerate()
	{
		return m_u32AudioSamplerate;
	}
	unsigned int Channel()
	{
		return m_u32AudioChannel;
	}
	unsigned int PCMBitSize()
	{
		return m_nPCMBitSize;
	}
private:
	unsigned int m_u32AudioCodec;
	unsigned int m_u32AudioSamplerate;
	unsigned int m_u32AudioChannel;

	unsigned int m_nPCMBitSize;
};
//-------------------------------------------------------------------------------------------------------------------------
class DecodeToPcmBase:public IDecodeToPcm
{
public:
	DecodeToPcmBase();
	virtual ~DecodeToPcmBase();

	int Init();

public:
	virtual int Decode(unsigned char* outbuf, unsigned int* outlen , unsigned char* inbuf, unsigned int inlen);
	virtual int PCMSize();
	virtual int G7FrameSize();

	virtual unsigned short DecodeOneChar(unsigned char data)=0;

private:
	int m_g7FrameSize;
};

#endif

