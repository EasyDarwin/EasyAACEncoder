/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#include "G726ToPcm.h"
#include "condef.h"


G726ToPcm::G726ToPcm(void)
{
	//g726_state_t *g_state726_16 = NULL; //for g726_16 
	//g726_state_t *g_state726_24 = NULL; //for g726_24 
	//g726_state_t *g_state726_32 = NULL; //for g726_32 
	//g726_state_t *g_state726_40 = NULL; //for g726_40 

	//char* infilename ="O:\\video_audio\\encode_out_16-80.g726";
	//char* outfilename ="O:\\video_audio\\decode_out_16-30.pcm";
	//g_state726_16 = (g726_state_t *)malloc(sizeof(g726_state_t));
	//g_state726_16 = g726_init(g_state726_16, 8000*2);

	//char* infilename ="O:\\video_audio\\encode_out_24.g726";
	//char* outfilename ="O:\\video_audio\\decode_out_24.pcm";
	//g_state726_24 = (g726_state_t *)malloc(sizeof(g726_state_t));
	//g_state726_24 = g726_init(g_state726_24, 8000*3);

	//char* infilename ="O:\\video_audio\\encode_out_32-80.g726";
	//char* outfilename ="O:\\video_audio\\decode_out_32-30.pcm";
	//g_state726_32 = (g726_state_t *)malloc(sizeof(g726_state_t));
	//g_state726_32 = g726_init(g_state726_32, 8000*4);

	//char* infilename ="O:\\video_audio\\encode_out_40.g726";
	//char* outfilename ="O:\\video_audio\\decode_out_40-30.pcm";
	//g_state726_40 = (g726_state_t *)malloc(sizeof(g726_state_t));
	//g_state726_40 = g726_init(g_state726_40, 8000*5);
}


G726ToPcm::~G726ToPcm(void)
{
	SAFE_FREE_BUF(m_state726);
}

int G726ToPcm::Init(InAudioInfo info)
{
	m_g7FrameSize = G711_ONE_LEN;

	m_state726 = (g726_state_t *)malloc(sizeof(g726_state_t));

	int rateBits = info.G726RateBits();
	switch (rateBits)
	{
	default:
	case Rate16kBits:
		{
		m_bitRate = 8000*2;
		m_pcmSize = (2*m_g7FrameSize*120+30)/30;
		}
		break;
	case Rate24kBits:	
		{
		m_bitRate = 8000*3;
		m_pcmSize = (2*m_g7FrameSize*80+30)/30;
		}
		break;
	case Rate32kBits:	
		{
		m_bitRate = 8000*4;
		m_pcmSize = (2*m_g7FrameSize*60+30)/30;
		}
		break;

	case Rate40kBits:	
		{
		m_bitRate = 8000*5;
		m_pcmSize = (2*m_g7FrameSize*48+30)/30;
		}
		break;
	}
	m_state726 = g726_init(m_state726, m_bitRate );

	return 0;
}

int G726ToPcm::Decode(unsigned char* outbuf, unsigned int* outlen , unsigned char* inbuf, unsigned int inlen)
{
	//iRet = g726_decode(g_state726_16, (short*)ucOutBuff, ucInBuff,30);//   120 ÐÐ
	//iRet = g726_decode(g_state726_24, (short*)ucOutBuff, ucInBuff, 30);//   80 ÐÐ
	//iRet = g726_decode(g_state726_32, (short*)ucOutBuff, ucInBuff, 30);// 60
	//iRet = g726_decode(g_state726_40, (short*)ucOutBuff, ucInBuff, 30);// 48

	int iRet = g726_decode(m_state726, (short*)outbuf, inbuf, inlen);

	*outlen = iRet*2;

	return iRet*2;
}
int G726ToPcm::PCMSize()
{
	return m_pcmSize;

}
int G726ToPcm::G7FrameSize()
{
	return m_g7FrameSize;
}