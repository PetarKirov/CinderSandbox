#pragma once;

#include "cinder/Color.h"
#include "cinder/Rand.h"
#include "Vec2.h"

namespace zlx
{
    //return a point between (0, 0) and (1, 1)
    Point2 randPoint2()
    {
        Point2 rand = ci::randVec2f();

        return rand * 0.5f + 0.5f;
    }

    Vec2 randVec2()
    {
        Vec2 rand = ci::randVec2f();

        return rand * 0.5f + 0.5f;
    }

    Point2 to_screen_coordinates(Point2 relative_position, float radius)
    {
        Point2 w = ci::app::getWindowSize();

        Point2 result =  (w - 2 * radius) * relative_position + radius;

        return result;
    }


    ci::Color randColor()
    {
        ci::Color c = ci::Color(
            ci::randFloat(),
            ci::randFloat(),
            ci::randFloat());

        return c;
    }

}