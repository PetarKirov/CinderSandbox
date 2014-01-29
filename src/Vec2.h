#pragma once;

#include "cinder/Vector.h"

namespace zlx
{
    class vec2
    {
    public:
        vec2(float x_, float y_) : x(x_), y(y_) { }

        vec2& operator=(const vec2& other) 
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        vec2(ci::Vec2f ciVecf) : x(ciVecf.x), y(ciVecf.y) { }

        vec2(ci::Vec2i ciVeci) : x(ciVeci.x), y(ciVeci.y) { }

        operator ci::Vec2f() const { return ci::Vec2f(x, y); }

        vec2& operator+=(const vec2& other) { x += other.x; y += other.y; return *this; }

        vec2 operator+(const vec2& other) const { return vec2(other.x + x, other.y + y); }

        vec2 operator-(const vec2& other) const { return vec2(other.x - x, other.y - y); }

        //somewhat controversial
        //applies the operator member-wise
        vec2 operator*(const vec2& other) const { return vec2(other.x * x, other.y * y); }

        vec2 operator/(const vec2& other) const { return vec2(other.x / x, other.y / y); }
        //end controversial

        vec2 operator+(float f) const { return vec2(x + f, y + f); }
        vec2 operator-(float f) const { return vec2(x - f, y - f); }
        vec2 operator*(float f) const { return vec2(x * f, y * f); }
        vec2 operator/(float f) const { return vec2(x / f, y / f); }

        void negate_x()
        {
            x = -x;
        }

        void negate_y()
        {
            y = -y;
        }

        float& operator[](uint8_t component_index)
        {
            return elem[component_index];
        }

    private:
        union {
            float elem[2];
            struct { float x, y; };
        };
    };
}