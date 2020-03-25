#include "Strategy.h"
#include "utils.h"

float fastInvSqrt(float x) {
	float xhalf = x * 0.5f;
	int i = *(int*)& x;// get bits for floating value
	i = 0x5f3759df - (i >> 1); // gives initial guess
	x = *(float*)& i; // convert bits back to float
	x = x * (1.5f - xhalf * x * x); // Newton step
	return x;
}
