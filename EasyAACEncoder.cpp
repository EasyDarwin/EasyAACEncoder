/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   EasyAACEncoder.cpp
 * Author: Wellsen
 * 
 * Created on 2015年4月11日, 上午11:44
 */

#include "EasyAACEncoder.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "g711.h"

#include "EasyAACEncoderAPI.h"

#include "outDebug.h"
#include "G711AToPcm.h"
#include "G726ToPcm.h"
#include "condef.h"


G7ToAac::G7ToAac()
{
    m_pbPCMBuffer = NULL;
    m_pbAACBuffer = NULL;
	m_pbG7FrameBuffer = NULL;
    m_pbPCMTmpBuffer = NULL;

    m_audio_buffer_ = NULL;

	m_pDecodeToPcm = NULL;

	m_pPCMToAAC = NULL;
}

G7ToAac::~G7ToAac()
{

    /*free the source of malloc*/
	SAFE_FREE_BUF(m_pbPCMBuffer);
	SAFE_FREE_BUF(m_pbAACBuffer);
	SAFE_FREE_BUF(m_pbG7FrameBuffer);
	SAFE_FREE_BUF(m_pbPCMTmpBuffer);

	SAFE_DELETE_OBJ(m_audio_buffer_);
	SAFE_DELETE_OBJ(m_pDecodeToPcm);
	SAFE_DELETE_OBJ(m_pPCMToAAC);

}
bool G7ToAac::init()
{
	nRet = 0;
	nTmp = 0;
	nCount = 0;
	nStatus = 0;
	nPCMRead = 0;



	CreateBuffer();

	return true;
}

bool G7ToAac::init(InAudioInfo info)
{
	m_inAudioInfo = info;

	bool ret=false;
	ret = CreateDecodePcm();

	ret = CreateEncodeAac();
	if (!ret)
	{
		return false;
	}
	return init();
}
bool G7ToAac::CreateDecodePcm()
{
	if ( Law_ALaw == m_inAudioInfo.CodecType())
	{
		m_pDecodeToPcm = new G711AToPcm();
	}else if ( Law_ULaw == m_inAudioInfo.CodecType() )
	{
		m_pDecodeToPcm = new G711UToPcm();
	}else if ( Law_G726 == m_inAudioInfo.CodecType())
	{
		m_pDecodeToPcm = new G726ToPcm();
	}else
	{
		m_pDecodeToPcm = new G711AToPcm();
	}
	m_pDecodeToPcm->Init(m_inAudioInfo);

	return true;
}
bool G7ToAac::CreateEncodeAac()
{
	m_pPCMToAAC = new PcmToAac();
	bool ret = m_pPCMToAAC->Init(&m_inAudioInfo);

	return ret;
}
bool G7ToAac::CreateBuffer()
{
	m_nPCMBufferSize = m_pPCMToAAC->GetPCMBufferSize();
	m_pbPCMBuffer = (unsigned char*) malloc(m_nPCMBufferSize * sizeof (unsigned char));
	memset(m_pbPCMBuffer, 0, m_nPCMBufferSize);

	m_nMaxOutputBytes = m_pPCMToAAC->GetMaxOutputBytes();
	m_pbAACBuffer = (unsigned char*) malloc(m_nMaxOutputBytes * sizeof (unsigned char));
	memset(m_pbAACBuffer, 0, m_nMaxOutputBytes);

	m_nG7FrameBufferSize = m_pDecodeToPcm->G7FrameSize();
	m_pbG7FrameBuffer = (unsigned char *) malloc(m_nG7FrameBufferSize * sizeof (unsigned char));
	memset(m_pbG7FrameBuffer, 0, m_nG7FrameBufferSize);

	m_nPCMSize = m_pDecodeToPcm->PCMSize();
	m_pbPCMTmpBuffer = (unsigned char *) malloc(m_nPCMSize * sizeof (unsigned char));
	memset(m_pbPCMTmpBuffer, 0, m_nPCMSize);

	m_audio_buffer_ = new audio_buffer();

	return true;
}
int G7ToAac::aac_encode(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen)
{
	int encodeLen = 0;

	if (NULL != m_pDecodeToPcm)
	{
		encodeLen = aac_encode_obj(inbuf , inlen , outbuf , outlen);
	}

	return encodeLen;
}

