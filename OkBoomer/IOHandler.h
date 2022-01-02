#pragma once

#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <SDL.h>

/* IOHandler class is the main manager for handling IO inputs.
*  It handles both mouse and keyboard inputs. (currently only handles keyboard)
*/
class IOHandler
{
public:
	static IOHandler* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new IOHandler();

	}

	void Listen();
	bool KeyPressed(SDL_Scancode key);
	bool KeyReleased(SDL_Scancode key);


private:
	IOHandler();
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;
	static IOHandler* s_Instance;
};

#endif // !IOHANDLER_H
