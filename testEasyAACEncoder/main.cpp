/*
	Copyright (c) 2013-2015 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
/* 
 * File:   main.cpp
 * Author: Wellsen
 *
 * Created on 2015年4月11日, 下午6:38
 */

#include <iostream>
#include "../EasyAACEncoderAPI.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TEST_G711A_FILE       "src.g711a"
#define TEST_AAC_FILE         "dest.aac"

int main(int argc, char** argv)
{
    EasyAACEncoder_Handle handle = Easy_AACEncoder_Init(0, 0, 0);
    
    FILE* fpIn = fopen(TEST_G711A_FILE, "rb");
    if(NULL == fpIn)
    {
        printf("%s:[%d] open %s file failed\n",__FUNCTION__,__LINE__,TEST_G711A_FILE);
        return -1;
    }
 
    FILE* fpOut = fopen(TEST_AAC_FILE, "wb");
    if(NULL == fpOut)
    {
        printf("%s:[%d] open %s file failed\n",__FUNCTION__,__LINE__,TEST_AAC_FILE);
        return -1;
    }
    
    int gBytesRead = 0;
    unsigned char *pbG711ABuffer = (unsigned char *)malloc(1024 *sizeof(unsigned char));
    unsigned char *pbAACBuffer = (unsigned char*)malloc(1024 * sizeof(unsigned char));  
    unsigned int out_len = 0;
    
    while((gBytesRead = fread(pbG711ABuffer, 1, 500, fpIn)) >0)
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

