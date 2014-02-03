#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "UpdateDrawSystem.h"
#include "ParticleSystem.h"
#include "STDExtensions.h" //for make_unique

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace zlx;

class CinderSandboxApp : public AppNative {
public:
    void setup();
    void mouseDown(MouseEvent event);
    void update();
    void draw();
    double sinTick(double rate);

private:
	vector<unique_ptr<zlx::UpdateDrawSystem>> systems;
};

void CinderSandboxApp::setup()
{
    auto pc = std::ext::make_unique<ParticleController>();
    pc->generate(50);
    systems.push_back(std::move(pc));
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
	for (auto& pSys : systems)
		pSys->update();
}

void CinderSandboxApp::draw()
{
    float r = (float)sinTick(0.25);
    float g = (float)sinTick(0.75);
    float b = (float)sinTick(0.5);

    gl::clear(Color(r, g, b));

	for (auto& pSys : systems)
		pSys->draw();
}

CINDER_APP_NATIVE(CinderSandboxApp, RendererGl)
