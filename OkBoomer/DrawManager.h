#pragma once

#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "Vector2D.h"

/* The Vector2D, Transform and DrawManager Class handles the updating 
*  of drwaings to the screen. Used when player moves -> draw new player position to the screen.
*  DrawManager has no CPP file as most methods are inline.
*/
class DrawManager {

public:
	
	DrawManager() {}

	// Apply Force (used to forcibly reposition an object)
	inline void ApplyForce(Vector2D F) {
		m_Force = F;
	}
	// Move an object by Fx (either left or right)
	inline void ApplyForceX(int Fx) {
		m_Force.X = Fx;
	}
	// Move an object by Fy (either up or down)
	inline void ApplyForceY(int Fy) {
		m_Force.Y = Fy;
	}

	// Remove all force on an object (stop the object)
	inline void UnsetForce() {
		m_Force = Vector2D(0, 0);
	}

	inline Vector2D GetPosition() { return m_Position; }

	void Update() {
		m_Position = m_Force;
	}

private:

	Vector2D m_Force, m_Position;
	
};
#endif