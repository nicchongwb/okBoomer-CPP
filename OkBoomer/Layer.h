#pragma once

#ifndef LAYER_H
#define LAYER_H

/* Base Class for any class related to layering
*  In this engine: TileLayer class is derived class of Layer class
*  Class file is Layer.cpp
*/

class Layer
{
public:
    virtual void Render() = 0;
    virtual void Update() = 0;
};
#endif // LAYER_H
