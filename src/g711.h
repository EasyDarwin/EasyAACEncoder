/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#ifndef __G_711_H_
#define __G_711_H_

#include <stdint.h>

enum _e_g711_tp
{
	TP_ALAW,	//G711A
	TP_ULAW		//G711U
};

unsigned char linear2alaw(int		pcm_val);	/* 2's complement (16-bit range) */
int alaw2linear(unsigned char	a_val);

unsigned char linear2ulaw(int pcm_val);	/* 2's complement (16-bit range) */
int ulaw2linear(unsigned char	u_val);

unsigned char alaw2ulaw(unsigned char	aval);
unsigned char ulaw2alaw(unsigned char	uval);

int g711_decode(void *pout_buf, int *pout_len, const void *pin_buf, const int in_len , int type);

#endif
