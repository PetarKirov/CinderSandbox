#pragma once;

namespace zlx
{
    class UpdateDrawSystem
    {
    public:
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual ~UpdateDrawSystem() { }
    };
}