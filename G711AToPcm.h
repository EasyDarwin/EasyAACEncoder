#pragma once
#include "idecodetopcm.h"

class G711AToPcm :
	public DecodeToPcmBase
{
public:
	G711AToPcm(void);
	virtual ~G711AToPcm(void);
public:
	virtual unsigned short DecodeOneChar(unsigned char data);
};


class G711UToPcm :
	public DecodeToPcmBase
{
public:
	G711UToPcm(void);
	virtual ~G711UToPcm(void);
public:
	virtual unsigned short DecodeOneChar(unsigned char data);
};
