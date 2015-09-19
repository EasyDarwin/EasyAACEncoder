#include "IDecodeToPcm.h"
#include "audio_buffer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





IDecodeToPcm::IDecodeToPcm(void)
{
}


IDecodeToPcm::~IDecodeToPcm(void)
{

}
//------------------------------------------------------------------------------------------------------------------------
InAudioInfo::InAudioInfo(unsigned int u32AudioCodec/*=EASY_SDK_AUDIO_CODEC_G711A*/, unsigned int u32AudioSamplerate/*=8000*/, unsigned int u32AudioChannel/*=1*/):
m_u32AudioCodec(u32AudioCodec),m_u32AudioChannel(u32AudioChannel),m_u32AudioSamplerate(u32AudioSamplerate)
{
	if (0 == u32AudioCodec)
	{
		m_u32AudioCodec = EASY_SDK_AUDIO_CODEC_G711A;
	}
	if (0 == u32AudioChannel)
	{
		m_u32AudioChannel = 1;
	}
	if (0 == u32AudioSamplerate)
	{
		m_u32AudioSamplerate = 8000;
	}

	m_nPCMBitSize = 16;
}
//------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
DecodeToPcmBase::DecodeToPcmBase(void)
{

}


DecodeToPcmBase::~DecodeToPcmBase(void)
{

}

int DecodeToPcmBase::Init()
{
	return 0;
}

int DecodeToPcmBase::Decode(unsigned char* pout_buf, unsigned int* pout_len , unsigned char* pin_buf, unsigned int in_len)
{
	int16_t *dst = (int16_t *) pout_buf;
	uint8_t *src = (uint8_t *) pin_buf;
	uint32_t i = 0;
	int Ret = 0;

	if ((NULL == pout_buf) || \
		(NULL == pout_len) || \
		(NULL == pin_buf) || \
		(0 == in_len))
	{
		return -1;
	}

	if (*pout_len < 2 * in_len)
	{
		return -2;
	}
	//---{{{

	for (i = 0; i < in_len; i++)
	{
		*(dst++) = (int16_t)DecodeOneChar(*(src++));
	}

	//---}}}
	*pout_len = 2 * in_len;

	Ret = 2 * in_len;
	return Ret;
	return 0;
}