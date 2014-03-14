#pragma once;

#include "UIElement.h"
#include <string>

namespace zlx
{
    namespace ui
    {
        class TextBlock : public UIElement
        {
        public:
            TextBlock() : UIElement() { }
            TextBlock(std::string txt) : text_(txt) { }
            std::string& text() { return text_; }

            //From UIElement
            Size2 measure(const Size2& available_size) override;
            Size2 arrange(const Size2& available_size) override;
            void draw() override;
            size_t total_children_count() override { return 1; }

        private:
            std::string text_;
        };
    }
}