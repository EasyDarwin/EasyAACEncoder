/*
	Copyright (c) 2012-2017 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#include <iostream>
#include "EasyAACEncoderAPI.h"
#include <stdio.h>
#include <stdlib.h>
#include "EasyTypes.h"

using namespace std;

//#define TEST_G711A_FILE       "src.g711a"  //私有
#define TEST_G711A_FILE       "g711.g711a"  //标准

#define TEST_AAC_FILE         "dest.aac"

#define EASYAACENCODER_KEY "7558773264662B2B72624B41386D395A7070414D792B39305A584E305A57467A65576C77593246745A584A684B56634D5671442F532B424859585A7062695A4359574A76633246414D6A41784E6B566863336C4559584A33615735555A5746745A57467A65513D3D"


int TestG711ToAAC_private();
int TestG711ToAAC_standard();
int TestG726ToAAC();
int TestPcmToAAC();

int main(int argc, char** argv)
{
    //TestG711ToAAC_private();
    //TestG711ToAAC_standard();
    //TestG726ToAAC();
	TestPcmToAAC();
    return 0;
}

int TestG711ToAAC_standard()
{
    int active = 0;
    InitParam initParam;
    initParam.u32AudioSamplerate=8000;
    initParam.ucAudioChannel=1;
    initParam.u32PCMBitSize=16;
    initParam.ucAudioCodec = Law_ALaw;
    //initParam.ucAudioCodec = Law_ULaw;

    active = Easy_AACEncoder_activate(EASYAACENCODER_KEY);
    if(active != EASY_ACTIVATE_SUCCESS)
    {
        printf("%s:[%d] Easy_AACEncoder_activate failed! ret=%d\n",__FUNCTION__,__LINE__,active);
        return -1;
    }

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

#include <unistd.h>
#include <time.h>
static unsigned long long os_get_reltime(void)
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (tp.tv_sec * 1000000ULL + tp.tv_nsec / 1000ULL);
}

int TestG726ToAAC()
{
    int active = 0;
    InitParam initParam;
    initParam.u32AudioSamplerate=8000;
    initParam.ucAudioChannel=1;
    initParam.u32PCMBitSize=16;
    initParam.ucAudioCodec = Law_G726;
    //initParam.g726param.ucRateBits=Rate16kBits;
    //initParam.g726param.ucRateBits=Rate24kBits;
    //initParam.g726param.ucRateBits=Rate32kBits;	
    initParam.g726param.ucRateBits=Rate40kBits;	

    active = Easy_AACEncoder_activate(EASYAACENCODER_KEY);
    if(active != EASY_ACTIVATE_SUCCESS)
    {
        printf("%s:[%d] Easy_AACEncoder_activate failed! ret=%d\n",__FUNCTION__,__LINE__,active);
        return -1;
    }

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
    int bG726BufferSize = 40000 / 8 / 25;
    int bAACBufferSize = 4*bG726BufferSize;//提供足够大的缓冲区
    unsigned char *pbG726Buffer = (unsigned char *)malloc(bG726BufferSize *sizeof(unsigned char));
    unsigned char *pbAACBuffer = (unsigned char*)malloc(bAACBufferSize * sizeof(unsigned char));  
    unsigned int out_len = 0;
    unsigned long long ts = os_get_reltime();

    while((gBytesRead = fread(pbG726Buffer, 1, bG726BufferSize, fpIn)) >0)
    {    
        if(Easy_AACEncoder_Encode(handle, pbG726Buffer, gBytesRead, pbAACBuffer, &out_len) > 0)
        {
                fwrite(pbAACBuffer, 1, out_len, fpOut);
                printf("%s:[%d] pbAACBuffer(%d) len=%d \n",__FUNCTION__,__LINE__,bAACBufferSize,out_len);
        }
        while (os_get_reltime() < ts + 1000000/25) {
                usleep(1000000/25);
        }
        ts += 1000000/25;
    }

    Easy_AACEncoder_Release(handle);

    free(pbG726Buffer);
    free(pbAACBuffer);
    fclose(fpIn);
    fclose(fpOut);

    return 0;
}

int TestPcmToAAC()
{
    int active = 0;
	InitParam initParam;
	initParam.u32AudioSamplerate=44100;
	initParam.ucAudioChannel=2;
	initParam.u32PCMBitSize=16;
	initParam.ucAudioCodec = Law_PCM16;
	//initParam.g726param.ucRateBits=Rate16kBits;
	//initParam.g726param.ucRateBits=Rate24kBits;
	//initParam.g726param.ucRateBits=Rate32kBits;	
	//initParam.g726param.ucRateBits=Rate40kBits;	

    active = Easy_AACEncoder_activate(EASYAACENCODER_KEY);
    if(active != EASY_ACTIVATE_SUCCESS)
    {
        printf("%s:[%d] Easy_AACEncoder_activate failed! ret=%d\n",__FUNCTION__,__LINE__,active);
        return -1;
    }

	EasyAACEncoder_Handle handle = Easy_AACEncoder_Init(initParam);
	//char* infilename = "encode_out_16.g726"; 
	//char* outAacname = "encode_out_16.aac";
	//char* infilename = "encode_out_24.g726"; 
	//char* outAacname = "encode_out_24.aac";
	//char* infilename = "encode_out_32.g726"; 
	//char* outAacname = "encode_out_32.aac";
	char* infilename = "playback.pcm"; 
	char* outAacname = "playback.aac";

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
	int bPcmBufferSize = 44100 * 2 * 16 / 8 / 25;
	int bAACBufferSize = 4*bPcmBufferSize;//提供足够大的缓冲区
	unsigned char *pbPcmBuffer = (unsigned char *)malloc(bPcmBufferSize *sizeof(unsigned char));
	unsigned char *pbAACBuffer = (unsigned char*)malloc(bAACBufferSize * sizeof(unsigned char));  
	unsigned int out_len = 0;
	unsigned long long ts = os_get_reltime();

	while((gBytesRead = fread(pbPcmBuffer, 1, bPcmBufferSize, fpIn)) >0)
	{    
		if((Easy_AACEncoder_Encode(handle, pbPcmBuffer, gBytesRead, pbAACBuffer, &out_len)) > 0)
		{
			fwrite(pbAACBuffer, 1, out_len, fpOut);
			printf("%s:[%d] pbAACBuffer(%d) len=%d \n",__FUNCTION__,__LINE__,bAACBufferSize,out_len);
		}
		//while (os_get_reltime() < ts + 1000000/25) {
		//	usleep(1000000/25);
		//}
		ts += 1000000/25;
	}

	Easy_AACEncoder_Release(handle);

	free(pbPcmBuffer);
	free(pbAACBuffer);
	fclose(fpIn);
	fclose(fpOut);

	return 0;
}

