#include "TextBlock.h"
#include "..\Vec2.h"

#include "cinder/gl/gl.h"

namespace zlx
{
    namespace ui
    {
        Size2 TextBlock::measure(const Size2& available_size)
        {
            return available_size;
        }

        Size2 TextBlock::arrange(const Size2& available_size)
        {
            return available_size;
        }

        void TextBlock::draw()
        {
            auto mFont = ci::Font("Consolas", 24.0f);
            ci::gl::drawString(text_, 
                               ci::Vec2f(bounding_box.top_left_point()), 
                               ci::Color::white(), 
                               mFont);
        }
    }
}