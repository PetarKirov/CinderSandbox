#pragma once;

#include <memory>
#include "Vec2.h"
#include "UpdateDrawSystem.h"


namespace zlx
{
    namespace ui
    {
        class UIElement
        {
            friend class LayoutSystem;

        public:
            UIElement(Box2 bounding_box_)
                : bounding_box(bounding_box_) { }
            virtual ~UIElement() { }

            virtual Size2 measure(const Size2& available_size) = 0;
            virtual Size2 arrange(const Size2& available_size) = 0;
            virtual void draw() = 0;
            virtual size_t total_children_count() = 0;

        protected:
            //screenspace coordinates
            Box2 bounding_box;
        };

        class Panel : public UIElement
        {

        };
    }
}
