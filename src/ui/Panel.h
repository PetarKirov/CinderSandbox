#include "UIElement.h"

#include <memory>
#include <vector>

namespace zlx
{
    namespace ui
    {
        class Panel : public UIElement
        {
            virtual std::vector<std::shared_ptr<UIElement>>& children();
        };
    }
}