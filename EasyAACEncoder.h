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

#include "audio_buffer.h"
#include "IDecodeToPcm.h"
#include "PcmToAac.h"



class g7712aac
{
public:
    g7712aac();
    virtual ~g7712aac();
    
	int init2();
    int init();
	int init(InAudioInfo info);
    
    int aac_encode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);

private:
	int aac_encode_base(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
	int aac_encode_g711(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen , int type);

	int aac_encode_obj(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen );
    
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

	IDecodeToPcm* m_pDecodeToPcm;
	PcmToAac* m_pPCMToAAC;
};

#endif	/* EasyAACEncoder_H */

