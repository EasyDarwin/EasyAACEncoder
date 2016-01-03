/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "IDecodeToPcm.h"

extern "C" 
{
#include <faac.h>
}

class PcmToAac
{
public:
	PcmToAac(void);
	~PcmToAac(void);
public:
	bool Init(InAudioInfo* info);
	int Encode(int32_t * inputBuffer, unsigned int samplesInput, unsigned char *outputBuffer, unsigned int bufferSize);
public:
	unsigned int GetPCMBitSize()
	{
		return m_nPCMBitSize;
	}
	unsigned int GetInputSamples()
	{
		return m_nInputSamples;
	}
	unsigned int GetMaxOutputBytes()
	{
		return m_nMaxOutputBytes;
	}
	unsigned int GetPCMBufferSize()
	{
		return (m_nInputSamples * (m_nPCMBitSize / 8));
	}


private:
	faacEncHandle hEncoder;
	faacEncConfigurationPtr pConfiguration;

	unsigned int m_nPCMBitSize /*= 16*/;

	unsigned long m_nInputSamples /*= 0*/;

	unsigned long m_nMaxOutputBytes /*= 0*/;
};

