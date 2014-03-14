#pragma once;

#include <memory>
#include "..\Vec2.h"
#include "..\UpdateDrawSystem.h"


namespace zlx
{
    namespace ui
    {
        /// <summary> The main class representing UI 
        /// </summary>
        class UIElement
        {
            friend class LayoutSystem;

        public:
            UIElement() { }

            UIElement(Box2 bounding_box_)
                : bounding_box(bounding_box_) { }
            virtual ~UIElement() { }

            virtual Size2 measure(const Size2& available_size) = 0;
            virtual Size2 arrange(const Size2& available_size) = 0;
            virtual void draw() = 0;

            // Returns 1 (for the current element) + the number of
            // child elements. Computes recursively.
            virtual size_t total_children_count() = 0; 

        protected:
            //screenspace coordinates
            Box2 bounding_box;
        };
    }
}
