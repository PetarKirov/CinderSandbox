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
            : location(other.location), velocity(other.velocity), radius(other.radius) { }

        Particle(Point2 location_, Vec2 velocity_, float radius_)
            : location(location_), velocity(velocity_), radius(radius_) { }

        void update() 
        { 
            location += velocity;
        }

        void draw() 
        { 
            ci::gl::drawSolidCircle(
                to_screen_coordinates(location, radius),
                radius,
				4); 
        }

        Point2 location; //relative, from (0, 0) to (1, 1), where zero is the top-left corner, and one - the bottom-right
        Vec2 velocity; //relative, from (0, 0) to (1, 1), where zero is the top-left corner, and one - the bottom-right
        float radius;  //in pixels
    };

	inline std::ostream& operator<<(std::ostream& o, const Particle& p)
	{
		o << "location: " << p.location << " velocity: " << p.velocity << " radius: " << p.radius;

		return o;
	}


	class ParticleController : public UpdateDrawSystem
    {
    public:
        void update()
        {
            for (auto& p : particles)
            {
                p.update();

                if (p.location.x <= 0.0 || p.location.x >= 1.0)
                    p.velocity.negate_x();

                if (p.location.y <= 0.0 || p.location.y >= 1.0)
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

			const float speedFactor = 0.01f;

            for (size_t i = 0; i < n; i++)
            {
				float size = (float)ci::randInt(3, 12);

				Vec2 direction = randVec2().normalize();
				Vec2 velocity = direction * (speedFactor / (size * 2));

				particles.push_back(Particle(randPoint2(), velocity, size));
            }
        }

    private:
        std::vector<Particle> particles;
    };

}