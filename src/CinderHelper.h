#pragma once;

#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "Vec2.h"

namespace zlx
{
    vec2 randVec2()
    {
        return vec2(ci::randVec2f()) * 0.5 + 0.5;
    }

    vec2 to_screen_coordinates(vec2 relative_position, float radius)
    {
        vec2 w = ci::app::getWindowSize();

        return (w - 2 * radius) * relative_position + radius;
    }
}