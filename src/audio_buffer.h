#pragma once

class audio_buffer
{
public:
	audio_buffer(void);
	~audio_buffer(void);

	int write_data(void *data, int len);

	int get_data(unsigned char *dest, int how_you_want);

	void update_data_len(int len);

	unsigned char *get_writable_ptr();

private:
	unsigned char *data_;
	int len_;
};

