#include "vec_math.h"
#include <math.h>

vec2 multiply(vec2 x, vec2 y) {
	return (vec2){x.x * y.x, x.y * y.y};
}

vec2 mult_scaler(vec2 v, double scaler) {
	return (vec2){v.x * scaler, v.y * scaler};
}

vec2 add(vec2 x, vec2 y) {
	return (vec2){x.x + y.x, x.y + y.y};
}
vec2 sub(vec2 x, vec2 y) {
	return (vec2){x.x - y.x, x.y - y.y};
}

vec2 normalize(vec2 x) {
	double m = sqrt(x.x * x.x + x.y * x.y);
	return (vec2){x.x / m, x.y / m};
}

double magnitude(vec2 x) {
	return sqrt(x.x * x.x + x.y * x.y);
}
