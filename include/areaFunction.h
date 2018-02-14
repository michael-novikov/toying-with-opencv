#pragma once

const float eps = 0.001f;

// true if point (x,y) belongs to the the area, false otherwise
typedef bool(*AreaFuncrion)(float x, float y);

bool insideParabola(float x, float y);
bool outsideParabola(float x, float y);
bool insideCircle(float x, float y);
bool outsideCircle(float x, float y);
bool leftOfLine(float x, float y);
bool rightOfLine(float x, float y);
bool equalSinPlusCos(float x, float y);