int G7ToAac::aac_encode_obj(unsigned char* inbuf, unsigned int inlen, unsigned char* outbuf, unsigned int* outlen )
{
	m_audio_buffer_->write_data(inbuf, inlen);
	int buffer_len = 0;
	*outlen = 0;
	int nPCMSize = 0;
	//while ((buffer_len = audio_buffer_->get_data(pbG711ABuffer, /*164*/G711_ONE_LEN)) > 0)
	while ((buffer_len = m_audio_buffer_->get_data(m_pbG7FrameBuffer, m_nG7FrameBufferSize)) > 0)
	{
		if (buffer_len <= 0)
		{
			if(AAC_DEBUG) printf("%s:[%d] G711A -> PCM  no G711 data !\n", __FUNCTION__, __LINE__);
			//Sleep(100);
			return -1;
		}

		nStatus = 0;        
		memset(m_pbPCMTmpBuffer, 0, m_nPCMSize);
		nPCMSize = m_nPCMSize;
		//if ((nPCMRead = m_pDecodeToPcm->Decode(pbPCMTmpBuffer, (unsigned int*)&PCMSize, pbG711ABuffer+/*4*/G711_ONE_OFFSET, buffer_len-/*4*/G711_ONE_OFFSET )) < 0) // TODO: skip 4 byte?
		if ((nPCMRead = m_pDecodeToPcm->Decode(m_pbPCMTmpBuffer, (unsigned int*)&nPCMSize, m_pbG7FrameBuffer, buffer_len )) < 0) // TODO: skip 4 byte?
		{
			if(AAC_DEBUG) printf("%s:[%d] G711A -> PCM  failed buffer_len = %d !\n", __FUNCTION__, __LINE__, buffer_len);            
			return -1;
		}
		//if(AAC_DEBUG) printf("nPCMRead = %d, PCMSize = %d\n", nPCMRead, PCMSize);

		if ((m_nPCMBufferSize - nCount) < nPCMRead)
		{
			//if(AAC_DEBUG) printf("nPCMBufferSize = %d, nCount = %d, nPCMRead = %d\n", nPCMBufferSize, nCount, nPCMRead);
			nStatus = 1;
			memset(m_pbAACBuffer, 0, m_nMaxOutputBytes);
			memcpy(m_pbPCMBuffer + nCount, m_pbPCMTmpBuffer, (m_nPCMBufferSize - nCount));

			nRet = m_pPCMToAAC->Encode( (int32_t*)m_pbPCMBuffer , m_nPCMBufferSize , m_pbAACBuffer, m_nMaxOutputBytes);


			memcpy(outbuf + *outlen, m_pbAACBuffer, nRet);
			*outlen += nRet;

			nTmp = nPCMRead - (m_nPCMBufferSize - nCount);
			memset(m_pbPCMBuffer, 0, m_nPCMBufferSize);
			memcpy(m_pbPCMBuffer, m_pbPCMTmpBuffer + (m_nPCMBufferSize - nCount), nTmp);
			if(AAC_DEBUG) printf("%s:[%d] G711A -> PCM (nPCMBufferSize - nCount) < nPCMRead\n",  __FUNCTION__, __LINE__);
			nCount = 0;
			nCount += nTmp;
		}

		if (nStatus == 0)
		{
			if(AAC_DEBUG) printf("%s:[%d] G711A -> PCM nStatus = 0...\n",  __FUNCTION__, __LINE__);
			memcpy(m_pbPCMBuffer + nCount, m_pbPCMTmpBuffer, nPCMRead);
			if(AAC_DEBUG) printf("%s:[%d] G711A -> PCM nStatus = 0\n",  __FUNCTION__, __LINE__);
			nCount += nPCMRead;
		}

		if (nPCMRead < /*320*/CON_PCM_SIZE)
		{
			if(AAC_DEBUG) printf("nPCMRead = %d\n", nPCMRead);

			nRet = m_pPCMToAAC->Encode((int*) m_pbPCMBuffer, nCount , m_pbAACBuffer, m_nMaxOutputBytes);


			memcpy(outbuf + *outlen, m_pbAACBuffer, nRet);
			*outlen += nRet;

			INFO_D(AAC_DEBUG , "G711A -> PCM nPCMRead < 320");
		}
	}
	return *outlen;
}