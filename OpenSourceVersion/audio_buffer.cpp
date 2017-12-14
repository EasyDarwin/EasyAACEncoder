#include "audio_buffer.h"
#include "EasyDSSBuffers.h"
#include "outDebug.h"


audio_buffer::audio_buffer()
{
	data_ = new unsigned char[iBufLen];
	len_ = 0;
}

audio_buffer::~audio_buffer()
{
	delete []data_;
}

int audio_buffer::write_data(void* data, int len)
{
	if (iBufLen - len_ < len)
	{
		if(AAC_DEBUG) printf("audio_buffer full\n");
		return -1;
	}
	if (len > 0)
	{
		memcpy(data_ + len_, data, len);
		len_ += len;
		return len;
	}
	return 0;
}

int audio_buffer::get_data(unsigned char* dest, int how_you_want)
{
	if (len_ == 0 || len_ < how_you_want)
	{
		return 0;
	}
	else
	{
		memcpy(dest, data_, how_you_want);
		memmove(data_, data_ + how_you_want, len_ - how_you_want);
		len_ -= how_you_want;
		return how_you_want;
	}   
}

unsigned char* audio_buffer::get_writable_ptr()
{
	return data_ + len_;
}

void audio_buffer::update_data_len(int len)
{
	len_ += len;
}
