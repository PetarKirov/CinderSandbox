#pragma once;

#include <vector>
#include <iostream>
#include <string>
#include "cinder/gl/gl.h"
#include "CinderHelper.h"
#include "UpdateDrawSystem.h"

namespace zlx
{
    class Particle
    {
    public:
        Particle(const Particle& other)
            : location(other.location), velocity(other.velocity), radius(other.radius), color(other.color) { }

        Particle(Point2 location_, Vec2 velocity_, float radius_, ci::Color color_ = ci::Color(1, 1, 1))
            : location(location_), velocity(velocity_), radius(radius_), color(color_) { }

        void update();

        void draw();

        Point2 location; //relative, from (0, 0) to (1, 1), where zero is the top-left corner, and one - the bottom-right
        Vec2 velocity; //relative, from (0, 0) to (1, 1), where zero is the top-left corner, and one - the bottom-right
        float radius;  //in pixels
        ci::Color color;
    };

    inline std::ostream& operator<<(std::ostream& o, const Particle& p);

	class ParticleController : public UpdateDrawSystem
    {
    public:
        void update();

        void draw();

        //Create @n particles with random location and velocity
        void generate(size_t n);

    private:
        std::vector<Particle> particles;
    };

}