#pragma once

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

/* Vector2D class is to process drawing of objects to the screen 
*  It is used by Transform.h.
*/

class Vector2D {
public:
    int X, Y;

public:
    Vector2D(int x = 0, int y = 0) : X(x), Y(y) {}

public:
    // addition +
    inline Vector2D operator+(const Vector2D& v2) const {
        return Vector2D(X + v2.X, Y + v2.Y);
    }

    // difference -
    inline Vector2D operator-(const Vector2D& v2) const {
        return Vector2D(X - v2.X, Y - v2.Y);
    }

    void Log(std::string msg = "") {
        std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
    }
};

#endif // VECTOR2D_H
