#pragma once

#ifndef LAYER_H
#define LAYER_H

// interface for all layer type: image- and tile layer
// Helps us to layer backgrounds
class Layer
{
public:
    virtual void Render() = 0;
    virtual void Update() = 0;
};
#endif // LAYER_H
