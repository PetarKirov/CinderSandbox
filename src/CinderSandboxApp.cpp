#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "UpdateDrawSystem.h"
#include "ParticleSystem.h"
#include "STDExtensions.h" //for make_unique
#include <functional>

using namespace std;

typedef function<void()> Action;
struct TimedAction
{
    TimedAction(Action a, double i) : action(a), interval(i) { }
    Action action;
    double interval; //in miliseconds
};

class CinderSandboxApp : public ci::app::AppNative {
public:
    void setup();
    void mouseDown(ci::app::MouseEvent event);
    void update();
    void draw();
private:
    ci::Color backgroundColor;
    uint64_t counter;

    vector<unique_ptr<zlx::UpdateDrawSystem>> systems;
    vector<TimedAction> updateActions;

    double sinTick(double rate = 1.0)
    {
        return sin(getElapsedSeconds() * rate) * 0.5 + 0.5;
    }

    ci::Color sinColor()
    {
        return ci::Color((float)sinTick(0.25),
                         (float)sinTick(0.75),
                         (float)sinTick(0.5));
    }

    void addTimedAction(function<void()> action, double duration)
    {
        updateActions.push_back(TimedAction(action, duration));
    }

    void executeTimedActions();
};

void CinderSandboxApp::setup()
{
    using namespace std::ext;
    using namespace zlx;

    counter = 0;

    auto pc = make_unique<ParticleController>();
    pc->generate(50);
    systems.push_back(std::move(pc));

    addTimedAction([this] { backgroundColor = this->sinColor(); }, 1.0 / 60);
}

void CinderSandboxApp::mouseDown(ci::app::MouseEvent event)
{
}

void CinderSandboxApp::executeTimedActions()
{
    double time = ci::app::getElapsedSeconds();
    double delta = 1.0 / ci::app::getFrameRate(); //precision of ~one frame

    for (auto& a : updateActions)
    {
        double c = fmod(time, a.interval);
        if (c < delta)
            a.action();
    }
}

void CinderSandboxApp::update()
{
    counter++;
    executeTimedActions();

    for (auto& pSys : systems)
        pSys->update();
}

void CinderSandboxApp::draw()
{
    ci::gl::clear(backgroundColor);

    for (auto& pSys : systems)
        pSys->draw();
}

CINDER_APP_NATIVE(CinderSandboxApp, ci::app::RendererGl)
