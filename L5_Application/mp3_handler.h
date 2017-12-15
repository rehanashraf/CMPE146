/*
 * mp3Handler.h
 *
 *  Created on: Dec 8, 2017
 *      Author: mjaradah
 */

#ifndef L5_APPLICATION_MP3HANDLER_H_
#define L5_APPLICATION_MP3HANDLER_H_

#include "io.hpp"
#include "tasks.hpp"
#include "utilities.h"
#include "printf_lib.h"
#include "gpio.hpp"
#include "ssp0.h"
#include "stdio.h"
#include "storage.hpp"


class mp3Handler : public scheduler_task {
public:
	mp3Handler():scheduler_task("mp3Handler", 2000, PRIORITY_HIGH){
		play_song = NULL;
		pause_song = NULL;
		skip_song = NULL;
		volume_decrease = NULL;
		volume_increase = NULL;
	};

	bool init(void);
	bool run(void *p);

private:
	GPIO* play_song;
	GPIO* pause_song;
	GPIO* skip_song;
	GPIO* volume_decrease;
	GPIO* volume_increase;
};

#endif /* L5_APPLICATION_MP3HANDLER_H_ */
