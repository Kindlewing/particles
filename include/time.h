#ifndef TIME_H
#define TIME_H

#include <stdint.h>

typedef struct {
	float delta;
	float now;
	float last;

	float frame_last;
	float frame_delay;
	float frame_time;
	uint32_t frame_rate;
	uint32_t frame_count;
} time;

#endif
