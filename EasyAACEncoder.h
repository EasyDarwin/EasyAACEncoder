/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   EasyAACEncoder.h
 * Author: Wellsen
 *
 * Created on 2015年4月11日, 上午11:44
 */

#ifndef EasyAACEncoder_H
#define	EasyAACEncoder_H
extern "C" {
#include <faac.h>
}
#include "EasyDSSBuffers.h"
#include "EasyAACEncoderAPI.h"

class audio_buffer
{
public:
    audio_buffer();
    ~audio_buffer();
    
    int write_data(void *data, int len);
    
    int get_data(unsigned char *dest, int how_you_want);
    
    void update_data_len(int len);
    
    unsigned char *get_writable_ptr();
    
private:
    unsigned char *data_;
    int len_;
};


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
private:
	unsigned int m_u32AudioCodec;
	unsigned int m_u32AudioSamplerate;
	unsigned int m_u32AudioChannel;
};

class g7712aac
{
public:
    g7712aac();
    virtual ~g7712aac();
    
    int init();
	int init(InAudioInfo info);
    
    int aac_encode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

private:
	int aac_encode_base(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
	int aac_encode_g711(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen , int type);
    
private:        
    int nRet;
    int nTmp;
    int nCount;
    int nStatus; 
    int nPCMRead;
    int PCMSize;    
    int nPCMBufferSize;
    unsigned long nInputSamples;
    unsigned long nMaxOutputBytes;
    unsigned int nPCMBitSize;
    unsigned char *pbPCMBuffer;
    unsigned char *pbAACBuffer;
    audio_buffer *audio_buffer_;
    unsigned char *pbG711ABuffer;
    unsigned char *pbPCMTmpBuffer; 
    faacEncHandle hEncoder;
    faacEncConfigurationPtr pConfiguration;

	//------
	InAudioInfo m_inAudioInfo;
	unsigned int GetAudioChannel()
	{
		return m_inAudioInfo.Channel();
	}
	unsigned int GetAudioSamplerate()
	{
		return m_inAudioInfo.Samplerate();
	}
};

#endif	/* EasyAACEncoder_H */

