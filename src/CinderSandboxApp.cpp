#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderSandboxApp : public AppNative {
public:
    void setup();
    void mouseDown(MouseEvent event);
    void update();
    void draw();
    double sinTick(double rate);

private:
    zlx::ParticleController particle_controller;
};

void CinderSandboxApp::setup()
{
    particle_controller.generate(10000);
}

void CinderSandboxApp::mouseDown(MouseEvent event)
{
}

double CinderSandboxApp::sinTick(double rate = 1.0)
{
    return sin(getElapsedSeconds() * rate) * 0.5 + 0.5;
}

void CinderSandboxApp::update()
{
    particle_controller.update();
}

void CinderSandboxApp::draw()
{
    float r = sinTick(0.25);
    float g = sinTick(0.75);
    float b = sinTick(0.5);

    gl::clear(Color(r, g, b));

    particle_controller.draw();
}

CINDER_APP_NATIVE(CinderSandboxApp, RendererGl)
