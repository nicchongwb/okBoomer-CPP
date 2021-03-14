#pragma once

#ifndef IOOBJECT_H
#define IOOBJECT_H

/* IOObject is an Interface. It is the main class for all objects
*  It is implemented by Entity.h
*/

class IOObject {

public:
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;
};

#endif // IOOBJECT_H

