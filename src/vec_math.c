
#include <math.h>
#include "vec_math.h"

vec2 sub(vec2 a, vec2 b) {
	vec2 result = {a.x - b.x, a.y - b.y};
	return result;
}

double distance(vec2 a, vec2 b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vec2 normalize(vec2 v) {
	double len = sqrt(v.x * v.x + v.y * v.y);
	if(len > EPSILON) {
		v.x /= len;
		v.y /= len;
	}
	return v;
}

double sqr_magnitude(vec2 v) {
	return v.x * v.x + v.y * v.y;
}

vec2 mult_scaler(vec2 v, double s) {
	vec2 result = {v.x * s, v.y * s};
	return result;
}
