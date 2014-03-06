#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "UpdateDrawSystem.h"
#include "ParticleSystem.h"
#include "STDExtensions.h" //for make_unique
#include "LayoutSystem.h"
#include "Chart.h"
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

    std::shared_ptr <zlx::ui::charting::ItemsSource_f> data;

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
    using namespace zlx::ui;

    counter = 0;
    addTimedAction([this] { backgroundColor = this->sinColor(); }, 1.0 / 60);

    //Add systems:
    auto pc = make_unique<ParticleController>();
    pc->generate(50);
    systems.push_back(move(pc));

    auto layout_sys = make_unique<LayoutSystem>(Box2(Vec2(1.0f, 0.2f)));

    data = make_shared<charting::ItemsSource_f>();

    layout_sys->set_layout_root<Chart>().items_source = data;
    systems.push_back(move(layout_sys));
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

    if (data->get_data_source().size() > 100)
        data->get_data_source().erase(data->get_data_source().begin());

    data->get_data_source().emplace_back(ci::app::getElapsedSeconds(),
                                         ci::randFloat(30, 60));
}

void CinderSandboxApp::draw()
{
    ci::gl::clear(backgroundColor);

    for (auto& pSys : systems)
        pSys->draw();
}

CINDER_APP_NATIVE(CinderSandboxApp, ci::app::RendererGl)
