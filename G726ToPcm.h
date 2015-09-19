#pragma once
#include "idecodetopcm.h"
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

