#include "include.h"

struct vec2
{
	double x, y;
};

struct house
{
	vec2 coordinaten;
};

struct pinwheel
{
	vec2 coordinaten;
	double maximalhoehe = -1; // 246,5 (größtest Windrad) * 10 - da keine höhe vorgeschrieben ist habe ich diese genommen
};