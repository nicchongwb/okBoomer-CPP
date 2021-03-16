#include "IOHandler.h"
#include "Game.h"


// initialise
IOHandler* IOHandler::s_Instance = nullptr;

IOHandler::IOHandler(){
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void IOHandler::Listen() {
	SDL_Event event;

	// Event handler so the system knows what to do with our SDL window.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: 
				Game::GetInstance()->Quit(); 
				break;
			case SDL_KEYDOWN: 
				KeyDown();
				break;
			case SDL_KEYUP:
				KeyUp();
				break;
		}
	}
}

bool IOHandler::KeyPressed(SDL_Scancode key) {
	// return True or False depending on m_KeyStates[key] value
	return m_KeyStates[key] == 1;
}

void IOHandler::KeyUp() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void IOHandler::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}
