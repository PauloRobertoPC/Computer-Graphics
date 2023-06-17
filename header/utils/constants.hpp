#pragma once

#include <stdlib.h>
#include "px.hpp"

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 0.0001; 
const double	kHugeValue	= 1.0E10;

const px	black(0.0, 0.0, 0.0);
const px	white(1.0, 1.0, 1.0);
const px	red(1.0, 0.0, 0.0);

const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;
