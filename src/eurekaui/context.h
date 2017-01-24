#pragma once
#include <vector>
#include "element.h"
#include "drivers/video/base.h"

namespace EurekaUI
{
    /** EurekaUI context
     *
     */
    class Context
    {
    public:
        explicit Context();
        Element* root() { return &mRoot; }
    private:
        Element mRoot;
    };
}
