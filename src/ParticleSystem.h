#pragma once;

#include <vector>
#include <iostream>
#include <string>
#include "cinder/gl/gl.h"
#include "CinderHelper.h"
#include "IUpdateDrawSystem.h"

namespace zlx
{
    class Particle
    {
    public:
        Particle(const Particle& other)
            : location(other.location), velocity(other.velocity), radius(other.radius) { }

        Particle(vec2 location_, vec2 velocity_, float radius_)
            : location(location_), velocity(velocity_), radius(radius_) { }

        void update() { location += velocity; }

        void draw() 
        { 
            ci::gl::drawSolidCircle(
                to_screen_coordinates(location, radius), 
                radius,
				4); 
        }

        vec2 location; //relative, from (0, 0) to (1, 1), where zero is the top-left corner, and one - the bottom-right
        vec2 velocity; //relative, from (0, 0) to (1, 1), where zero is the top-left corner, and one - the bottom-right
        float radius;  //in pixels
    };

	inline std::ostream& operator<<(std::ostream& o, const Particle& p)
	{
		o << "location: " << p.location << " velocity: " << p.velocity << " radius: " << p.radius;

		return o;
	}


	class ParticleController : public IUpdateDrawSystem
    {
    public:
        void update()
        {
            for (auto& p : particles)
            {
                p.update();

                if (p.location[0] <= 0.0 || p.location[0] >= 1.0)
                    p.velocity.negate_x();

                if (p.location[1] <= 0.0 || p.location[1] >= 1.0)
                    p.velocity.negate_y();
            }
        }

        void draw() 
        {
            for (auto& x : particles) 
                x.draw(); 
        }

        //Create @n particles with random location and velocity
        void generate(size_t n)
        {
            using namespace ci;

			const float speedFactor = 0.01;

            for (size_t i = 0; i < n; i++)
            {
				int size = ci::randInt(3, 12);

				vec2 direction = randVec2().normalize();
				vec2 velocity = direction * (speedFactor / (size * 2));

				particles.push_back(Particle(randVec2(), velocity, size));
            }
        }

    //private:
        std::vector<Particle> particles;
    };

}