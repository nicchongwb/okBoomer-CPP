#pragma once

#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <SDL.h>

class IOHandler
{
public:
	static IOHandler* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new IOHandler();

	}

	void Listen();
	bool KeyPressed(SDL_Scancode key);


private:
	IOHandler();
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;
	static IOHandler* s_Instance;
};

#endif // !IOHANDLER_H
