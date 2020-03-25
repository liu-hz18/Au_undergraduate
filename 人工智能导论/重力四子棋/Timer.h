
#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

class Timer {
	clock_t begin;
	bool is_running;
public:
	Timer() :begin(0), is_running(false) {}
	void start() {
		begin = clock();
		is_running = true;
	}
	float duration()const {
		if (is_running)
			return (clock() - begin) / float(CLOCKS_PER_SEC);
		return 0.0;
	}
};
#endif
