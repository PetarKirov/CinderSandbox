#include "LayoutSystem.h"
#include "Vec2.h"

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace zlx
{
    namespace ui
    {
        void LayoutSystem::update()
        {
            if (!layout_root) return;

            Size2 s = (layout_area * Vec2(ci::app::getWindowSize())).size();

            Size2 requested_size = layout_root->measure(s);

            Size2 size_taken = layout_root->arrange(s);
        }

        void LayoutSystem::draw()
        {
            bool debug = true;

            if (debug && layout_root)
            {
                ci::gl::color(ci::Color(0, 0, 1));
                ci::gl::drawSolidRect(layout_root->bounding_box);
            }

            if (layout_root)
                layout_root->draw();
        }
    }
}