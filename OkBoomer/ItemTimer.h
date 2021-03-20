#pragma once

#ifndef ITEMTIMER_H
#define ITEMTIMER_H

#define MIN_ITEMSPAWNRATE 3 // lower bound of timer
#define MAX_ITEMSPAWNRATE 5 // upper bound of timer

#include <iostream>
#include <chrono>
#include <thread>
#include <random>

/* ItemTimer class manages the rate of spawning items.
*  Currently, items will spawn randomly between 3 to 5 seconds. This
*  value can be adjusted in MIN_ITEMSPAWNRATE and MAX_ITEMSPAWNRATE
*  Class file is in itemTimer.cpp.
*/
class ItemTimer {

	std::thread m_timerThread;

public:
	ItemTimer() {
		startTimer();
	}

	void startTimer();
	void stopTimer();

	/* Getters and Setters */
	inline bool getReadyToSpawn() { return m_ReadyToSpawn; }
	inline bool getTimerHasStarted() { return m_TimerHasStarted; }
	inline void setReadyToSpawn(bool val) { m_ReadyToSpawn = val; }
	inline void setTimerHasStarted(bool val) { m_TimerHasStarted = val; }

private:

	// variables to check if item can be spawned 
	bool m_ReadyToSpawn = false; // set to 'true' if it can be spawned
	bool m_TimerHasStarted = false; // set to 'true' if timer has already started

	// generate thread-safe random number to set timer for item spawning
	inline int intRand(const int & min, const int & max) {
		static thread_local std::mt19937 generator;
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(generator);
	}

};

#endif // !ITEMTIMER_H




