#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "IUpdateDrawSystem.h"
#include "ParticleSystem.h"
#include <memory>

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
	vector<shared_ptr<zlx::IUpdateDrawSystem>> systems;
};

void CinderSandboxApp::setup()
{
	systems.push_back(make_shared<zlx::ParticleController>());

	dynamic_cast<ParticleController*>(systems[0].get())->generate(50);
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
    float r = sinTick(0.25);
    float g = sinTick(0.75);
    float b = sinTick(0.5);

    gl::clear(Color(r, g, b));

	for (auto& pSys : systems)
		pSys->draw();
}

CINDER_APP_NATIVE(CinderSandboxApp, RendererGl)
