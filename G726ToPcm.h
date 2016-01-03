/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#pragma once
#include "IDecodeToPcm.h"
#include "g726.h"

class G726ToPcm:public IDecodeToPcm
{
public:
	G726ToPcm(void);
	virtual ~G726ToPcm(void);

public:
	int Init(InAudioInfo info);

public:
	virtual int Decode(unsigned char* outbuf, unsigned int* outlen , unsigned char* inbuf, unsigned int inlen);
	virtual int PCMSize();
	virtual int G7FrameSize();

private:
	g726_state_t *m_state726;
	int m_bitRate;

	int m_g7FrameSize;
	int m_pcmSize;
};

