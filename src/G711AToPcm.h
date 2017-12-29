/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#pragma once
#include "IDecodeToPcm.h"

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
