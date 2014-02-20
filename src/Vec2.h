#pragma once;

#include <cmath>
#include <iostream>
#include "cinder/Vector.h"

namespace zlx
{
    //for internal use
    class vec2
    {
    public:
        union {
            float elem[2];
            struct { float x, y; };
        };

        vec2(float x_, float y_) : x(x_), y(y_) { }

        vec2(const vec2& other) : x(other.x), y(other.y) { }

        vec2(ci::Vec2f ciVecf) : x(ciVecf.x), y(ciVecf.y) { }

        vec2(ci::Vec2i ciVeci)
            : x((float)ciVeci.x), y((float)ciVeci.y) { }

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
            float multiplyer = 1.0f / (float)length();

            return (*this *= multiplyer);
        }
    };

    class Size2 : protected vec2
    {
    public:
        Size2(float width, float height) : vec2(width, height) { }

        Size2(ci::Vec2f ci_vf) : vec2(ci_vf) { }
        Size2(ci::Vec2i ci_vi) : vec2(ci_vi) { }

        float& width() { return x; }
        float width() const { return x; }
        float& height() { return y; }
        float height() const { return y; }
        float area() { return x*y; }
    };

    inline std::ostream& operator<<(std::ostream& o, const Size2& s)
    {
        float width = s.width();
        float height = s.height();

        o << width << height;
        return o;
    }

    class Vec2 : public vec2
    {
    public:
        Vec2(float x_, float y_) : vec2(x_, y_) { }
        Vec2(const vec2& v) : vec2(v) { }
        Vec2(ci::Vec2f ci_vf) : vec2(ci_vf) { }
        Vec2(ci::Vec2i ci_vi) : vec2(ci_vi) { }

        Vec2 operator*(float f) const { return vec2::operator*(f); }
        Vec2 operator+(float f) const { return vec2::operator+(f); }
    };

    inline std::ostream& operator<<(std::ostream& o, const Vec2& v)
    {
        o << v.x << v.y;
        return o;
    }

    class Point2 : public vec2
    {
    public:
        Point2(float x, float y) : vec2(x, y) { }
        Point2(const vec2& v) : vec2(v) { }

        Point2(const cinder::Vec2i ci_vi&) : vec2(ci_vi) { }
        Point2(const cinder::Vec2f ci_vf&) : vec2(ci_vf) { }

        operator ci::Vec2f() { return ci::Vec2f(x, y); }
        operator ci::Vec2i() { return ci::Vec2i((int)x, (int)y); }

        //displace the point by vector v
        Point2 operator+(const Vec2& v) { return vec2::operator+(v); }

        Point2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
        Point2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }

        //Point2& operator-=(const Vec2& v) { return *this -= v; }

        //displace the point by vector -v
        //Point2 operator-(const Vec2& v) { return Point2(*this - v); }

        //distance between two points
        //Vec2 operator-(const Point2& other) { return Vec2(*this - other); }

        //Point2 operator+(float f) { return Point2(x + f, y + f); }
        //Point2 operator-(float f) { return Point2(x - f, y - f); }

        //displace by f
        /*Point2& operator+=(float f)
        {
            x += f;
            y += f;
            return *this;
        }

        Point2& operator/=(float f)
        {
            x += f;
            y += f;
            return *this;
        }

        Point2 operator*(const Point2& p) { return Point2(x * p.x, y * p.y); }*/
    };

    inline std::ostream& operator<<(std::ostream& o, const Point2& p)
    {
        o << p.x << p.y;
        return o;
    }

    class Box2
    {
    public:
        Box2(const Point2& p1, const Point2& p2)
            : top_left(p1), bottom_right(p2) { }

        explicit Box2(const ci::Vec2i ci_vf&) : top_left(0.0, 0.0), bottom_right(ci_vf) { }
        explicit Box2(const ci::Vec2f ci_vi&) : top_left(0.0, 0.0), bottom_right(ci_vi) { }

        Box2(const ci::Rectf ci_rect&) 
            : top_left(ci_rect.getUpperLeft()), 
            bottom_right(ci_rect.getLowerRight()) { }

        operator ci::Rectf()
        {
            return ci::Rectf(top_left, bottom_right);
        }

        Box2 operator+(const Vec2& v) const; //displace the box by vector v
        Box2 operator-(const Vec2& v) const; //displace the box by vector -v

        Box2 operator*(float f) const; //uniform scale
        Box2 operator/(float f) const; //uniform scale

        Box2 operator*(const Vec2& v) const //2D scale
        {
            return Box2(top_left * v, bottom_right * v);
        }

        Box2 operator/(const Vec2& v); //2D scale

        Size2 size()
        {
            Vec2 diff = top_left - bottom_right;

            return Size2(diff.x, diff.y);
        }

    private:
        Point2 top_left;
        Point2 bottom_right;
    };
}