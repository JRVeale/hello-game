#pragma once

#include <chrono>

class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, now;
	float interval = 0;
	bool running = false;
	bool looping = false;
public:
	Timer() {
		start = std::chrono::high_resolution_clock::now();
		now = std::chrono::high_resolution_clock::now();
	}
	void Start(float ms, bool loop = false) {
		SetInterval(ms);
		SetStart();
		running = true;
		looping = loop;
	}
	void SetInterval(float ms) {
		interval = ms;
	}
	void SetStart() {
		start = std::chrono::high_resolution_clock::now();
	}
	int Check() {
	/*
	Returns	1 when timer completes
			0 if running but not finished
			-1 if not running
	*/
		if (running) {
			now = std::chrono::high_resolution_clock::now();
			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > interval) {
				if (looping) {
					SetStart();
				}
				else {
					running = false;
				}
				return 1;
			}
			return 0;
		}
		return -1;
	}
};