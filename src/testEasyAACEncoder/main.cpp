/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   main.cpp
 * Author: Wellsen@easydarwin.org
 *
 * Created on 2015年4月11日, 下午6:38
 */

#include <iostream>
#include "../EasyAACEncoderAPI.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//#define TEST_G711A_FILE       "src.g711a"  //私有
#define TEST_G711A_FILE       "g711.g711a"  //标准

#define TEST_AAC_FILE         "dest.aac"

int TestG711ToAAC_private();
int TestG711ToAAC_standard();
int TestG726ToAAC();

int main(int argc, char** argv)
{
	//TestG711ToAAC_private();
	//TestG711ToAAC_standard();
	TestG726ToAAC();
    return 0;
}

int TestG711ToAAC_standard()
{
	InitParam initParam;
	initParam.u32AudioSamplerate=8000;
	initParam.ucAudioChannel=1;
	initParam.u32PCMBitSize=16;
	initParam.ucAudioCodec = Law_ALaw;
	//initParam.ucAudioCodec = Law_ULaw;
	EasyAACEncoder_Handle handle = Easy_AACEncoder_Init( initParam);
	char* infilename = "g711.g711a";  //标准
	char* outAacname = "g711.aac";

	FILE* fpIn = fopen(infilename, "rb");
	if(NULL == fpIn)
	{
		printf("%s:[%d] open %s file failed\n",__FUNCTION__,__LINE__,infilename);
		return -1;
	}

	FILE* fpOut = fopen(outAacname, "wb");
	if(NULL == fpOut)
	{
		printf("%s:[%d] open %s file failed\n",__FUNCTION__,__LINE__,outAacname);
		return -1;
	}

	int gBytesRead = 0;
	int bG711ABufferSize = 500;
	int bAACBufferSize = 4*bG711ABufferSize;//提供足够大的缓冲区
	unsigned char *pbG711ABuffer = (unsigned char *)malloc(bG711ABufferSize *sizeof(unsigned char));
	unsigned char *pbAACBuffer = (unsigned char*)malloc(bAACBufferSize * sizeof(unsigned char));  
	unsigned int out_len = 0;

	while((gBytesRead = fread(pbG711ABuffer, 1, bG711ABufferSize, fpIn)) >0)
	{    
		if(Easy_AACEncoder_Encode(handle, pbG711ABuffer, gBytesRead, pbAACBuffer, &out_len) > 0)
		{
			fwrite(pbAACBuffer, 1, out_len, fpOut);
		}
	}

	Easy_AACEncoder_Release(handle);

	free(pbG711ABuffer);
	free(pbAACBuffer);
	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
int TestG726ToAAC()
{
	InitParam initParam;
	initParam.u32AudioSamplerate=8000;
	initParam.ucAudioChannel=1;
	initParam.u32PCMBitSize=16;
	initParam.ucAudioCodec = Law_G726;
	//initParam.g726param.ucRateBits=Rate16kBits;
	//initParam.g726param.ucRateBits=Rate24kBits;
	//initParam.g726param.ucRateBits=Rate32kBits;	
	initParam.g726param.ucRateBits=Rate40kBits;	

	EasyAACEncoder_Handle handle = Easy_AACEncoder_Init(initParam);
	//char* infilename = "encode_out_16.g726"; 
	//char* outAacname = "encode_out_16.aac";
	//char* infilename = "encode_out_24.g726"; 
	//char* outAacname = "encode_out_24.aac";
	//char* infilename = "encode_out_32.g726"; 
	//char* outAacname = "encode_out_32.aac";
	char* infilename = "encode_out_40.g726"; 
	char* outAacname = "encode_out_40.aac";

	FILE* fpIn = fopen(infilename, "rb");
	if(NULL == fpIn)
	{
		printf("%s:[%d] open %s file failed\n",__FUNCTION__,__LINE__,infilename);
		return -1;
	}

	FILE* fpOut = fopen(outAacname, "wb");
	if(NULL == fpOut)
	{
		printf("%s:[%d] open %s file failed\n",__FUNCTION__,__LINE__,outAacname);
		return -1;
	}

	int gBytesRead = 0;
	int bG726BufferSize = 500;
	int bAACBufferSize = 4*bG726BufferSize;//提供足够大的缓冲区
	unsigned char *pbG726Buffer = (unsigned char *)malloc(bG726BufferSize *sizeof(unsigned char));
	unsigned char *pbAACBuffer = (unsigned char*)malloc(bAACBufferSize * sizeof(unsigned char));  
	unsigned int out_len = 0;

	while((gBytesRead = fread(pbG726Buffer, 1, bG726BufferSize, fpIn)) >0)
	{    
		if(Easy_AACEncoder_Encode(handle, pbG726Buffer, gBytesRead, pbAACBuffer, &out_len) > 0)
		{
			fwrite(pbAACBuffer, 1, out_len, fpOut);
			printf("%s:[%d] pbAACBuffer(%d) len=%d \n",__FUNCTION__,__LINE__,bAACBufferSize,out_len);
		}
	}

	Easy_AACEncoder_Release(handle);

	free(pbG726Buffer);
	free(pbAACBuffer);
	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
