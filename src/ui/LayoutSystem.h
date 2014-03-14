#pragma once;

#include "UIElement.h"
#include "..\STDExtensions.h"

namespace zlx
{
    namespace ui
    {
        class LayoutSystem : public UpdateDrawSystem
        {
        public:
            LayoutSystem(Box2 layout_area_)
                : layout_area(layout_area_) { }

            void update() override;

            void draw() override;

            //Creates a new instance of UIElem, sets it as the layout_root and returns a reference to it
            template<class UIElem>
            UIElem& set_layout_root();

        private:
            std::unique_ptr<UIElement> layout_root;
            Box2 layout_area;
        };

        template<class UIElem>
        UIElem& LayoutSystem::set_layout_root()
        {
            using namespace std;
            using namespace std::ext;

            auto root = make_unique<UIElem>(layout_area);
            layout_root = move(root);

            auto x = layout_root.get();

            return *dynamic_cast<UIElem*>(x);
        }
    }
}