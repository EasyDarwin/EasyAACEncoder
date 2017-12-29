/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#include "G711AToPcm.h"

#include "g711.h"


G711AToPcm::G711AToPcm(void)
{
}


G711AToPcm::~G711AToPcm(void)
{
}
unsigned short G711AToPcm::DecodeOneChar(unsigned char data)
{
	return (int16_t)alaw2linear(data);
}
//-------------------------------------------
G711UToPcm::G711UToPcm(void)
{
}


G711UToPcm::~G711UToPcm(void)
{
}
unsigned short G711UToPcm::DecodeOneChar(unsigned char data)
{
	return (int16_t)ulaw2linear(data);
}