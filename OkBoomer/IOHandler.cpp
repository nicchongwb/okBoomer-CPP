#include "IOHandler.h"
#include "Game.h"
#include "Player.h"

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
				KeyReleased(event.key.keysym.scancode);
				//SDL_Log("Key released");
				break;
		}
	}
}

// On key press
bool IOHandler::KeyPressed(SDL_Scancode key) {
	// return True or False depending on m_KeyStates[key] value
	return m_KeyStates[key] == true;
}

// On key release
bool IOHandler::KeyReleased(SDL_Scancode key) {

	if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_A || key == SDL_SCANCODE_S || key == SDL_SCANCODE_D || key == SDL_SCANCODE_G) {
		if (Player::s_AlrPressedP1) {
			Player::s_AlrPressedP1 = false;
		}
	}

	if (key == SDL_SCANCODE_UP || key == SDL_SCANCODE_DOWN || key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT || key == SDL_SCANCODE_COMMA) {
		if (Player::s_AlrPressedP2) {
			Player::s_AlrPressedP2 = false;
		}
	}

	m_KeyStates = SDL_GetKeyboardState(nullptr);
	// return True or False depending on m_KeyStates[key] value
	return m_KeyStates[key] == false;
}

void IOHandler::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}
