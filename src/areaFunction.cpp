#include "areaFunction.h"

#include <cmath>

bool insideParabola(float x, float y) {
	return x >= y * y;
}

bool outsideParabola(float x, float y) {
	return !insideParabola(x, y);
}

bool insideCircle(float x, float y) {
	return x * x + y * y <= 4;
}

bool outsideCircle(float x, float y) {
	return !insideCircle(x, y);
}

bool leftOfLine(float x, float y) {
	return x < -1;
}

bool rightOfLine(float x, float y) {
	return x >= -1;
}

bool equalSinPlusCos(float x, float y) {
	return y - (sin(x) + cos(x)) < eps;
}
