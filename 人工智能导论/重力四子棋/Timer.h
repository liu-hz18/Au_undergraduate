
#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

class Timer {
	clock_t begin;
	bool is_running;
public:
	Timer() :begin(0), is_running(false) {}
	inline void start() {
		begin = clock();
		is_running = true;
	}
	inline float duration()const {
		return is_running ? (clock() - begin) / float(CLOCKS_PER_SEC) : 0.0f;
	}
};

#endif
