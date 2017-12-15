/*
 * mp3Decoder.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: mjaradah
 */

#include <mp3_handler.h>

bool mp3Handler::init(void)
{
	/*
	 * We need to set up some push buttons here
	 * to handle the pause/play/skip and volume
	 *

	play_song = new GPIO(P2_0);
	pause_song = new GPIO(P2_0);
	skip_song = new GPIO(P2_0);
	volume_decrease = new GPIO(P2_0);
	volume_increase = new GPIO(P2_0);

	(*play_song).setAsInput();
	(*pause_song).setAsInput();
	(*skip_song).setAsInput();
	(*volume_decrease).setAsInput();
	(*volume_increase).setAsInput();
	 */
	return true;
}


bool mp3Handler::run(void *p)
{

	puts("RUNNING HANDLER TASK\n");
	return true;
}
