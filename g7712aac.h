/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   g7712aac.h
 * Author: Wellsen
 *
 * Created on 2015年4月11日, 上午11:44
 */

#ifndef G7712AAC_H
#define	G7712AAC_H
extern "C" {
#include <faac.h>
}
#include "EasyDSSBuffers.h"

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

class g7712aac
{
public:
    g7712aac();
    virtual ~g7712aac();
    
    int init();
    
    int aac_encode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen);
    
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
};

#endif	/* G7712AAC_H */

