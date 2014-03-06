#include "ParticleSystem.h"

namespace zlx
{
    void Particle::update()
    {
        location += velocity;
    }

    void Particle::draw()
    {
        ci::gl::color(color);
        ci::gl::drawSolidCircle(
            to_screen_coordinates(location, radius),
            radius,
            4);
    }

    inline std::ostream& operator<<(std::ostream& o, const Particle& p)
    {
        o << "location: " << p.location << " velocity: " << p.velocity << " radius: " << p.radius;

        return o;
    }

    void ParticleController::update()
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

    void ParticleController::draw()
    {
        for (auto& x : particles)
            x.draw();
    }

    void ParticleController::generate(size_t n)
    {
        using namespace ci;

        const float speedFactor = 0.01f;

        for (size_t i = 0; i < n; i++)
        {
            float size = (float)ci::randInt(3, 12);

            Vec2 direction = randVec2().normalize();
            Vec2 velocity = direction * (speedFactor / (size * 2));

            particles.push_back(Particle(randPoint2(), velocity, size, ci::Color(1, 1, 1)));
        }
    }
}