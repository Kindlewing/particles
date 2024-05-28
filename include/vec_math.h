#ifndef MATH_H
#define MATH_H
#include "defs.h"

#define EPSILON 1e-10 // Small value to prevent division by zero

vec2 multiply(vec2 x, vec2 y);
vec2 mult_scaler(vec2 v, double scaler);
vec2 add(vec2 x, vec2 y);
vec2 sub(vec2 x, vec2 y);
vec2 normalize(vec2 x);
double distance(vec2 pos_a, vec2 pos_b);
double magnitude(vec2 x);
double sqr_magnitude(vec2 x);

#endif
