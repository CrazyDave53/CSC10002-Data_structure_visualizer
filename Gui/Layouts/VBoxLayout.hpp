#ifndef GUI_VBOXLAYOUT_HPP
#define GUI_VBOXLAYOUT_HPP

#include "Layout.hpp"

namespace gui
{

/**
 * Vertically stacked layout
 */
class VBoxLayout: public Layout
{
public:
    void recomputeGeometry() override;
};

}

#endif // GUI_VBOXLAYOUT_HPP
