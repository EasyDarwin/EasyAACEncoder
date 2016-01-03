/*
	Copyright (c) 2013-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/

#include "EasyDSSBuffers.h"

int init_buffers(buffers_t * bufs, int bufsize, int bufnum)
{
    int i;
    bufs->rear = 0;
    bufs->front = 0;
    if(bufnum > MAX_BUF_NUM)
    {
        bufs->bufnum = MAX_BUF_NUM;
    }
    else
    {
        bufs->bufnum = bufnum;
    }
    for(i = 0; i < bufs->bufnum; i++)
    {
        bufs->buf[i].length = 0;
        bufs->buf[i].start = (char *) calloc(1, bufsize);
        bufs->buf[i].frame_type = -1;
        bufs->buf[i].channel = -1;
        bufs->buf[i].frame_index = 0;
        if(bufs->buf[i].start == NULL)
            return -1;
    }
#ifdef WIN32
    InitializeCriticalSection(&(bufs->cs));
#else
    InitializeCriticalSection(&(bufs->cs), NULL);
#endif
    return 0;
}

int free_buffers(buffers_t* bufs)
{
    for(int i = 0; i < bufs->bufnum; i++)
    {
        if(bufs->buf[i].start != NULL)
            free(bufs->buf[i].start);
    }
    bufs->pOnVideoData = NULL;
    DeleteCriticalSection(&(bufs->cs));
    return 0;
}

int buffers_get_data(void *data, unsigned int *length, buffers_t * bufs, int *type,
                     int *channel, int *frame_index)
{
    int res = -1;
    EnterCriticalSection(&(bufs->cs));
    if(bufs->front != bufs->rear)
    {
        res = *length = bufs->buf[bufs->front].length;
        memcpy(data, bufs->buf[bufs->front].start, *length);
        *type = bufs->buf[bufs->front].frame_type;
        *channel = bufs->buf[bufs->front].channel;
        *frame_index = bufs->buf[bufs->front].frame_index;
        bufs->front = (bufs->front + 1) % bufs->bufnum;
        //res = 1;
    }
    LeaveCriticalSection(&(bufs->cs));
    return res;
}

int buffers_put_data(void *data, unsigned int length, buffers_t * bufs, int type,
                     int channel, int frame_index)
{
    int res = 0;
    EnterCriticalSection(&(bufs->cs));

    if(((bufs->rear + 1) % bufs->bufnum) == bufs->front)
    {
        res = -1;
    }
    else
    {
        bufs->buf[bufs->rear].length = length;
        bufs->buf[bufs->rear].frame_type = type;
        bufs->buf[bufs->rear].channel = channel;
        bufs->buf[bufs->rear].frame_index = frame_index;
        if(length < iBufLen)
        {
            memcpy(bufs->buf[bufs->rear].start, data, length);
        }
        else
        {
            //WriteSystemLog("DataRecv.log", "Frame is too large");
            printf("Frame is too large, length=%d\r\n", length);
        }
        bufs->rear = (bufs->rear + 1) % bufs->bufnum;
        res = 1;       
    }

    LeaveCriticalSection(&(bufs->cs));
    return res;
}

void buffers_clear_data(buffers_t * bufs)
{
    EnterCriticalSection(&(bufs->cs));
    bufs->rear = 0;
    bufs->front = 0;
    LeaveCriticalSection(&(bufs->cs));
}


