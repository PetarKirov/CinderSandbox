#include "Chart.h"

#include "cinder/gl/gl.h"
#include "..\CinderHelper.h"

namespace zlx
{
    namespace ui
    {
        Size2 Chart::measure(const Size2& available_size)
        {
            bounding_box = Box2(available_size);

            return available_size;
        }

        Size2 Chart::arrange(const Size2& available_size)
        {
            return available_size;
        }

        void Chart::draw()
        {
            if (!items_source)
                return;

            items_source->calculate();

            const auto& data = items_source->get_data_points();

            ci::gl::color(ci::Color(0, 0, 0));

            for (size_t i = 1; i < data.size(); i++)
            {
                auto p1 = data[i - 1];
                auto p2 = data[i];

                ci::gl::drawLine(bounding_box.relative_position(p1),
                                 bounding_box.relative_position(p2));
            }
        }
    }
}