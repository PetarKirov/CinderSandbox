#pragma once;

#include <cmath>
#include <iostream>
#include "cinder/Vector.h"

namespace zlx
{
    class vec2
    {
    public:
        vec2(float x_, float y_) : x(x_), y(y_) { }

		vec2(ci::Vec2f ciVecf) : x(ciVecf.x), y(ciVecf.y) { }

		vec2(ci::Vec2i ciVeci) : x(ciVeci.x), y(ciVeci.y) { }

		operator ci::Vec2f() const { return ci::Vec2f(x, y); }

        vec2& operator=(const vec2& other) 
        {
            x = other.x;
            y = other.y;
            return *this;
        }        

        vec2& operator+=(const vec2& other) { x += other.x; y += other.y; return *this; }

		vec2& operator*=(float f) { x *= f; y *= f; return *this; }

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

		float lengthSquared() const
		{
			return x*x + y*y;
		}

		float length() const
		{
			return sqrt(x*x + y*y);
		}

		vec2& normalize()
		{
			float multiplyer = 1.0 / length();

			return (*this *= multiplyer);
		}

        union {
            float elem[2];
            struct { float x, y; };
        };
    };

	inline std::ostream& operator<<(std::ostream& o, const vec2& v)
	{
		o << v.length();
		return o;
	}
}