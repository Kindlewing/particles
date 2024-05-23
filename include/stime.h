#ifndef STIME_H
#define STIME_H

#include <stdint.h>

typedef struct {
	float dt;
	uint64_t frame_count;
} stime;
#endif
