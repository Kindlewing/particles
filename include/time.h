#ifndef TIME_H
#define TIME_H

#include <stdint.h>

typedef struct {
	float dt;
	uint64_t frame_count;
} time;

#endif
