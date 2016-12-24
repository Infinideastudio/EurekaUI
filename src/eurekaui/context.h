#ifndef EUREKAUI_CONTEXT_H
#define EUREKAUI_CONTEXT_H
#include <vector>
#include "element.h"

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

#endif
