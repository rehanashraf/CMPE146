/*
 * mp3Decoder.h
 *
 *  Created on: Dec 8, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_MP3DECODER_H_
#define L5_APPLICATION_MP3DECODER_H_

#include "io.hpp"
#include "tasks.hpp"
#include "utilities.h"
#include "printf_lib.h"
#include "gpio.hpp"
#include "ssp0.h"
#include "stdio.h"
#include "storage.hpp"
#include "sdcard.h"
//#include "songnames.h"
#include "uart3.hpp"
#include <string.h>


void MP3_play_handler(void);
void MP3_incr_vol_handler(void);
void MP3_decr_vol_handler(void);
void MP3_next_song_handler(void);
void MP3_prev_song_handler(void);


class mp3Decoder : public scheduler_task {
public:

	mp3Decoder():scheduler_task("mp3decoder", 2000, PRIORITY_HIGH){
		localOffset =localOffsetMax= offset=0;
		needmoredatainbuffer = true;
	};

	bool init(void);
	bool run(void *p);
	void MP3_set_volume_percent(float percent);
	float MP3_get_volume_percentage(void);


private:
	uint16_t localOffset;				// 0 // 33
	uint16_t localOffsetMax;
	uint8_t data[512];
	int offset;
	UINT sizeread;
	bool needmoredatainbuffer;
	FRESULT status = FR_INT_ERR;
	char songpathbuffer[15];
	UINT ReadeSize;
};
#endif /* L5_APPLICATION_MP3DECODER_H_ */
