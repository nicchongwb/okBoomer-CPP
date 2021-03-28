#include "ItemTimer.h"

/* ItemTimer class manages the rate of spawning items.
*  Currently, items will spawn randomly between 3 to 5 seconds. This
*  value can be adjusted in MIN_ITEMSPAWNRATE and MAX_ITEMSPAWNRATE
*  The code here is used in Game.cpp -> SpawnItem()
*  Header file is in ItemTimer.h.
*/
void ItemTimer::startTimer() {

	//std::cout << "Timer has started!" << std::endl;
	m_TimerHasStarted = true;
	// choose a number between lowerBound and upperBound
	int time = intRand(MIN_ITEMSPAWNRATE, MAX_ITEMSPAWNRATE);
	// our timer thread will sleep for this number
	m_timerThread = std::thread([=]() {
		// sleeps the thread for the specified amount of time
		std::this_thread::sleep_for(std::chrono::seconds(time));
		//std::cout << "Timer has ended!" << std::endl;
		m_ReadyToSpawn = true;
	});
	
}

void ItemTimer::stopTimer() {
	// join thread once timer has finished.
	m_timerThread.join();
}