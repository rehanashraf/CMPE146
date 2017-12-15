/*
 * mp3Decoder.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rehanashraf
 */

#include <mp3Decoder.h>
#include "scheduler_task.hpp"

#define MAX_VOLUME 1
#define MIN_VOLUME 100
#define MAX_SONGS 20
#define CLEAR 0x0C
#define BACKLIGHT_ON 0X11
#define CURSOR_OFF 0x16

#define ARR_SIZEOF(array) sizeof(array) / sizeof(array[0])


FIL file;

GPIO dataRequest(P1_20);
GPIO cs_SCI(P1_19);
GPIO cs_SDI(P0_30);
GPIO softReset(P0_29);

uint8_t volume = MAX_VOLUME;
int song_to_play = 0;
uint8_t songs_available = 8;
bool initialized = false;
song_info_S * newsong;
Uart3 &lcd = Uart3::getInstance();

typedef enum{
	VS1053_WRITE = 0x02,
	VS1053_CLK_FREQ = 0x3, // Clock freq + multiplier
	VS1053_VOL_CTRL = 0xB, // Volume control
} VS1053_E;


bool mp3Decoder::init(void)
{

	lcd.init(9600, 10, 10);
	delay_ms(100);
	lcd.putChar(CLEAR, portMAX_DELAY);
	delay_ms(5);
	lcd.putChar(BACKLIGHT_ON, portMAX_DELAY);
	lcd.putChar(CURSOR_OFF, portMAX_DELAY);
//	lcd.putChar('0x0C', portMAX_DELAY);
	char initStr[] = "Hello World!\n";
	lcd.putline(initStr, portMAX_DELAY);
	delay_ms(1000);
	lcd.putChar(CLEAR, portMAX_DELAY);
	delay_ms(5);

	ssp0_init(1);
	ssp0_set_max_clock(1);


	cs_SCI.setAsOutput();
	cs_SDI.setAsOutput();
	softReset.setAsOutput();

	cs_SCI.setHigh();
	cs_SDI.setHigh();

	dataRequest.setAsInput();
	dataRequest.enablePullDown();

	softReset.setLow();
	delay_ms(10);
	softReset.setHigh();
	delay_ms(50);

	localOffset = 0;
	localOffsetMax = 32;
	offset = 0;
	needmoredatainbuffer = true;

	cs_SCI.setLow();
	ssp0_exchange_byte(VS1053_WRITE);
	ssp0_exchange_byte(VS1053_CLK_FREQ);
	ssp0_exchange_byte(0x80);
	ssp0_exchange_byte(0x00);
	cs_SCI.setHigh();

	ssp0_set_max_clock(5);
	ReadeSize = 512;
	newsong = get_all_song_info_arry();
	song_to_play = 0;

	return true;
}

bool mp3Decoder::run(void *p)
{

	if (!initialized)
	{
		delay_ms(500);
		offset =0;
		localOffset = 0;

		songpathbuffer[0]= '\0';
		strcat(songpathbuffer, "1:");

		strcat(songpathbuffer, newsong[song_to_play].song_name);

		if(FR_OK== f_open(&file, songpathbuffer, FA_READ))
		{
			printf("file opened properly\n");
			lcd.putChar(CLEAR, portMAX_DELAY);
			delay_ms(20);
			lcd.putline(newsong[song_to_play].song_name, portMAX_DELAY);
			delay_ms(100);
			initialized = true;
		}
	}
	if (localOffset > 511)
	{
		offset = offset + 512;
		localOffset = 0;
		needmoredatainbuffer = true;
	}

	if (needmoredatainbuffer)
	{
		if(offset)
		{
			f_lseek(&file, offset);
		}
		if (FR_OK== f_read(&file, data, ReadeSize, &sizeread))
		{

		}
		needmoredatainbuffer = false;
	}

	if (dataRequest.read())
	{
		cs_SDI.setLow();
		localOffsetMax = localOffset + 32;

		for (uint16_t i=localOffset; i< localOffsetMax ; i++)
		{
			(void)ssp0_exchange_byte(data[i]);
			localOffset ++;
		}

		cs_SDI.setHigh();
	}
	return true;
}

void mp3Decoder::MP3_set_volume_percent(float percent)
{
	if (percent >= 100)
	{
		volume = MIN_VOLUME;
	}
	else if (percent <= 0)
	{
		volume = MAX_VOLUME;
	}

	taskENTER_CRITICAL();
	cs_SCI.setLow();
	(void)ssp0_exchange_byte(VS1053_WRITE);
	(void)ssp0_exchange_byte(VS1053_VOL_CTRL);
	(void)ssp0_exchange_byte((char)volume);
	(void)ssp0_exchange_byte((char)volume);
	cs_SCI.setHigh();
	taskEXIT_CRITICAL();
}


float mp3Decoder::MP3_get_volume_percentage(void)
{
	return (float)(101.0 - volume);
}



void MP3_play_handler(void)
{
	static bool playing = true;


	scheduler_task *decoder_task = scheduler_task::getTaskPtrByName("mp3decoder");

	if (playing)
	{
		playing = false;
		vTaskSuspend(decoder_task->getTaskHandle());
	}
	else
	{
		playing = true;
		vTaskResume(decoder_task->getTaskHandle());
	}
}

void MP3_incr_vol_handler(void)
{
	mp3Decoder decoder;
	volume -= 2.0;
	decoder.MP3_set_volume_percent(volume);
}

void MP3_decr_vol_handler(void)
{
	mp3Decoder decoder;
	volume += 2.0;
	decoder.MP3_set_volume_percent(volume);
}

void MP3_next_song_handler(void)
{
	initialized = false;
	f_close(&file);

	if((song_to_play < 0))
	{
		song_to_play = 0;
	}
	else if (song_to_play > songs_available)
	{
		song_to_play = songs_available;
	}
	else
	{
		song_to_play += 1;
	}
}

void MP3_prev_song_handler(void)
{
	initialized = false;
	f_close(&file);

	if((song_to_play < 0))
	{
		song_to_play = 0;
	}
	else if (song_to_play > songs_available)
	{
		song_to_play = songs_available;
	}
	else
	{
		song_to_play -= 1;
	}
}
